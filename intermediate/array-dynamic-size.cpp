#include <iostream>
using namespace std;

// Dynamic size array
int main() {
  int size = 5;
  int* numbers = new int[size];
  int entries = 0;

  while (true) {
    cout << "Number: ";

    cin >> numbers[entries];

    if (cin.fail()) {
      break;
    }

    if (entries > size) {
      size = entries * 2;
      int* tempNumbers = new int[size];
      for (int i = 0; i < entries; i++) {
        tempNumbers[i] = numbers[i];
      }

      delete[] numbers;
      numbers = tempNumbers;
    }

    entries++;
  }

  cout << "entries: " << entries << endl;

  for (int i = 0; i < entries; i++) {
    cout << numbers[i] << endl;
  }

  delete[] numbers;

  return 0;
}