#include <iostream>
using namespace std;

int main() {
  size_t t = -1;  // It will overflow to the maximum value of size_t
  // This is because size_t is an unsigned type, so it wraps around

  string x = R"("Hello\fjakls world")";

  if (t == 18446744073709551615) {
    cout << "true" << endl;
  } else {
    cout << "false" << endl;
  }

  if (t == -1) {
    cout << "true" << endl;
  } else {
    cout << "false" << endl;
  }

  cout << t << endl;

  return 0;
}