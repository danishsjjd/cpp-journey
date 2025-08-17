#pragma once

class SmartPointer {
 public:
  explicit SmartPointer(int* ptr) : ptr(ptr) {}
  ~SmartPointer() {
    delete ptr;  // Automatically delete the managed pointer
  }

 private:
  int* ptr;
};