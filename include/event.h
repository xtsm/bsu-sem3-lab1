#pragma once
#include <string>

enum class EventType {
  Empty,
  UserPop,
  UserPush,
  UserShift,
  ModelUpdate
};

struct Event {
  virtual EventType GetType() const = 0;
  virtual ~Event() = default;
};

struct UserPopEvent : public Event {
  EventType GetType() const override {
    return EventType::UserPop;
  }
};

struct UserShiftEvent : public Event {
  EventType GetType() const override {
    return EventType::UserShift;
  }
};

struct UserPushEvent : public Event {
  UserPushEvent(const std::string& value) : Value(value) {}
  EventType GetType() const override {
    return EventType::UserPush;
  }
  std::string Value;
};

struct ModelUpdateEvent : public Event {
  ModelUpdateEvent(const std::string& queue, const std::string& status) : QueueString(queue), StatusString(status) {}
  EventType GetType() const override {
    return EventType::ModelUpdate;
  }
  std::string QueueString;
  std::string StatusString;
};
