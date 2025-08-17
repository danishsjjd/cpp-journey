#include <iostream>
#include <sstream>

using namespace std;

int main() {
  string str = "Terminator 1, 1984";

  stringstream ss(str);

  string title;
  getline(ss, title, ',');
  int year;
  ss >> year;

  cout << "Title: " << title << " Year: " << year;

  return 0;
}