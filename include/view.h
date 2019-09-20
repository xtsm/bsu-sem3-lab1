#pragma once
#include <windows.h>
#include "queue.h"

class MainWindowView {
 public:
  MainWindowView(HINSTANCE, int);

  HWND GetWindowHandle() const;
  LRESULT ProcessMessage(HWND, UINT, WPARAM, LPARAM);
 private:
  static char* _className;
  static char* _title;
  static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

  HINSTANCE appInstance;
  HWND mainWindow;
  HWND queueLabel, statusLabel;
  HWND elementEdit;
  HWND pushButton, popButton;
  Queue<std::string> queue;

  MainWindowView(const MainWindowView&) = delete;
  MainWindowView& operator=(const MainWindowView&) = delete;
};
