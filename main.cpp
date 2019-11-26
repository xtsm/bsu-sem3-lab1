#include "include/model.h"
#include "include/cli_view.h"
#include "include/controller.h"

int main() {
  QueueModel model;
  CLIView view(model);
  AppController controller(model, view);
  return controller.Run();
}
