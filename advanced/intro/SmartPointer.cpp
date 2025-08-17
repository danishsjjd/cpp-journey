#include "SmartPointer.hpp"

SmartPointer::SmartPointer(int* ptr) {};
SmartPointer::~SmartPointer() {
  delete this->ptr;
  ptr = nullptr;
}