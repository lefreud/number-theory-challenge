#include <iostream>
#include <vector>
#include "utils.h"
#include <iomanip>

int main() {
  int bitsDividedByTwo;
  cin >> bitsDividedByTwo;
  cin.ignore();

  int size = 2 * bitsDividedByTwo / INTEGER_BIT_SIZE;
  auto polynomial = new unsigned int[size];

  for (int i = 0; i < size; i++) {
    cin >> hex >> polynomial[i];
  }
  cin.ignore();
  auto outputs = decode(polynomial, size);

  cout << setfill('0') << hex << setw(8);
  for (auto it = outputs.begin(); it != outputs.end(); it++) {
    for (int b = 0; b < size - 1; b++) {
      cout << setw(8) << it->first[b] << " ";
    }
    cout << setw(8) << it->first[size - 1];
    if (it != outputs.end()) cout << endl;
  }
}
