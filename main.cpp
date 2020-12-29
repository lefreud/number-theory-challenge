#include <iostream>
#include <bitset>
#include <vector>
#include "utils.h"

int main() {
  std::cout << "Hello, World!" << std::endl;
  int COUNT = 2;
  auto quotient = new unsigned int[COUNT];
  auto remainder = new unsigned int[COUNT];
  auto a = new unsigned int[COUNT];
  a[0] = 0x46508fb7;
  a[1] = 0x6677e201;
  auto b = new unsigned int[COUNT];
  b[0] = 0xb0c152f9;
  //b[0] = 0b10010;
  b[1] = 0x0;
  polynomialDivision(a, b, quotient, remainder, COUNT);
  cout << "quotient" << endl;
  // for (int i = 0; i < 3; i++)
  //   cout << bitset<32>(quotient[i]) << endl;
//
  // cout << "remainder" << endl;
  // for (int i = 0; i < 3; i++)
  //   cout << bitset<32>(remainder[i]) << endl;

  for (int i = 0; i < 2; i++)
    cout << hex << quotient[i] << endl;

  cout << "remainder" << endl;
  for (int i = 0; i < 2; i++)
    cout << hex << remainder[i] << endl;



  // cout << bitset<32>(quotient) << endl;
  // cout << bitset<32>(remainder) << endl;
  // cout << getPolynomialBitSize(0b1001) << endl;


  // auto factors = factorPolynomial(0b10010100111100000010110011110011);
  // for (auto e : factors)
  //   cout << bitset<32>(e) << endl;
//
  // auto convolution = multiplyPolynomials(0b100, 0b0111);
  // for (int i = 0; i < 2; i++)
  //   cout << bitset<32>(convolution[i]) << endl;
//
  // cout << "DECONV" << endl << endl;
  // for (auto e : blindDeconvolution(0b00111000, 4))
  //   for (int i = 0; i < 2; i++)
  //     cout << bitset<32>(e[i]) << endl;
  // return 0;

  // cout << getPolynomialBitSize(a, 3) << endl;
}
