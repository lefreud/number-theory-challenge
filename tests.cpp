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

TEST(factoring, small1) {
  int COUNT = 1;
  auto polynomial = new unsigned int[COUNT];
  polynomial[0] = 0b1001110001;
  auto factors = factorPolynomial(polynomial, COUNT);
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
  auto factors = factorPolynomial(polynomial, COUNT);

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
  auto factors = factorPolynomial(polynomial, COUNT);
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
  auto factors = factorPolynomial(polynomial, COUNT);
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


TEST(factoring, codingGameSample) {
  int COUNT = 2;
  auto polynomial = new unsigned int[COUNT];
  polynomial[0] = 0x46508fb7;
  polynomial[1] = 0x6677e201;
  auto factors = factorPolynomial(polynomial, COUNT);
  for (auto & factor : factors) {
    cout << factor << endl;
  }
  // int EXPECTED_FACTORS = 4;
  // vector<unsigned int*> expectedFactors(EXPECTED_FACTORS);
  // for (int i = 0; i < EXPECTED_FACTORS; i++)
  //   expectedFactors[i] = new unsigned int[1];
//
  // expectedFactors[0][0] = 0b10;
  // expectedFactors[1][0] = 0b10;
  // expectedFactors[2][0] = 0b111;
  // expectedFactors[3][0] = 0b11001011;
  // for (int i = 0; i < EXPECTED_FACTORS; i++)
  //   EXPECT_EQ(factors[i][0], expectedFactors[i][0]);
}
