#include "include/controller.h"
#include <iostream>

AppController::AppController(QueueModel& model, MainWindowView& view) : _model(model), _view(view) {
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
  int retCode = 1;
  while (true) {
    MSG message;
    bool loopQuit = false;
    switch (GetMessage(&message, 0, 0, 0)) {
      case -1: {
        std::cerr << "GetMessage returned -1" << std::endl;
        loopQuit = true;
        break;
      }
      case 0: {
        retCode = message.wParam;
        loopQuit = true;
        break;
      }
      default: {
        if (IsDialogMessage(_view.GetWindowHandle(), &message) == 0) {
          TranslateMessage(&message);
          DispatchMessage(&message);
        }
      }
    }
    if (loopQuit) {
      break;
    }
  }

  return retCode;
}
