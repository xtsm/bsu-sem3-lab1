#pragma once
#include <windows.h>
#include "queue.h"
#include "model.h"
#include "observe.h"

class MainWindowView : public EventSource, IListener {
 public:
  MainWindowView(HINSTANCE, int, QueueModel&);

  HWND GetWindowHandle() const;
  LRESULT ProcessMessage(HWND, UINT, WPARAM, LPARAM);
  void ProcessEvent(const Event&);
 private:
  static char* _className;
  static char* _title;
  static LRESULT CALLBACK _WndProc(HWND, UINT, WPARAM, LPARAM);

  HINSTANCE _appInstance;
  HWND _mainWindow;
  HWND _queueLabel, _statusLabel;
  HWND _elementEdit;
  HWND _pushButton, _popButton;
  QueueModel& _model;

  MainWindowView(const MainWindowView&) = delete;
  MainWindowView& operator=(const MainWindowView&) = delete;
};
