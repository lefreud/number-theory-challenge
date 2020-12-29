//
// Created by freud on 12/29/2020.
//

#ifndef CPP__UTILS_H_
#define CPP__UTILS_H_

using namespace std;

const int INTEGER_BIT_SIZE = sizeof(unsigned int) * 8;

int getPolynomialBitSize(const unsigned int* polynomial, int size) {
  int bitSize = INTEGER_BIT_SIZE * size;

  int firstSignificantInt = size - 1;
  // remove leading integers containing only zeros
  for ( ; firstSignificantInt >= 0; firstSignificantInt--) {
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

void polynomialDivision(const unsigned int* dividend, const unsigned int* divisor, unsigned int* &quotient, unsigned int* &remainder, int size) {
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
          if (k - 1 - intShift >=  0){
            remainder[k] ^= divisor[k - 1 - intShift] >> ((INTEGER_BIT_SIZE - bitShift) % INTEGER_BIT_SIZE);
          }
        }

        // update quotient
        quotient[intShift] ^= 1 << (bitShift % INTEGER_BIT_SIZE);
      }
    }
  }
}
//
// /**
// Factors a monic univariate polynomial over a galois field (2).
// The polynomial x^3 + x^2 + 1 is represented as
// 0000 0000 0000 0000 0000 0000 0000 1101
// with an unsigned int.
// */
// vector<unsigned int> factorPolynomial(unsigned int polynomial) {
//   vector<unsigned int> factors;
//   unsigned int simplifiedPolynomial = polynomial;
//
//   // compute x factors
//   while ((simplifiedPolynomial & 1) == 0) {
//     simplifiedPolynomial >>= 1;
//     factors.push_back(0b10); // x factor
//   }
//
//   // compute factors ending with + 1
//   unsigned int divisor = 0b11;
//   while (simplifiedPolynomial != 1) {
//     unsigned int quotient = 0, remainder = 0;
//     polynomialDivision(simplifiedPolynomial, divisor, quotient, remainder);
//     if (remainder == 0) {
//       factors.push_back(divisor);
//       simplifiedPolynomial = quotient;
//     } else {
//       divisor += 0b10;
//     }
//   }
//   return factors;
// }
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
