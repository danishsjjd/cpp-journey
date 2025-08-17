#include <iostream>
using namespace std;

int main() {
  int numbers[] = {1, 20, 30};

  for (int i = 0; i < sizeof(numbers) / sizeof(int); i++) {
    cout << numbers[i] << endl;
  }

  return 0;
}