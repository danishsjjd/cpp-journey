#pragma once

struct Position {
  int x = 0, y = 0;
};

class Rectangle {
 public:
  Rectangle() = default;
  Rectangle(int w, int h);
  Rectangle(int w, int h, Position pos);
  Rectangle(const Rectangle& source) = delete;
  ~Rectangle();

  int getWidth() const;
  int getHeight() const;

  void setWidth(int w);
  void setHeight(int h);

  static int getObjectCount();

 private:
  int width = 0, height = 0;
  Position position;

  static int objectCount;
};
