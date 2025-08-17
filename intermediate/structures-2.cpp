#include <iostream>
using namespace std;

struct Point {
  int x;
  int y;
};

bool operator==(const Point& first, const Point& second) {
  return first.x == second.x && first.y == second.y;
}

ostream& operator<<(ostream& stream, const Point& point) {
  return stream << "(" << point.x << ", " << point.y << ")";
}

int main() {
  Point p1{1, 2};
  Point p2{1, 2};

  cout << p1 << endl;
  cout << p2 << endl;

  cout << (p1 == p2);

  return 0;
}