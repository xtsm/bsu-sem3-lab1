#include "include/tostring_visitor.h"
#include "include/list.h"
#include <sstream>

std::string ToStringVisitor::Visit(List<std::string>& list) const {
  ListIterator<std::string> it(list);
  std::ostringstream ss;
  do {
    ss << it.Next();
    if (it.HasNext()) {
      ss << " ";
    }
  } while (it.HasNext());
  return ss.str();
}
