#pragma once
#include "visitor.h"
#include <string>

template<class T> class List;

class ToStringVisitor : public IVisitor<List<std::string>, std::string> {
 public:
  ToStringVisitor() {}
  std::string Visit(List<std::string>& list) const override;
};
