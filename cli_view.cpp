#include "include/cli_view.h"
#include "include/resource.h"
#include <iostream>

CLIView::CLIView(QueueModel& model) : 
    _model(model)
{
  _model.AddListener(this);
}

void CLIView::ProcessEvent(const Event& evt) {
  if (evt.GetType() == EventType::ModelUpdate) {
    std::cout << "Status: " << dynamic_cast<const ModelUpdateEvent&>(evt).StatusString << std::endl;
    std::cout << "Queue: " << dynamic_cast<const ModelUpdateEvent&>(evt).QueueString << std::endl;
  }
}

bool CLIView::ProcessUserInput() {
  std::cout << "Choose action:\n 1. Push\n 2. Pop\n 3. Shift\n 4. Exit\n> ";
  int cmd;
  if (!(std::cin >> cmd)) {
    std::cout << std::endl;
    return false;
  }
  switch (cmd) {
    case 1: {
      std::string el;
      std::cout << "Enter element:\n> ";
      std::cin >> el;
      SendEvent(UserPushEvent(el));
      break;
    }
    case 2: {
      SendEvent(UserPopEvent());
      break;
    }
    case 3: {
      SendEvent(UserShiftEvent());
      break;
    }
    case 4: {
      return false;
    }
  }
  return true;
}
