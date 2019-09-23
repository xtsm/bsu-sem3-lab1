#include "include/model.h"
#include "include/shift_visitor.h"
#include <sstream>

QueueModel::QueueModel() : _queue(), _lastAction() {}

std::string QueueModel::GetQueueString() const {
  std::ostringstream stream;
  stream << _queue;
  return stream.str();
}

std::string QueueModel::GetStatusString() const {
  std::ostringstream stream;
  stream << _lastAction << ", "
      << "size: " << _queue.Size();
  return stream.str();
}

void QueueModel::Push(const std::string& val) {
  _queue.Push(val);
  std::ostringstream stream;
  stream << "pushed \"" << val << "\"";
  _lastAction = stream.str();
  SendEvent(ModelUpdateEvent(GetQueueString(), GetStatusString()));
}

void QueueModel::Pop() {
  std::string val = _queue.Pop();
  std::ostringstream stream;
  stream << "popped \"" << val << "\"";
  _lastAction = stream.str();
  SendEvent(ModelUpdateEvent(GetQueueString(), GetStatusString()));
}

void QueueModel::Shift() {
  _queue.Accept(ShiftVisitor<Queue<std::string>>());
  std::ostringstream stream;
  stream << "shifted 1 left";
  _lastAction = stream.str();
  SendEvent(ModelUpdateEvent(GetQueueString(), GetStatusString()));
}
