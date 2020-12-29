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
  EXPECT_EQ(quotient[0], 0b10);
  EXPECT_EQ(quotient[1], 0);
  EXPECT_EQ(quotient[2], 0);
  EXPECT_EQ(quotient[3], 0);
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