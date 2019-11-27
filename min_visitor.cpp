#include "include/tostring_visitor.h"
#include "include/list.h"
#include <sstream>

std::string MinVisitor::Visit(List<std::string>& list) const {
  ListIterator<std::string> it(list);
  if (!it.HasNext()) {
    throw std::runtime_error("List is empty");
  }
  std::string ret = it.Next();
  while (it.HasNext()) {
    std::string t = it.Next();
    if (t.size() <= ret.size()) {
      ret = t;
    }
  }
  return ret;
}
