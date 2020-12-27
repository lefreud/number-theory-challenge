#include <iostream>
#include <bitset>
#include <vector>

using namespace std;

unsigned int getPolynomialSize(unsigned int polynomial) {
  unsigned int size = 0;
  while (polynomial >> size != 0) {
    size += 1;
  }
  return size;
}

void polynomialDivision(unsigned int dividend, unsigned int divisor, unsigned int &quotient, unsigned int &remainder) {
  quotient = 0;
  remainder = dividend;

  unsigned int divisorBitLength = getPolynomialSize(divisor);

  for (unsigned int i = sizeof(unsigned int) * 8 - 1; i >= divisorBitLength - 1; i--) {
    quotient <<= 1;
    if (((remainder >> i) & 1) == 1) {
      remainder ^= divisor << (i - divisorBitLength + 1);
      quotient ^= 1;
    }
  }
}

/**
Factors a monic univariate polynomial over a galois field (2).
The polynomial x^3 + x^2 + 1 is represented as
0000 0000 0000 0000 0000 0000 0000 1101
with an unsigned int.
*/
vector<unsigned int> factorPolynomial(unsigned int polynomial) {
  vector<unsigned int> factors;
  unsigned int simplifiedPolynomial = polynomial;

  // compute x factors
  while ((simplifiedPolynomial & 1) == 0) {
    simplifiedPolynomial >>= 1;
    factors.push_back(0b10); // x factor
  }

  // compute factors ending with + 1
  unsigned int divisor = 0b11;
  while (simplifiedPolynomial != 1) {
    unsigned int quotient = 0, remainder = 0;
    polynomialDivision(simplifiedPolynomial, divisor, quotient, remainder);
    if (remainder == 0) {
      factors.push_back(divisor);
      simplifiedPolynomial = quotient;
    } else {
      divisor += 0b10;
    }
  }
  return factors;
}

unsigned int *multiplyPolynomials(unsigned int firstPolynomial, unsigned int secondPolynomial) {
  int size = 32;
  auto *product = new unsigned int[size / 2];

  for (int i = 0; i < size / 16; i++) {
    product[i] = 0;
  }
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      // b[(i + j) / 32] ^= ( (a[i / 32] >> (i % 32)) &
      //      (a[j / 32 + size / 32] >> (j % 32)) & 1 ) << ((i + j) % 32);   // Magic centaurian operation

      // simplified version
      product[(i + j) / 32] ^= ((firstPolynomial >> i) & (secondPolynomial >> j) & 1) << ((i + j) % 32);
    }
  }
  return product;
}

vector<unsigned int*> blindDeconvolution(unsigned int polynomial, int factorMaxSizes) {
  auto factors = factorPolynomial(polynomial);

  unsigned int leftPolynomial1 = 1, rightPolynomial1 = 1;
  for (size_t i = factors.size() - 1; i >= 1; i--) {
    if (getPolynomialSize(factors[i]) + getPolynomialSize(leftPolynomial1) - 1 < factorMaxSizes) {
      auto product = multiplyPolynomials(leftPolynomial1, factors[i]);
      leftPolynomial1 = product[0];
    } else if (getPolynomialSize(factors[i]) + getPolynomialSize(rightPolynomial1) - 1 < factorMaxSizes) {
      auto product = multiplyPolynomials(rightPolynomial1, factors[i]);
      rightPolynomial1 = product[0];
    } else {
      // ambiguity
      cout << "unexpected ambiguity" << endl;
      cout << factors[i] << endl;
    }
  }

  // Last and ambiguous factor

  vector<unsigned int*> deconvoluted;
  auto firstPossibility = new unsigned int[2];
  auto product = multiplyPolynomials(leftPolynomial1, factors[0]);
  firstPossibility[0] = product[0];
  firstPossibility[1] = rightPolynomial1;

  auto secondPossibility = new unsigned int[2];
  product = multiplyPolynomials(rightPolynomial1, factors[0]);
  secondPossibility[0] = leftPolynomial1;
  secondPossibility[1] = product[0];

  deconvoluted.push_back(firstPossibility);
  deconvoluted.push_back(secondPossibility);
  return deconvoluted;
}

int main() {
  std::cout << "Hello, World!" << std::endl;
  unsigned int quotient, remainder;
  // polynomialDivision(0b10111, 0b11, quotient, remainder);
  // cout << bitset<32>(quotient) << endl;
  // cout << bitset<32>(remainder) << endl;
  //cout << getPolynomialSize(0b1001) << endl;


  auto factors = factorPolynomial(0b10010100111100000010110011110011);
  for (auto e : factors)
    cout << bitset<32>(e) << endl;

  auto convolution = multiplyPolynomials(0b100, 0b0111);
  for (int i = 0; i < 2; i++)
    cout << bitset<32>(convolution[i]) << endl;

  cout << "DECONV" << endl << endl;
  for (auto e : blindDeconvolution(0b00111000, 4))
    for (int i = 0; i < 2; i++)
      cout << bitset<32>(e[i]) << endl;
  return 0;
}
