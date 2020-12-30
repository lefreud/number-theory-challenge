//
// Created by freud on 12/29/2020.
//

#ifndef CPP__UTILS_H_
#define CPP__UTILS_H_

using namespace std;

const int INTEGER_BIT_SIZE = sizeof(unsigned int) * 8;

int getPolynomialBitSize(const unsigned int *polynomial, int size) {
  int bitSize = INTEGER_BIT_SIZE * size;

  int firstSignificantInt = size - 1;
  // remove leading integers containing only zeros
  for (; firstSignificantInt >= 0; firstSignificantInt--) {
    if (polynomial[firstSignificantInt] == 0) {
      bitSize -= sizeof(unsigned int) * 8;
    } else {
      break;
    }
  }

  if (firstSignificantInt == -1) {
    return 0;
  }

  int intBitSize = 0;
  while ((polynomial[firstSignificantInt] >> intBitSize) != 1) {
    intBitSize++;
  }
  intBitSize++;

  int leadingZeros = INTEGER_BIT_SIZE - intBitSize;
  bitSize -= leadingZeros;
  return bitSize;
}

void polynomialDivision(const unsigned int *dividend,
                        const unsigned int *divisor,
                        unsigned int *&quotient,
                        unsigned int *&remainder,
                        int size) {
  for (int i = 0; i < size; i++) {
    quotient[i] = 0;
    remainder[i] = dividend[i];
  }

  int divisorBitLength = getPolynomialBitSize(divisor, size);

  for (int i = size - 1; i >= 0; i--) {
    for (int j = INTEGER_BIT_SIZE - 1; j >= 0; j--) {
      int bitIndex = i * INTEGER_BIT_SIZE + j;

      if (bitIndex < divisorBitLength - 1)
        break;

      if (((remainder[i] >> j) & 1) == 1) {
        // update remainder
        int bitShift = bitIndex - divisorBitLength + 1;
        int intShift = bitShift / INTEGER_BIT_SIZE;
        for (int k = i; k >= intShift; k--) {
          remainder[k] ^= divisor[k - intShift] << (bitShift % INTEGER_BIT_SIZE);
          if (bitShift % 32 != 0 && k - 1 - intShift >= 0) {
            remainder[k] ^= divisor[k - 1 - intShift] >> ((INTEGER_BIT_SIZE - bitShift) % INTEGER_BIT_SIZE);
          }
        }

        // update quotient
        quotient[intShift] ^= 1 << (bitShift % INTEGER_BIT_SIZE);
      }
    }
  }
}

void polynomialModulo(const unsigned int *dividend, const unsigned int *divisor, unsigned int *&remainder, int size) {
  auto quotient = new unsigned int[size];
  polynomialDivision(dividend, divisor, quotient, remainder, size);
}

vector<unsigned int *> computeBerlekampFactors(const unsigned int *polynomial, int size) {
  int hBitSize = getPolynomialBitSize(polynomial, size) - 1;

  // init matrix
  auto matrix = new unsigned int *[hBitSize];
  for (int i = 0; i < hBitSize; i++) {
    matrix[i] = new unsigned int[size];
    for (int j = 0; j < size; j++) {
      matrix[i][j] = 0;
    }
  }

  for (int i = 0; i < hBitSize; i++) {
    // initialize the power of x
    auto xPower = new unsigned int[size];
    for (int j = 0; j < size; j++) {
      xPower[j] = 0;
    }
    int power = i * 2;

    // modulo f
    if (power + 1 < getPolynomialBitSize(polynomial, size)) {
      xPower[power / INTEGER_BIT_SIZE] = 1 << (power % INTEGER_BIT_SIZE);
    } else if (power + 1 > getPolynomialBitSize(polynomial, size)) {
      xPower[power / INTEGER_BIT_SIZE] = 1 << (power % INTEGER_BIT_SIZE);
      auto remainder = new unsigned int[size];
      polynomialModulo(xPower, polynomial, remainder, size);
      for (int j = 0; j < size; j++) {
        xPower[j] = remainder[j];
      }
    } else {
      // same degree, xPower must be zero.
    }

    // add to matrix
    for (int j = 0; j < hBitSize; j++) {
      if (j == 0 || (xPower[j / INTEGER_BIT_SIZE] >> (j - 1) >= 0b10)) {
        matrix[j][i / INTEGER_BIT_SIZE] ^=
            ((xPower[j / INTEGER_BIT_SIZE] >> (j % INTEGER_BIT_SIZE)) & 1) << (i % INTEGER_BIT_SIZE);
      }
    }
  }
  vector<unsigned int*> factors;
  return factors;
}

/**
Factors a monic univariate polynomial over a galois field (2).
The polynomial x^3 + x^2 + 1 is represented as
0000 0000 0000 0000 0000 0000 0000 1101
with an unsigned int.
*/
vector<unsigned int *> factorPolynomial(const unsigned int *polynomial, int size) {
  vector<unsigned int *> factors;
  auto simplifiedPolynomial = new unsigned int[size];
  for (int i = 0; i < size; i++)
    simplifiedPolynomial[i] = polynomial[i];

  // compute x factors

  while ((simplifiedPolynomial[0] & 1) == 0) {
    for (int i = 0; i < size - 1; i++) {
      simplifiedPolynomial[i] >>= 1;
      simplifiedPolynomial[i] ^= simplifiedPolynomial[i + 1] << (INTEGER_BIT_SIZE - 1);
    }
    simplifiedPolynomial[size - 1] >>= 1;
    auto factor = new unsigned int[1];
    factor[0] = 0b10;
    factors.push_back(factor); // x factor
  }

  // compute factors ending with + 1

  auto divisor = new unsigned int[size];
  divisor[0] = 0b11;
  for (int i = 1; i < size; i++)
    divisor[i] = 0;

  auto quotient = new unsigned int[size];
  auto remainder = new unsigned int[size];
  int w = 0;
  while (getPolynomialBitSize(simplifiedPolynomial, size) != 1) {
    w++;
    if (w % 1000000 == 0)
      cout << w << endl;
    polynomialDivision(simplifiedPolynomial, divisor, quotient, remainder, size);

    if (getPolynomialBitSize(remainder, size) == 0) {
      auto divisorCopy = new unsigned int[size];
      for (int i = 0; i < size; i++)
        divisorCopy[i] = divisor[i];
      factors.push_back(divisorCopy);

      for (int i = 0; i < size; i++)
        simplifiedPolynomial[i] = quotient[i];
    } else {
      // add 0b10 to divisor
      // Note: no overflow checking
      unsigned int carry = 1;
      int currentBit = 1;
      do {
        divisor[currentBit / INTEGER_BIT_SIZE] ^= carry << (currentBit % INTEGER_BIT_SIZE);
        if ((divisor[currentBit / INTEGER_BIT_SIZE] & (1 << (currentBit % INTEGER_BIT_SIZE))) == 0) {
          carry = 1;
        } else {
          carry = 0;
        }
        currentBit++;
      } while (carry != 0);
    }
  }
  return factors;
}
//
// unsigned int *multiplyPolynomials(unsigned int firstPolynomial, unsigned int secondPolynomial) {
//   int size = 32;
//   auto *product = new unsigned int[size / 2];
//
//   for (int i = 0; i < size / 16; i++) {
//     product[i] = 0;
//   }
//   for (int i = 0; i < size; i++) {
//     for (int j = 0; j < size; j++) {
//       // b[(i + j) / 32] ^= ( (a[i / 32] >> (i % 32)) &
//       //      (a[j / 32 + size / 32] >> (j % 32)) & 1 ) << ((i + j) % 32);   // Magic centaurian operation
//
//       // simplified version
//       product[(i + j) / 32] ^= ((firstPolynomial >> i) & (secondPolynomial >> j) & 1) << ((i + j) % 32);
//     }
//   }
//   return product;
// }
//
// vector<unsigned int*> blindDeconvolution(unsigned int polynomial, int factorMaxSizes) {
//   auto factors = factorPolynomial(polynomial);
//
//   unsigned int leftPolynomial1 = 1, rightPolynomial1 = 1;
//   for (size_t i = factors.size() - 1; i >= 1; i--) {
//     if (getPolynomialBitSize(factors[i]) + getPolynomialBitSize(leftPolynomial1) - 1 < factorMaxSizes) {
//       auto product = multiplyPolynomials(leftPolynomial1, factors[i]);
//       leftPolynomial1 = product[0];
//     } else if (getPolynomialBitSize(factors[i]) + getPolynomialBitSize(rightPolynomial1) - 1 < factorMaxSizes) {
//       auto product = multiplyPolynomials(rightPolynomial1, factors[i]);
//       rightPolynomial1 = product[0];
//     } else {
//       // ambiguity
//       cout << "unexpected ambiguity" << endl;
//       cout << factors[i] << endl;
//     }
//   }
//
//   // Last and ambiguous factor
//
//   vector<unsigned int*> deconvoluted;
//   auto firstPossibility = new unsigned int[2];
//   auto product = multiplyPolynomials(leftPolynomial1, factors[0]);
//   firstPossibility[0] = product[0];
//   firstPossibility[1] = rightPolynomial1;
//
//   auto secondPossibility = new unsigned int[2];
//   product = multiplyPolynomials(rightPolynomial1, factors[0]);
//   secondPossibility[0] = leftPolynomial1;
//   secondPossibility[1] = product[0];
//
//   deconvoluted.push_back(firstPossibility);
//   deconvoluted.push_back(secondPossibility);
//   return deconvoluted;
// }

#endif //CPP__UTILS_H_
