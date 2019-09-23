#pragma once
#include "queue.h"
#include "observe.h"

class QueueModel : public EventSource {
 public:
  QueueModel();
  void Push(const std::string&);
  void Pop();
  void Shift();
 private:
  Queue<std::string> _queue;
  std::string _lastAction;

  std::string GetQueueString() const;
  std::string GetStatusString() const;

  QueueModel(const QueueModel&) = delete;
  QueueModel& operator=(const QueueModel&) = delete;
};
