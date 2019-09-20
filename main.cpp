#include <windows.h>
#include <iostream>
#include "include/resource.h"
#include "include/queue.h"
#include "include/view.h"
#include "include/model.h"

int APIENTRY WinMain(
    HINSTANCE hInst,
    HINSTANCE,
    LPSTR,
    int cmdShow) {

  QueueModel model;
  MainWindowView view(hInst, cmdShow, model);

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
        if (IsDialogMessage(view.GetWindowHandle(), &message) == 0) {
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
