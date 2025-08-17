#include <iostream>
using namespace std;

void bubbleSort(int *arr, size_t size, bool debug = true);

int main() {
  int myArr[] = {2, 1};

  bool debug = true;
  bubbleSort(myArr, size(myArr), debug);

  if (debug) {
    cout << endl << endl << endl;
  }

  for (size_t i = 0; i < size(myArr); i++) {
    cout << myArr[i] << " ";
  }

  cout << endl;

  return 0;
}

void swap(int arr[], int leftIndex, int rightIndex) {
  int temp = arr[leftIndex];

  arr[leftIndex] = arr[rightIndex];
  arr[rightIndex] = temp;
}

void bubbleSort(int *arr, size_t size, bool debug) {
  bool sorted = size <= 1;

  while (!sorted) {
    bool isReallySorted = true;

    if (debug) {
      for (size_t i = 0; i < size; i++) {
        cout << arr[i] << " ";
      }
      cout << endl;
    }

    for (size_t i = 1; i < size; i++) {
      int leftIndex = i - 1;
      int rightIndex = i;

      if (arr[leftIndex] > arr[rightIndex]) {
        swap(arr, leftIndex, rightIndex);

        isReallySorted = false;
      }

      int sizeAtInstance = i + 1;
      if (sizeAtInstance == size) {
        if (isReallySorted) {
          sorted = true;
        }
      }
    }
  }
}