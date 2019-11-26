#pragma once
#include "view.h"
#include "queue.h"
#include "model.h"
#include "observe.h"

class CLIView : IListener, public IView {
 public:
  CLIView(QueueModel&);

  bool ProcessUserInput();

  void ProcessEvent(const Event&);
 private:
  QueueModel& _model;

  CLIView(const CLIView&) = delete;
  CLIView& operator=(const CLIView&) = delete;
};