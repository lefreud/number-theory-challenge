//
// Created by freud on 12/29/2020.
//

#ifndef CPP__UTILS_H_
#define CPP__UTILS_H_

# include <bitset>

using namespace std;

const int INTEGER_BIT_SIZE = sizeof(unsigned int) * 8;

void displayPolynomial(const unsigned int* polynomial, int size) {
  for (int j = size - 1; j >= 0; j--) {
    cout << bitset<32>(polynomial[j]);
  }
  cout << endl;
}

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

void gaussianElimination(unsigned int **&matrix, int size, int bitSize) {
  int pivotRow = 0;
  for (int pivotColumn = bitSize - 1; pivotColumn >= 0; pivotColumn--) {
    // Find the pivot row and swap it with the current row
    bool pivotFound = false;
    for (int row = pivotRow; row < bitSize; row++) {
      if ((matrix[row][pivotColumn / INTEGER_BIT_SIZE] & (1 << pivotColumn)) != 0) {
        // swap rows
        if (row != pivotRow) {
          auto temporaryRow = new unsigned int[size];
          for (int j = 0; j < size; j++)
            temporaryRow[j] = matrix[pivotRow][j];
          for (int j = 0; j < size; j++)
            matrix[pivotRow][j] = matrix[row][j];
          for (int j = 0; j < size; j++)
            matrix[row][j] = temporaryRow[j];
          delete[] temporaryRow;
        }

        pivotFound = true;
        break;
      }
    }

    // simplify other rows
    if (pivotFound) {
      for (int row = 0; row < bitSize; row++) {
        if (row == pivotRow)
          continue;

        if ((matrix[row][pivotColumn / INTEGER_BIT_SIZE] & (1 << (pivotColumn % INTEGER_BIT_SIZE))) != 0) {
          // There's a one in this row's pivot column, eliminate it!!!
          for (int j = pivotColumn / INTEGER_BIT_SIZE; j >= 0; j--) {
            matrix[row][j] ^= matrix[pivotRow][j];
          }
        }
      }
      pivotRow++;
    }
  }
  // for (int i = 0; i < bitSize; i++) {
  //   for (int j = size - 1; j >= 0; j--) {
  //     cout << bitset<32>(matrix[i][j]);
  //   }
  //   cout << endl;
  // }
}

unsigned int getBinaryParity(const unsigned int *sequence, int size) {
  unsigned int parity = 0;
  for (int bitIndex = 0; bitIndex < size * INTEGER_BIT_SIZE; bitIndex++) {
    if ((sequence[bitIndex / INTEGER_BIT_SIZE] & (1 << (bitIndex % INTEGER_BIT_SIZE))) != 0) {
      parity ^= 1;
    }
  }
  return parity;
}
/**
 * Finds a vector from the null space of a matrix.
 *
 * @param rrefMatrix Reduced row echelon form binary matrix
 * @param size integers per row
 * @param bitSize matrix dimension
 * @return A vector in the null space
 */
unsigned int *findVectorFromNullSpace(unsigned int **rrefMatrix, int size, int bitSize) {
  unsigned int choicesMatrix[bitSize][size];
  for (int row = 0; row < bitSize; row++) {
    for (int j = 0; j < size; j++) {
      choicesMatrix[row][j] = rrefMatrix[row][j];
    }
  }

  unsigned int mustBeZeros[size];
  unsigned int mustBeOnes[size];
  for (int i = 0; i < size; i++) {
    mustBeOnes[i] = 0;
    mustBeZeros[i] = 0;
  }

  for (int row = 0; row < bitSize; row++) {
    unsigned int usedOnes[size];
    for (int j = 0; j < size; j++)
      usedOnes[j] = rrefMatrix[row][j] & mustBeOnes[j];
    unsigned int usedOnesParity = getBinaryParity(usedOnes, size);

    // set bits that must be zero to zero
    for (int j = 0; j < size; j++) {
      choicesMatrix[row][j] &= ~mustBeZeros[j];
      choicesMatrix[row][j] &= ~mustBeOnes[j];
    }
    unsigned int choicesParity = getBinaryParity(choicesMatrix[row], size);
    unsigned int rowParity = choicesParity ^usedOnesParity;

    if (rowParity != 0) {
      for (int column = 0; column < bitSize; column++) {
        if ((choicesMatrix[row][column / INTEGER_BIT_SIZE] & (1 << (column % INTEGER_BIT_SIZE))) != 0) {
          mustBeZeros[column / INTEGER_BIT_SIZE] ^= 1 << (column % INTEGER_BIT_SIZE);
          choicesMatrix[row][column / INTEGER_BIT_SIZE] ^= 1 << (column % INTEGER_BIT_SIZE);
          break;
        }
      }
    }
    for (int j = 0; j < size; j++) {
      mustBeOnes[j] |= choicesMatrix[row][j];
    }
  }

  auto vectorFromNullSpace = new unsigned int[size];
  for (int i = 0; i < size; i++)
    vectorFromNullSpace[i] = mustBeOnes[i];
  return vectorFromNullSpace;
}

/**
 * Finds the greatest common divisor between two polynomials. First must be greater than second.
 * Euclide algo
 */
unsigned int *gcd(const unsigned int *first, const unsigned int *second, int size) {
  // init
  auto dividend = new unsigned int[size];
  auto divisor = new unsigned int[size];
  auto quotient = new unsigned int[size];
  auto remainder = new unsigned int[size];
  for (int i = 0; i < size; i++) {
    dividend[i] = first[i];
    divisor[i] = second[i];
    quotient[i] = 0;
    remainder[i] = first[i];
  }

  while (true) {
    polynomialDivision(dividend, divisor, quotient, remainder, size);
    if (getPolynomialBitSize(remainder, size) == 0)
      break;

    for (int i = 0; i < size; i++)
      dividend[i] = divisor[i];
    for (int i = 0; i < size; i++)
      divisor[i] = remainder[i];
  }
  return divisor;
}

/**
 * Factorizes a polynomial in GF(2).
 *
 * @param polynomial A squarefree polynomial. Must have twice the size it needs
 * @param size Must be twice the size of the actual polynomial
 * @return two factors
 */
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
    unsigned int xPower[size];
    for (int j = 0; j < size; j++) {
      xPower[j] = 0;
    }
    int power = i * 2;

    xPower[power / INTEGER_BIT_SIZE] = 1 << (power % INTEGER_BIT_SIZE);

    auto remainder = new unsigned int[size];
    polynomialModulo(xPower, polynomial, remainder, size);

    for (int j = 0; j < size; j++) {
      xPower[j] = remainder[j];
    }
    delete[] remainder;

    // add to matrix
    for (int j = 0; j < hBitSize; j++) {
      matrix[j][i / INTEGER_BIT_SIZE] ^=
          ((xPower[j / INTEGER_BIT_SIZE] >> (j % INTEGER_BIT_SIZE)) & 1) << (i % INTEGER_BIT_SIZE);
    }
  }

  // removed flipped identity matrix
  for (int i = 0; i < hBitSize; i++) {
    matrix[i][i / INTEGER_BIT_SIZE] ^= (1 << (i % INTEGER_BIT_SIZE));
  }

  gaussianElimination(matrix, size, hBitSize);

  // Find two vectors from null space
  unsigned int *vectorsFromNullSpace[2];
  vectorsFromNullSpace[0] = findVectorFromNullSpace(matrix, size, hBitSize);
  // Second vector is the first one + 1
  vectorsFromNullSpace[1] = new unsigned int[size];
  for (int i = 0; i < size; i++)
    vectorsFromNullSpace[1][i] = vectorsFromNullSpace[0][i];
  vectorsFromNullSpace[1][0] ^= 1;

  vector<unsigned int *> factors;
  factors.push_back(gcd(polynomial, vectorsFromNullSpace[0], size));
  factors.push_back(gcd(polynomial, vectorsFromNullSpace[1], size));

  // cleanup matrix
  for (int i = 0; i < hBitSize; i++) {
    delete[] matrix[i];
  }

  return factors;
}

unsigned int *getFormalDerivative(const unsigned int *polynomial, int size) {
  auto derivative = new unsigned int[size];

  // shift bits by one position to the right
  for (int i = 0; i < size; i++) {
    if (polynomial[i] > 1)
      derivative[i] = polynomial[i] >> 1;
    else
      derivative[i] = 0;

    if (i < size - 1 && (polynomial[i + 1] & 1) == 1) {
      derivative[i] ^= polynomial[i + 1] << (INTEGER_BIT_SIZE - 1);
    }
  }

  // only even powers should be kept
  unsigned int bitMask = 0;
  for (int i = 0; i < INTEGER_BIT_SIZE; i += 2)
    bitMask ^= 1 << i;

  for (int i = 0; i < size; i++) {
    derivative[i] &= bitMask;
  }
  return derivative;
}

unsigned int *getSquareRoot(const unsigned int *polynomial, int size) {
  auto squareRoot = new unsigned int[size];
  for (int i = 0; i < size; i++)
    squareRoot[i] = 0;

  for (int i = 0; i < size * INTEGER_BIT_SIZE; i += 2) {
    auto originalBit = (1 << (i % INTEGER_BIT_SIZE)) & polynomial[i / INTEGER_BIT_SIZE];
    if (originalBit)
      squareRoot[(i / 2) / INTEGER_BIT_SIZE] |= 1 << ((i / 2) % INTEGER_BIT_SIZE);
  }

  return squareRoot;
}

/**
 * Returns a vector of squarefree polynomials composing the input polynomial.
 *
 * Reference:
 * https://en.wikipedia.org/wiki/Factorization_of_polynomials_over_finite_fields#Square-free_factorization
 *
 * @param polynomial The initial polynomial
 * @param size The size of the polynomial
 * @return The squarefree polynomials
 */
multimap<int, pair<unsigned int *, int>> getSquareFreeDecomposition(const unsigned int *polynomial, int size) {
  // TODO: w not vector
  vector<unsigned int *> w;

  // R
  multimap<int, pair<unsigned int *, int>> squareFreeFactors; // polysize, <poly, multiplicity>

  // c <- gcd(f, f')
  vector<unsigned int *> c;
  auto polynomialDerivative = getFormalDerivative(polynomial, size);
  auto c0 = gcd(polynomial, polynomialDerivative, size);
  c.push_back(c0);

  // w <- f/c
  auto w1 = new unsigned int[size];
  auto remainder = new unsigned int[size];
  polynomialDivision(polynomial, c[0], w1, remainder, size);
  w.push_back(w1);

  int multiplicity = 1;

  while (getPolynomialBitSize(w[w.size() - 1], size) != 1) {
    // y <- gcd(w, c)
    auto y = gcd(w[w.size() - 1], c[c.size() - 1], size);

    // fac <- w/y
    auto fac = new unsigned int[size];
    polynomialDivision(w[w.size() - 1], y, fac, remainder, size);

    // R <- R . fac^i
    // don't add one
    if (getPolynomialBitSize(fac, size) != 1)
      squareFreeFactors.emplace(getPolynomialBitSize(fac, size), make_pair(fac, multiplicity));

    // w <- y
    w.push_back(y);

    // c <- c/y
    auto cTemp = new unsigned int[size];
    polynomialDivision(c[c.size() - 1], y, cTemp, remainder, size);
    c.push_back(cTemp);

    multiplicity += 1;
  }

  if (getPolynomialBitSize(c[c.size() - 1], size) != 1) {
    auto cNext = getSquareRoot(c[c.size() - 1], size);
    c.push_back(cNext);
    auto additionalFactors = getSquareFreeDecomposition(c[c.size() - 1], size);
    for (auto &additionalFactor:additionalFactors) {
      int actualMultiplicity = additionalFactor.second.second * 2;
      squareFreeFactors.emplace(additionalFactor.first, make_pair(additionalFactor.second.first, actualMultiplicity));
    }
  }

  // can we return vector?
  return squareFreeFactors;
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
/*//
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
// }*/

#endif //CPP__UTILS_H_
