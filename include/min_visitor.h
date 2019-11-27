#pragma once
#include "visitor.h"
#include <string>

template<class T> class List;

class MinVisitor : public IVisitor<List<std::string>, std::string> {
 public:
  MinVisitor() {}
  std::string Visit(List<std::string>& list) const override;
};
