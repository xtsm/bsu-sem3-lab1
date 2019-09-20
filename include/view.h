#pragma once
#include <windows.h>
#include "queue.h"
#include "model.h"

class MainWindowView {
 public:
  MainWindowView(HINSTANCE, int, QueueModel&);

  HWND GetWindowHandle() const;
  LRESULT ProcessMessage(HWND, UINT, WPARAM, LPARAM);
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
