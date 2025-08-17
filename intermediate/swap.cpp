#include <iostream>
using namespace std;

void swapUsingPointer(int* first, int* second) {
  int temp = *first;
  *first = *second;
  *second = temp;
}

void swapUsingReference(int& first, int& second) {
  int temp = first;
  first = second;
  second = temp;
}

int main() {
  int x = 10;
  int y = 20;

  swapUsingPointer(&x, &y);
  cout << "x=" << x << " y=" << y << endl;

  swapUsingReference(x, y);
  cout << "x=" << x << " y=" << y << endl;

  return 0;
}