#include "include/controller.h"
#include <iostream>

AppController::AppController(QueueModel& model, CLIView& view) : _model(model), _view(view) {
  _view.AddListener(this);
}

void AppController::ProcessEvent(const Event& evt) {
  switch(evt.GetType()) {
    case EventType::UserPop: {
      _model.Pop();
      break;
    }
    case EventType::UserPush: {
      _model.Push(dynamic_cast<const UserPushEvent&>(evt).Value);
      break;
    }
    case EventType::UserShift: {
      _model.Shift();
      break;
    }
    default: break;
  }
}

int AppController::Run() {
  try {
    while (_view.ProcessUserInput());
  } catch (const std::exception& e) {
    std::cerr << "AppController has caught an exception: " << e.what() << std::endl;
    return 1;
  }
  return 0;
}
