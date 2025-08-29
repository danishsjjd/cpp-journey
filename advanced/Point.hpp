#pragma once

#include <compare>
#include <ostream>

class Point {
 public:
  Point() = default;
  Point(int x, int y);

  bool operator==(const Point& other) const;
  std::strong_ordering operator<=>(const Point& other) const;
  explicit operator int() const;

 private:
  int x = 0;
  int y = 0;
  friend std::ostream& operator<<(std::ostream& stream, const Point& point);
};

std::ostream& operator<<(std::ostream& stream, const Point& point);
