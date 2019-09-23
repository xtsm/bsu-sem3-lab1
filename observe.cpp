#include "include/observe.h"
#include <iostream>

EventSource::EventSource() : _listeners() {}

void EventSource::AddListener(IListener* ptr) {
  _listeners.insert(ptr);
}

void EventSource::SendEvent(const Event& evt) const {
  for (IListener* i : _listeners) {
    i->ProcessEvent(evt);
  }
}
