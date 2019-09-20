#pragma once
#include "queue.h"

class QueueModel {
 public:
  QueueModel();
  std::string GetQueueString() const;
  std::string GetStatusString() const;
  void Push(const std::string&);
  void Pop();
 private:
  Queue<std::string> _queue;
  std::string _lastAction;

  QueueModel(const QueueModel&) = delete;
  QueueModel& operator=(const QueueModel&) = delete;
};
