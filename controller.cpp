#include "include/controller.h"
#include <iostream>

AppController::AppController(MainWindowView& view) : _view(view) {}

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
