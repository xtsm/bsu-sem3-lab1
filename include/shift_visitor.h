#pragma once
#include "visitor.h"
#include "queue.h"
#include <string>

template<class T>
class ShiftVisitor;

template<class T>
class ShiftVisitor<Queue<T>> : public IVisitor<Queue<T>> {
 public:
  void Visit(Queue<std::string>& queue) const override {
    if (queue.IsEmpty()) {
      return;
    }
    queue.Push(queue.Pop());
  }
};
