#pragma once
#include <unordered_set>
#include "event.h"

class IListener {
 public:
  virtual void ProcessEvent(const Event&) = 0;
  virtual ~IListener() = default;
};

class EventSource {
 public:
  EventSource();
  void AddListener(IListener*);
  void SendEvent(const Event&) const;
  virtual ~EventSource() = default;
 private:
  std::unordered_set<IListener*> _listeners;
};
