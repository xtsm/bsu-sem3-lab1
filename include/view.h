#pragma once
#include "observe.h"

class IView : public EventSource {
 public:
  virtual bool ProcessUserInput() = 0;
  virtual ~IView() = default;
};
