#include <fstream>
#include <iostream>
using namespace std;

int main() {
  ofstream file;

  file.open("data.txt");

  if (file.is_open()) {
    file << "title,author\n"
         << "terminator,random\n"
         << "terminator2.0,some dude\n";
  }

  file.close();
  cout << 'done';

  return 0;
}