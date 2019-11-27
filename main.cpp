#include "include/list.h"
#include <string>
#include <iostream>

int main() {
  List<std::string> list;
  list.push_front("toad");
  list.push_front("dog");
  list.push_front("rabbit");
  list.push_front("dinosaur");
  std::cout << list.toString() << std::endl << list.min() << std::endl;
  list.push_front("cat");
  list.push_front("kangaroo");
  std::cout << list.toString() << std::endl << list.min() << std::endl;
  return 0;
}
