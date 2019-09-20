#include <windows.h>
#include "include/model.h"
#include "include/view.h"
#include "include/controller.h"

int APIENTRY WinMain(
    HINSTANCE hInst,
    HINSTANCE,
    LPSTR,
    int cmdShow) {
  QueueModel model;
  MainWindowView view(hInst, cmdShow, model);
  AppController controller(view);
  return controller.Run();
}
