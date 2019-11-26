#pragma once
#include "model.h"
#include "view.h"
#include "observe.h"

class AppController : public IListener {
 public:
  AppController(QueueModel&, CLIView&);
  void ProcessEvent(const Event&);
  int Run();
 private:
  QueueModel& _model;
  CLIView& _view;
};
