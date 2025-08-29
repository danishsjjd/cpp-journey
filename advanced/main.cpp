#include <iostream>

#include "Point.hpp"
#include "Rectangle.hpp"

using namespace std;

int main() {
  // Because the copy constructor is deleted, we cannot create a copy of
  // Rectangle auto first = Rectangle();

  // const Rectangle first(10, 20, Position{5, 5});

  auto point1 = Point(1, 2);
  auto point2 = Point(1, 2);
  // Copy constructor (NEW)
  auto point3 = point1;
  // Assignment operator (EXISTING)
  // It's better to delete both copy & assignment operator if we want to delete
  // any.
  point3 = point2;

  strong_ordering result = point1 <=> point2;

  int myPointer = static_cast<int>(point3);

  cout << point1 << endl;
  cout << point2 << endl;

  cout << "(point1 >= point2): " << (point1 >= point2) << endl;

  return 0;
}