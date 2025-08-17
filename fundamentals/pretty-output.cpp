#include <iomanip>
#include <iostream>

using namespace std;

const int COLUMN_WIDTH = 10;

int main() {
  cout << left << setw(COLUMN_WIDTH) << "Course" << setw(COLUMN_WIDTH)
       << "Students" << left << endl
       << left << setw(COLUMN_WIDTH) << "C++" << setw(COLUMN_WIDTH) << right
       << "100" << left << endl
       << left << setw(COLUMN_WIDTH) << "JavaScript" << setw(COLUMN_WIDTH)
       << right << "5" << left << endl;

  return 0;
}