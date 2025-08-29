#include "Rectangle.hpp"

#include <iostream>
#include <stdexcept>

Rectangle::Rectangle(int w, int h) {
  // TODO: it will not increment for the default constructor
  Rectangle::objectCount++;

  this->setWidth(w);
  this->setHeight(h);
}

Rectangle::Rectangle(int w, int h, Position pos) : Rectangle(w, h) {
  this->position = pos;
}

Rectangle::~Rectangle() {
  Rectangle::objectCount--;
  std::cout << "Rectangle destructor called" << std::endl;
}

void Rectangle::setWidth(int w) {
  if (w < 0) {
    throw std::invalid_argument("Width cannot be negative");
  }
  this->width = w;
}

int Rectangle::getWidth() const { return this->width; }

void Rectangle::setHeight(int h) {
  if (h < 0) {
    throw std::invalid_argument("Height cannot be negative");
  }

  this->height = h;
}

int Rectangle::getHeight() const { return this->height; }

// Rectangle::Rectangle(const Rectangle& other) {
//   std::cout << "It's always better to rely on default copy constructor"
//             << std::endl;
//   this->width = other.width;
//   this->height = other.height;
//   this->position = other.position;
// }

int Rectangle::objectCount = 0;

int Rectangle::getObjectCount() { return Rectangle::objectCount; }
