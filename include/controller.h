#pragma once
#include "view.h"

class AppController {
 public:
  AppController(MainWindowView&);
  int Run();
 private:
  MainWindowView& _view;
};
