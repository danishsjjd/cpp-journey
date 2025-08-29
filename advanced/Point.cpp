#include "Point.hpp"

#include <ostream>

// TODO: make it inline
Point::Point(int x, int y) : x{x}, y{y} {}

bool Point::operator==(const Point& other) const {
  return this->x == other.x && this->y == other.y;
}

Point::operator int() const { return this->x + this->y; }

std::strong_ordering Point::operator<=>(const Point& other) const {
  if (auto cmp = this->x <=> other.x; cmp != 0) return cmp;
  return this->y <=> other.y;
}

std::ostream& operator<<(std::ostream& stream, const Point& point) {
  stream << "P(" << point.x << ", " << point.y << ")";
  return stream;
}
