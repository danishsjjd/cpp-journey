#include <iostream>
using namespace std;

// Using array print entries in reverse order
int main() {
  int numbers[] = {10, 20, 30};

  int* ptr = &numbers[size(numbers) - 1];

  while (ptr >= numbers) {
    cout << *ptr << " ";
    ptr--;
  }

  return 0;
}