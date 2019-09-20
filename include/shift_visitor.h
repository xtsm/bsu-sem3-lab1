#pragma once
#include "visitor.h"
#include "queue.h"
#include <string>

template<class T>
class ShiftVisitor;

template<class T>
class ShiftVisitor<Queue<T>> : public IVisitor<Queue<T>> {
 public:
  ShiftVisitor(size_t shiftCount = 1) : _shiftCount(shiftCount) {}
  void Visit(Queue<std::string>& queue) const override {
    if (queue.IsEmpty()) {
      return;
    }
    for (size_t i = _shiftCount; i > 0; i--) {
      queue.Push(queue.Pop());
    }
  }
 private:
  size_t _shiftCount;
};
