//
// Created by freud on 12/29/2020.
//
#include <gtest/gtest.h>
#include "utils.h"

TEST(division, bigDividend1) {
  int COUNT = 2;
  auto quotient = new unsigned int[COUNT];
  quotient[0] = 8; // random value
  auto remainder = new unsigned int[COUNT];
  remainder[0] = 434; // random value
  auto dividend = new unsigned int[COUNT];
  dividend[0] = 0x46508fb7;
  dividend[1] = 0x6677e201;
  auto divisor = new unsigned int[COUNT];
  divisor[0] = 0xb0c152f9;
  divisor[1] = 0x0;
  polynomialDivision(dividend, divisor, quotient, remainder, COUNT);
  EXPECT_EQ(remainder[0], 0);
  EXPECT_EQ(remainder[1], 0);
  EXPECT_EQ(quotient[0], 0xebf2831f);
  EXPECT_EQ(quotient[1], 0);
}

TEST(division, bigDividend2) {
  int COUNT = 2;
  auto quotient = new unsigned int[COUNT];
  quotient[0] = 8; // random value
  auto remainder = new unsigned int[COUNT];
  remainder[0] = 434; // random value
  auto dividend = new unsigned int[COUNT];
  dividend[0] = 0x46508fb7;
  dividend[1] = 0x6677e201;
  auto divisor = new unsigned int[COUNT];
  divisor[0] = 0xebf2831f;
  divisor[1] = 0x0;
  polynomialDivision(dividend, divisor, quotient, remainder, COUNT);
  EXPECT_EQ(remainder[0], 0);
  EXPECT_EQ(remainder[1], 0);
  EXPECT_EQ(quotient[0], 0xb0c152f9);
  EXPECT_EQ(quotient[1], 0);
}

TEST(division, veryBigOperands) {
  int COUNT = 4;
  auto quotient = new unsigned int[COUNT];
  auto remainder = new unsigned int[COUNT];
  auto dividend = new unsigned int[COUNT];
  dividend[0] = 0b11111111111111111111111111111110;
  dividend[1] = 0b11111111111111111111111111111111;
  dividend[2] = 0b11111111111111111111111111111111;
  dividend[3] = 0b11111111111111111111111111111111;
  auto divisor = new unsigned int[COUNT];
  divisor[0] = 0b11111111111111111111111111111111;
  divisor[1] = 0b11111111111111111111111111111111;
  divisor[2] = 0b11111111111111111111111111111111;
  divisor[3] = 0b01111111111111111111111111111111;
  polynomialDivision(dividend, divisor, quotient, remainder, COUNT);
  EXPECT_EQ(remainder[0], 0);
  EXPECT_EQ(remainder[1], 0);
  EXPECT_EQ(remainder[2], 0);
  EXPECT_EQ(remainder[3], 0);
  EXPECT_EQ(quotient[0], 0b10);
  EXPECT_EQ(quotient[1], 0);
  EXPECT_EQ(quotient[2], 0);
  EXPECT_EQ(quotient[3], 0);
}

TEST(division, veryBigOperandsRemainder) {
  int COUNT = 4;
  auto quotient = new unsigned int[COUNT];
  auto remainder = new unsigned int[COUNT];
  auto dividend = new unsigned int[COUNT];
  dividend[0] = 0b11111111111111111111111111111111;
  dividend[1] = 0b11111111111111111111111111111111;
  dividend[2] = 0b11111111111111111111111111111111;
  dividend[3] = 0b11111111111111111111111111111111;
  auto divisor = new unsigned int[COUNT];
  divisor[0] = 0b11111111111111111111111111111111;
  divisor[1] = 0b11111111111111111111111111111111;
  divisor[2] = 0b11111111111111111111111111111111;
  divisor[3] = 0b01111111111111111111111111111111;
  polynomialDivision(dividend, divisor, quotient, remainder, COUNT);
  EXPECT_EQ(remainder[0], 0b1);
  EXPECT_EQ(remainder[1], 0);
  EXPECT_EQ(remainder[2], 0);
  EXPECT_EQ(remainder[3], 0);
  EXPECT_EQ(quotient[0], 0b10);
  EXPECT_EQ(quotient[1], 0);
  EXPECT_EQ(quotient[2], 0);
  EXPECT_EQ(quotient[3], 0);
}

TEST(division, divisionByItself) {
  int COUNT = 3;
  auto quotient = new unsigned int[COUNT];
  auto remainder = new unsigned int[COUNT];
  auto dividend = new unsigned int[COUNT];
  dividend[0] = 0b11101010000111100010101010100001;
  dividend[1] = 0b00101011111001000001101010011111;
  dividend[2] = 0b00101011110001010010101011101001;
  auto divisor = new unsigned int[COUNT];
  divisor[0] = 0b11101010000111100010101010100001;
  divisor[1] = 0b00101011111001000001101010011111;
  divisor[2] = 0b00101011110001010010101011101001;
  polynomialDivision(dividend, divisor, quotient, remainder, COUNT);
  EXPECT_EQ(remainder[0], 0);
  EXPECT_EQ(remainder[1], 0);
  EXPECT_EQ(remainder[2], 0);
  EXPECT_EQ(quotient[0], 0b1);
  EXPECT_EQ(quotient[1], 0);
  EXPECT_EQ(quotient[2], 0);
}

TEST(division, divisionBy32bitShifted) {
  int COUNT = 3;
  auto quotient = new unsigned int[COUNT];
  auto remainder = new unsigned int[COUNT];
  auto dividend = new unsigned int[COUNT];
  dividend[0] = 0b0;
  dividend[1] = 0b11101010000111100010101010100001;
  dividend[2] = 0b00101011111001000001101010011111;
  auto divisor = new unsigned int[COUNT];
  divisor[0] = 0b11101010000111100010101010100001;
  divisor[1] = 0b00101011111001000001101010011111;
  divisor[2] = 0b0;
  polynomialDivision(dividend, divisor, quotient, remainder, COUNT);
  EXPECT_EQ(remainder[0], 0);
  EXPECT_EQ(remainder[1], 0);
  EXPECT_EQ(remainder[2], 0);
  EXPECT_EQ(quotient[0], 0);
  EXPECT_EQ(quotient[1], 0b1);
  EXPECT_EQ(quotient[2], 0);
}

TEST(division, smallDividend1) {
  int COUNT = 2;
  auto quotient = new unsigned int[COUNT];
  quotient[0] = 8; // random value
  auto remainder = new unsigned int[COUNT];
  remainder[0] = 434; // random value
  auto dividend = new unsigned int[COUNT];
  dividend[0] = 0b10111000;
  dividend[1] = 0;
  auto divisor = new unsigned int[COUNT];
  divisor[0] = 0b11;
  divisor[1] = 0x0;
  polynomialDivision(dividend, divisor, quotient, remainder, COUNT);
  EXPECT_EQ(remainder[0], 0);
  EXPECT_EQ(remainder[1], 0);
  EXPECT_EQ(quotient[0], 0b1101000);
  EXPECT_EQ(quotient[1], 0);
}

TEST(division, smallDividend2) {
  int COUNT = 2;
  auto quotient = new unsigned int[COUNT];
  quotient[0] = 8; // random value
  auto remainder = new unsigned int[COUNT];
  remainder[0] = 434; // random value
  auto dividend = new unsigned int[COUNT];
  dividend[0] = 0b10111;
  dividend[1] = 0;
  auto divisor = new unsigned int[COUNT];
  divisor[0] = 0b11;
  divisor[1] = 0x0;
  polynomialDivision(dividend, divisor, quotient, remainder, COUNT);
  EXPECT_EQ(remainder[0], 0);
  EXPECT_EQ(remainder[1], 0);
  EXPECT_EQ(quotient[0], 0b1101);
  EXPECT_EQ(quotient[1], 0);
}

TEST(modulo, small) {
  int COUNT = 1;
  auto remainder = new unsigned int[COUNT];
  auto dividend = new unsigned int[COUNT];
  dividend[0] = 0b1000000;
  auto divisor = new unsigned int[COUNT];
  divisor[0] = 0b110001;
  polynomialModulo(dividend, divisor, remainder, COUNT);
  EXPECT_EQ(remainder[0], 0b10011);
}

TEST(factoring, small1) {
  int COUNT = 1;
  auto polynomial = new unsigned int[COUNT];
  polynomial[0] = 0b1001110001;
  auto factors = decode(polynomial, COUNT);
  vector<unsigned int*> expectedFactors(2);
  expectedFactors[0] = new unsigned int[1];
  expectedFactors[1] = new unsigned int[1];
  expectedFactors[0][0] = 0b111;
  expectedFactors[1][0] = 0b11001011;
  EXPECT_EQ(factors[0][0], expectedFactors[0][0]);
  EXPECT_EQ(factors[1][0], expectedFactors[1][0]);
}

TEST(factoring, small2) {
  int COUNT = 1;
  auto polynomial = new unsigned int[COUNT];
  polynomial[0] = 0b100111000100;
  auto factors = decode(polynomial, COUNT);

  int EXPECTED_FACTORS = 4;
  vector<unsigned int*> expectedFactors(EXPECTED_FACTORS);
  for (int i = 0; i < EXPECTED_FACTORS; i++)
    expectedFactors[i] = new unsigned int[1];

  expectedFactors[0][0] = 0b10;
  expectedFactors[1][0] = 0b10;
  expectedFactors[2][0] = 0b111;
  expectedFactors[3][0] = 0b11001011;
  for (int i = 0; i < EXPECTED_FACTORS; i++)
    EXPECT_EQ(factors[i][0], expectedFactors[i][0]);
  EXPECT_EQ(factors.size(), EXPECTED_FACTORS);
}

TEST(factoring, longSimplePolynomial) {
  int COUNT = 2;
  auto polynomial = new unsigned int[COUNT];
  polynomial[0] = 0b1;
  polynomial[1] = 0b1;
  auto factors = decode(polynomial, COUNT);
  int EXPECTED_FACTORS = 32;
  vector<unsigned int*> expectedFactors(EXPECTED_FACTORS);

  // = (x+1)^32
  for (int i = 0; i < EXPECTED_FACTORS; i++) {
    expectedFactors[i] = new unsigned int[1];
    expectedFactors[i][0] = 0b11;
  }

  for (int i = 0; i < EXPECTED_FACTORS; i++)
    EXPECT_EQ(factors[i][0], expectedFactors[i][0]);
  EXPECT_EQ(factors.size(), EXPECTED_FACTORS);
}

TEST(factoring, longPolynomial) {
  int COUNT = 2;
  auto polynomial = new unsigned int[COUNT];
  polynomial[0] = 0b1;
  polynomial[1] = 0b10;
  auto factors = decode(polynomial, COUNT);
  int EXPECTED_FACTORS = 5;
  vector<unsigned int*> expectedFactors(EXPECTED_FACTORS);

  for (int i = 0; i < EXPECTED_FACTORS; i++) {
    expectedFactors[i] = new unsigned int[1];
  }

  expectedFactors[0][0] = 0b11;
  expectedFactors[1][0] = 0b111;
  expectedFactors[2][0] = 0b10010101001;
  expectedFactors[3][0] = 0b11000100011;
  expectedFactors[4][0] = 0b11111111111;

  for (int i = 0; i < EXPECTED_FACTORS; i++)
    EXPECT_EQ(factors[i][0], expectedFactors[i][0]);
  EXPECT_EQ(factors.size(), EXPECTED_FACTORS);
}

TEST(gaussianElimination, small1) {
  int bitSize = 5;
  auto matrix = new unsigned int*[bitSize];
  for (int i = 0; i < bitSize; i++)
    matrix[i] = new unsigned int[1];
  matrix[0][0] = 0b11000;
  matrix[1][0] = 0b11010;
  matrix[2][0] = 0b10110;
  matrix[3][0] = 0b11000;
  matrix[4][0] = 0b01100;
  gaussianElimination(matrix, 1, bitSize);
  EXPECT_EQ(matrix[0][0], 0b10100);
  EXPECT_EQ(matrix[1][0], 0b01100);
  EXPECT_EQ(matrix[2][0], 0b00010);
  EXPECT_EQ(matrix[3][0], 0b00000);
  EXPECT_EQ(matrix[4][0], 0b00000);
}

TEST(gaussianElimination, small2) {
  int bitSize = 6;
  auto matrix = new unsigned int*[bitSize];
  for (int i = 0; i < bitSize; i++)
    matrix[i] = new unsigned int[1];
  matrix[0][0] = 0b010000;
  matrix[1][0] = 0b000100;
  matrix[2][0] = 0b011000;
  matrix[3][0] = 0b100110;
  matrix[4][0] = 0b110010;
  matrix[5][0] = 0b010000;
  gaussianElimination(matrix, 1, bitSize);
  EXPECT_EQ(matrix[0][0], 0b100010);
  EXPECT_EQ(matrix[1][0], 0b010000);
  EXPECT_EQ(matrix[2][0], 0b001000);
  EXPECT_EQ(matrix[3][0], 0b000100);
  EXPECT_EQ(matrix[4][0], 0b000000);
  EXPECT_EQ(matrix[5][0], 0b000000);
}

TEST(nullSpace, small1) {
  int size = 6;
  auto matrix = new unsigned int*[size];
  for (int i = 0; i < size; i++) {
    matrix[i] = new unsigned int[1];
  }
  matrix[0][0] = 0b101010;
  matrix[1][0] = 0b011000;
  matrix[2][0] = 0b000100;
  matrix[3][0] = 0b000000;
  matrix[4][0] = 0b000000;
  matrix[5][0] = 0b000000;
  auto vec = findVectorFromNullSpace(matrix, 1, size);
  EXPECT_EQ(vec[0], 0b111000);
}

TEST(nullSpace, small2) {
  int size = 6;
  auto matrix = new unsigned int*[size];
  for (int i = 0; i < size; i++) {
    matrix[i] = new unsigned int[1];
  }
  matrix[0][0] = 0b1100;
  matrix[1][0] = 0b0010;
  matrix[2][0] = 0b0000;
  matrix[3][0] = 0b0000;
  auto vec = findVectorFromNullSpace(matrix, 1, size);
  EXPECT_EQ(vec[0], 0b1100);
}

TEST(gcd, small1) {
  auto first = new unsigned int[1];
  auto second = new unsigned int[1];

  first[0] = 0b110001;
  second[0] = 0b111000;

  auto out = gcd(first, second, 1);
  EXPECT_EQ(out[0], 0b111);
}

TEST(gcd, small2) {
  auto first = new unsigned int[1];
  auto second = new unsigned int[1];

  first[0] = 0b110001;
  second[0] = 0b11101;

  auto out = gcd(first, second, 1);
  EXPECT_EQ(out[0], 0b1011);
}

TEST(berlekamp, small1) {
  int COUNT = 2;
  auto polynomial = new unsigned int[COUNT];
  polynomial[0] = 0b110001;
  polynomial[1] = 0;
  auto factors = computeBerlekampFactors(polynomial, COUNT);

  int EXPECTED_FACTORS = 2;
  vector<unsigned int*> expectedFactors(EXPECTED_FACTORS);
  for (int i = 0; i < EXPECTED_FACTORS; i++)
    expectedFactors[i] = new unsigned int[1];

  expectedFactors[0][0] = 0b111;
  expectedFactors[1][0] = 0b1011;
  for (int i = 0; i < EXPECTED_FACTORS; i++)
    EXPECT_EQ(factors[i][0], expectedFactors[i][0]);
  EXPECT_EQ(factors.size(), EXPECTED_FACTORS);
}

TEST(berlekamp, small2) {
  int COUNT = 2;
  auto polynomial = new unsigned int[COUNT];
  polynomial[0] = 0b1100101;
  polynomial[1] = 0;
  auto factors = computeBerlekampFactors(polynomial, COUNT);

  int EXPECTED_FACTORS = 2;
  vector<unsigned int*> expectedFactors(EXPECTED_FACTORS);
  for (int i = 0; i < EXPECTED_FACTORS; i++)
    expectedFactors[i] = new unsigned int[1];

  expectedFactors[0][0] = 0b111;
  expectedFactors[1][0] = 0b10111;
  for (int i = 0; i < EXPECTED_FACTORS; i++)
    EXPECT_EQ(factors[i][0], expectedFactors[i][0]);
  EXPECT_EQ(factors.size(), EXPECTED_FACTORS);
}

TEST(berlekamp, codingGameSample) {
  int COUNT = 4;
  auto polynomial = new unsigned int[COUNT];
  polynomial[0] = 0x46508fb7;
  polynomial[1] = 0x6677e201;
  polynomial[2] = 0;
  polynomial[3] = 0;
  auto factors = computeBerlekampFactors(polynomial, COUNT);

  int EXPECTED_FACTORS = 2;
  vector<unsigned int*> expectedFactors(EXPECTED_FACTORS);
  for (int i = 0; i < EXPECTED_FACTORS; i++)
    expectedFactors[i] = new unsigned int[COUNT];

  expectedFactors[0][0] = 0xebf2831f;
  expectedFactors[0][1] = 0;
  expectedFactors[1][0] = 0xb0c152f9;
  expectedFactors[1][1] = 0;
  for (int i = 0; i < EXPECTED_FACTORS; i++)
    EXPECT_EQ(factors[i][0], expectedFactors[i][0]);
  EXPECT_EQ(factors.size(), EXPECTED_FACTORS);
}

TEST(berlekamp, codingGameTest1) {
  int COUNT = 2;
  auto polynomial = new unsigned int[COUNT];
  polynomial[0] = 0x000073af;
  polynomial[1] = 0;
  auto factors = computeBerlekampFactors(polynomial, COUNT);

  int EXPECTED_FACTORS = 2;
  vector<unsigned int*> expectedFactors(EXPECTED_FACTORS);
  for (int i = 0; i < EXPECTED_FACTORS; i++)
    expectedFactors[i] = new unsigned int[COUNT];

  expectedFactors[0][0] = 0b11100101;
  expectedFactors[0][1] = 0;
  expectedFactors[1][0] = 0b10000011;
  expectedFactors[1][1] = 0;
  for (int i = 0; i < EXPECTED_FACTORS; i++)
    EXPECT_EQ(factors[i][0], expectedFactors[i][0]);
  EXPECT_EQ(factors.size(), EXPECTED_FACTORS);
}

TEST(berlekamp, codingGameTest2) {
  int COUNT = 2;
  auto polynomial = new unsigned int[COUNT];
  polynomial[0] = 0x738377c1;
  polynomial[1] = 0;
  auto factors = computeBerlekampFactors(polynomial, COUNT);

  int EXPECTED_FACTORS = 2;
  vector<unsigned int*> expectedFactors(EXPECTED_FACTORS);

  for (int i = 0; i < EXPECTED_FACTORS; i++)
    expectedFactors[i] = new unsigned int[COUNT];

  expectedFactors[0][0] = 0b1100110101010101;
  expectedFactors[0][1] = 0;
  expectedFactors[1][0] = 0b1011000011000101;
  expectedFactors[1][1] = 0;
  for (int i = 0; i < EXPECTED_FACTORS; i++)
    EXPECT_EQ(factors[i][0], expectedFactors[i][0]);
  EXPECT_EQ(factors.size(), EXPECTED_FACTORS);
}

TEST(berlekamp, big1) {
  int COUNT = 4;
  auto polynomial = new unsigned int[COUNT];
  polynomial[0] = 0x338377c1;
  polynomial[1] = 0x00000040;
  for (int i = 2; i < COUNT; i++)
    polynomial[i] = 0;
  auto factors = computeBerlekampFactors(polynomial, COUNT);

  int EXPECTED_FACTORS = 2;
  vector<unsigned int*> expectedFactors(EXPECTED_FACTORS);

  for (int i = 0; i < factors.size(); i++)
    displayPolynomial(factors[i], COUNT);
  // for (int i = 0; i < EXPECTED_FACTORS; i++)
  //   expectedFactors[i] = new unsigned int[COUNT];
//
  // expectedFactors[0][0] = 0b1100110101010101;
  // expectedFactors[0][1] = 0;
  // expectedFactors[1][0] = 0b1011000011000101;
  // expectedFactors[1][1] = 0;
  // for (int i = 0; i < EXPECTED_FACTORS; i++)
  //   EXPECT_EQ(factors[i][0], expectedFactors[i][0]);
  // EXPECT_EQ(factors.size(), EXPECTED_FACTORS);
}

TEST(berlekamp, bla) {
  int COUNT = 1;
  auto polynomial = new unsigned int[COUNT];
  polynomial[0] = 0b10111;
  auto factors = computeBerlekampFactors(polynomial, COUNT);
}

TEST(berlekamp, codingGameTest64) {
  int COUNT = 8;
  auto polynomial = new unsigned int[COUNT];
  polynomial[0] = 0xf3268b49;
  polynomial[1] = 0x661859eb;
  polynomial[2] = 0x0b324559;
  polynomial[3] = 0x65ee6bda;
  for (int i = 4; i < COUNT; i++)
    polynomial[i] = 0;
  auto factors = computeBerlekampFactors(polynomial, COUNT);

  for (int i = 0; i < 2; i++)
    displayPolynomial(factors[i], COUNT);
  displayPolynomial(polynomial, COUNT);
  displayPolynomial(multiplyPolynomials(factors[0], factors[1], COUNT), COUNT);
}

TEST(berlekamp, codingGameTest128) {
  int COUNT = 16;
  auto polynomial = new unsigned int[COUNT];
  polynomial[0] = 0xa91db473;
  polynomial[1] = 0xfcea8db4;
  polynomial[2] = 0xf3bb434a;
  polynomial[3] = 0x8dba2f16;
  polynomial[4] = 0x51abc87e;
  polynomial[5] = 0x92c44759;
  polynomial[6] = 0x5c1a16d3;
  polynomial[7] = 0x6111c6f4;
  for (int i = 8; i < COUNT; i++)
    polynomial[i] = 0;
  auto factors = computeBerlekampFactors(polynomial, COUNT);
  displayPolynomial(polynomial, COUNT);
  displayPolynomial(multiplyPolynomials(factors[0], factors[1], COUNT), COUNT);
  EXPECT_EQ(1,1);
}

TEST(berlekamp, codingGameTest256) {
  int COUNT = 32;
  auto polynomial = new unsigned int[COUNT];
  polynomial[0] =  0x4af6fc33;
  polynomial[1] =  0x39029380;
  polynomial[2] =  0x465c5267;
  polynomial[3] =  0xc72f6a8b;
  polynomial[4] =  0x0906e6d0;
  polynomial[5] =  0xca60550f;
  polynomial[6] =  0x14a5e47c;
  polynomial[7] =  0x42ad10fb;
  polynomial[8] =  0x4a3bb446;
  polynomial[9] =  0xbb74360a;
  polynomial[10] = 0x5ea02b9c;
  polynomial[11] = 0x23c68553;
  polynomial[12] = 0x3fade253;
  polynomial[13] = 0xe270ba24;
  polynomial[14] = 0x39e141ad;
  polynomial[15] = 0x6c38c43d;
  for (int i = 16; i < COUNT; i++)
    polynomial[i] = 0;
  auto factors = computeBerlekampFactors(polynomial, COUNT);
  for (int i = 0; i < factors.size(); i++)
    displayPolynomial(factors[i], COUNT);
  displayPolynomial(polynomial, COUNT);
  displayPolynomial(multiplyPolynomials(factors[0], factors[1], COUNT), COUNT);
}

TEST(berlekamp, codingGameFrequent) {
  int COUNT = 16;
  auto polynomial = new unsigned int[COUNT];
  polynomial[0] = 0x541a4231;
  polynomial[1] = 0x5d324646;
  polynomial[2] = 0x27219a26;
  polynomial[3] = 0x12497b0e;
  polynomial[4] = 0x724eddcb;
  polynomial[5] = 0x0e131617;
  polynomial[6] = 0x9521bedf;
  polynomial[7] = 0x55544dc7;
  for (int i = 8; i < COUNT; i++)
    polynomial[i] = 0;

  auto factors = computeBerlekampFactors(polynomial, COUNT);
  for (auto factor : factors) {
    for (int j = COUNT-1;j>=0;j--) {
      cout << hex << factor[j];
    }
    cout << endl;
  }
//
  // int EXPECTED_FACTORS = 2;
  // vector<unsigned int*> expectedFactors(EXPECTED_FACTORS);
  // for (int i = 0; i < EXPECTED_FACTORS; i++)
  //   expectedFactors[i] = new unsigned int[1];

  // expectedFactors[0][0] = 0xb0c152f9;
  // expectedFactors[0][1] = 0;
  // expectedFactors[1][0] = 0xebf2831f;
  // expectedFactors[1][1] = 0;
  // for (int i = 0; i < EXPECTED_FACTORS; i++)
  //   EXPECT_EQ(factors[i][0], expectedFactors[i][0]);
  // EXPECT_EQ(factors.size(), EXPECTED_FACTORS);
}

TEST(derivative, zero) {
  auto polynomial = new unsigned int[1];
  polynomial[0] = 0;
  auto derivative = getFormalDerivative(polynomial, 1);
  EXPECT_EQ(derivative[0], 0);
}

TEST(derivative, one) {
  auto polynomial = new unsigned int[1];
  polynomial[0] = 1;
  auto derivative = getFormalDerivative(polynomial, 1);
  EXPECT_EQ(derivative[0], 0);
}

TEST(derivative, bigPower1) {
  // x^32
  auto polynomial = new unsigned int[2];
  polynomial[0] = 0;
  polynomial[1] = 0b1;
  auto derivative = getFormalDerivative(polynomial, 2);
  EXPECT_EQ(derivative[0], 0);
  EXPECT_EQ(derivative[1], 0);
}

TEST(derivative, bigPower2) {
  // x^32
  auto polynomial = new unsigned int[2];
  polynomial[0] = 0;
  polynomial[1] = 0b10;
  auto derivative = getFormalDerivative(polynomial, 2);
  EXPECT_EQ(derivative[0], 0);
  EXPECT_EQ(derivative[1], 0b1);
}

TEST(derivative, small1) {
  // x^4+x^3+x+1
  auto polynomial = new unsigned int[1];
  polynomial[0] = 0b11011;
  auto derivative = getFormalDerivative(polynomial, 1);
  EXPECT_EQ(derivative[0], 0b101);
}

TEST(derivative, small2) {
  // x^5+x^3+x^2+1
  auto polynomial = new unsigned int[1];
  polynomial[0] = 0b101101;
  auto derivative = getFormalDerivative(polynomial, 1);
  EXPECT_EQ(derivative[0], 0b10100);
}

TEST(squareRoot, small1) {
  auto polynomial = new unsigned int[1];
  polynomial[0] = 0b100010000010101;
  auto squareRoot = getSquareRoot(polynomial, 1);
  EXPECT_EQ(squareRoot[0], 0b10100111);
}

TEST(squareRoot, small2) {
  auto polynomial = new unsigned int[2];
  // x^32
  polynomial[0] = 0b0;
  polynomial[1] = 0b1;
  auto squareRoot = getSquareRoot(polynomial, 2);
  EXPECT_EQ(squareRoot[0], 0b10000000000000000);
  EXPECT_EQ(squareRoot[1], 0);
}

TEST(squareFreeDecomposition, small1) {
  // x^4+x^3+x+1
  unsigned int polynomial[] = {0b11011};
  auto squareFreeFactors = getSquareFreeDecomposition(polynomial, 1);
  EXPECT_EQ(squareFreeFactors.size(), 2);
  EXPECT_EQ(squareFreeFactors.find(3)->second.first[0], 0b111);
  EXPECT_EQ(squareFreeFactors.find(3)->second.second, 1);
  EXPECT_EQ(squareFreeFactors.find(2)->second.first[0], 0b11);
  EXPECT_EQ(squareFreeFactors.find(2)->second.second, 2);
}

TEST(squareFreeDecomposition, small2) {
  // x^5+x^3+x^2+1
  unsigned int polynomial[] = {0b101101};
  auto squareFreeFactors = getSquareFreeDecomposition(polynomial, 1);
  EXPECT_EQ(squareFreeFactors.size(), 2);
  EXPECT_EQ(squareFreeFactors.find(3)->second.first[0], 0b111);
  EXPECT_EQ(squareFreeFactors.find(3)->second.second, 1);
  EXPECT_EQ(squareFreeFactors.find(2)->second.first[0], 0b11);
  EXPECT_EQ(squareFreeFactors.find(2)->second.second, 3);
  // EXPECT_EQ(squareFreeFactors[1][0], 0b1);
  // EXPECT_EQ(squareFreeFactors[2][0], 0b11);
}


TEST(squareFreeDecomposition, perfectSquare) {
  // x^8+x^2+1 = (x^4+x+1)^2
  unsigned int polynomial[] = {0b100000101};
  auto squareFreeFactors = getSquareFreeDecomposition(polynomial, 1);
  EXPECT_EQ(squareFreeFactors.size(), 1);
  EXPECT_EQ(squareFreeFactors.find(5)->second.first[0], 0b10011);
  EXPECT_EQ(squareFreeFactors.find(5)->second.second, 2);
}

TEST(squareFreeDecomposition, perfectCube) {
  // x^12+x^9+x^8+x^6+x^4+x^3+x^2+x+1 = (x^4+x+1)^3
  unsigned int polynomial[] = {0b1001101011111};
  auto squareFreeFactors = getSquareFreeDecomposition(polynomial, 1);
  EXPECT_EQ(squareFreeFactors.size(), 1);
  EXPECT_EQ(squareFreeFactors.find(5)->second.first[0], 0b10011);
  EXPECT_EQ(squareFreeFactors.find(5)->second.second, 3);
}

TEST(squareFreeDecomposition, bigSquareFree) {
  // x^33+1
  // = (x + 1) (x^2 + x + 1) (x^10 + x^7 + x^5 + x^3 + 1) (x^10 + x^9 + x^5 + x + 1) (x^10 + x^9 + x^8 + x^7 + x^6 + x^5 + x^4 + x^3 + x^2 + x + 1) (mod 2)
  unsigned int polynomial[] = {0b1, 0b10};
  auto squareFreeFactors = getSquareFreeDecomposition(polynomial, 2);
  EXPECT_EQ(squareFreeFactors.size(), 1);
  EXPECT_EQ(squareFreeFactors.find(34)->second.first[0], 0b1);
  EXPECT_EQ(squareFreeFactors.find(34)->second.first[1], 0b10);
  EXPECT_EQ(squareFreeFactors.find(34)->second.second, 1);
}

TEST(squareFreeDecomposition, big1) {
  // x^34+1
  // = (x^17+1)^2
  // = (x + 1)^2 (x^8 + x^5 + x^4 + x^3 + 1)^2 (x^8 + x^7 + x^6 + x^4 + x^2 + x + 1)^2 (mod 2)
  unsigned int polynomial[] = {0b1, 0b100};
  auto squareFreeFactors = getSquareFreeDecomposition(polynomial, 2);
  EXPECT_EQ(squareFreeFactors.size(), 1);
  EXPECT_EQ(squareFreeFactors.find(18)->second.first[0], 0b100000000000000001);
  EXPECT_EQ(squareFreeFactors.find(18)->second.first[1], 0b0);
  EXPECT_EQ(squareFreeFactors.find(18)->second.second, 2);
}


TEST(squareFreeDecomposition, big2) {
  // x^34 + x^4 + x^2 + 1
  // = (x + 1)^4 (x^15 + x^13 + x^11 + x^9 + x^7 + x^5 + x^3 + x + 1)^2 (mod 2)
  unsigned int polynomial[] = {0b10101, 0b100};
  auto squareFreeFactors = getSquareFreeDecomposition(polynomial, 2);
  EXPECT_EQ(squareFreeFactors.size(), 2);
  EXPECT_EQ(squareFreeFactors.find(16)->second.first[0], 0b1010101010101011);
  EXPECT_EQ(squareFreeFactors.find(16)->second.first[1], 0b0);
  EXPECT_EQ(squareFreeFactors.find(16)->second.second, 2);
  EXPECT_EQ(squareFreeFactors.find(2)->second.first[0], 0b11);
  EXPECT_EQ(squareFreeFactors.find(2)->second.first[1], 0b0);
  EXPECT_EQ(squareFreeFactors.find(2)->second.second, 4);
}


TEST(squareFreeDecomposition, codingGame64bits) {
  // x^34+1
  // = (x^17+1)^2
  // = (x + 1)^2 (x^8 + x^5 + x^4 + x^3 + 1)^2 (x^8 + x^7 + x^6 + x^4 + x^2 + x + 1)^2 (mod 2)

  int COUNT = 8;
  auto polynomial = new unsigned int[COUNT];
  polynomial[0] = 0xf3268b49;
  polynomial[1] = 0x661859eb;
  polynomial[2] = 0x0b324559;
  polynomial[3] = 0x65ee6bda;

  auto squareFreeFactors = getSquareFreeDecomposition(polynomial, 4);
  for (auto it = squareFreeFactors.begin(); it != squareFreeFactors.end(); it++)
    cout << it->first << " " << it->second.first[0] << " " << it->second.second << endl;
  EXPECT_EQ(squareFreeFactors.size(), 1);
  EXPECT_EQ(squareFreeFactors.find(18)->second.first[0], 0b100000000000000001);
  EXPECT_EQ(squareFreeFactors.find(18)->second.first[1], 0b0);
  EXPECT_EQ(squareFreeFactors.find(18)->second.second, 2);
}

TEST(squareFreeDecomposition, codingGame128bits) {
  int COUNT = 16;
  auto polynomial = new unsigned int[COUNT];
  polynomial[0] = 0xa91db473;
  polynomial[1] = 0xfcea8db4;
  polynomial[2] = 0xf3bb434a;
  polynomial[3] = 0x8dba2f16;
  polynomial[4] = 0x51abc87e;
  polynomial[5] = 0x92c44759;
  polynomial[6] = 0x5c1a16d3;
  polynomial[7] = 0x6111c6f4;
  for (int i = 8; i < 16; i++)
    polynomial[i] = 0;

  auto squareFreeFactors = getSquareFreeDecomposition(polynomial, COUNT);
  for (auto it = squareFreeFactors.begin(); it != squareFreeFactors.end(); it++)
    cout << it->first << " " << it->second.first[0] << " " << it->second.second << endl;
}

TEST(squareFreeDecomposition, codingGame256bits) {
  int COUNT = 32;
  auto polynomial = new unsigned int[COUNT];
  polynomial[0] =  0x4af6fc33;
  polynomial[1] =  0x39029380;
  polynomial[2] =  0x465c5267;
  polynomial[3] =  0xc72f6a8b;
  polynomial[4] =  0x0906e6d0;
  polynomial[5] =  0xca60550f;
  polynomial[6] =  0x14a5e47c;
  polynomial[7] =  0x42ad10fb;
  polynomial[8] =  0x4a3bb446;
  polynomial[9] =  0xbb74360a;
  polynomial[10] = 0x5ea02b9c;
  polynomial[11] = 0x23c68553;
  polynomial[12] = 0x3fade253;
  polynomial[13] = 0xe270ba24;
  polynomial[14] = 0x39e141ad;
  polynomial[15] = 0x6c38c43d;
  for (int i = 16; i < COUNT; i++)
    polynomial[i] = 0;

  auto squareFreeFactors = getSquareFreeDecomposition(polynomial, COUNT);
  for (auto it = squareFreeFactors.begin(); it != squareFreeFactors.end(); it++)
    cout << it->first << " " << it->second.first[0] << " " << it->second.second << endl;
}

TEST(isLessThan, small1) {
  unsigned int first[] = {0b0};
  unsigned int second[] = {0b0};
  EXPECT_EQ(isLessThan(first, second, 1), false);
}

TEST(isLessThan, small2) {
  unsigned int first[] = {0b1};
  unsigned int second[] = {0b0};
  EXPECT_EQ(isLessThan(first, second, 1), true);
}

TEST(isLessThan, small3) {
  unsigned int first[] = {0b1111};
  unsigned int second[] = {0b1000};
  EXPECT_EQ(isLessThan(first, second, 1), true);
}

TEST(isLessThan, small4) {
  unsigned int first[] = {0b1111};
  unsigned int second[] = {0b10000};
  EXPECT_EQ(isLessThan(first, second, 1), false);
}

TEST(isLessThan, medium1) {
  unsigned int first[] = {0b0, 0b1};
  unsigned int second[] = {0b10000, 0};
  EXPECT_EQ(isLessThan(first, second, 2), true);
}

TEST(isLessThan, medium2) {
  unsigned int first[] = {0b0, 0b100};
  unsigned int second[] = {0b1110, 0b10};
  EXPECT_EQ(isLessThan(first, second, 2), true);
}