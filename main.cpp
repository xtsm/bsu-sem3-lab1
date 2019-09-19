#include <windows.h>
#include <iostream>
#include <sstream>
#include "include/resource.h"
#include "include/queue.h"

HINSTANCE appInstance;
HWND mainWindow;
HWND queueLabel, statusLabel;
HWND elementEdit;
HWND pushButton, popButton;
Queue<std::string> queue;

LRESULT CALLBACK MainWindowProc(HWND window, UINT message, WPARAM wp, LPARAM lp) {
  switch (message) {
    case WM_CLOSE: {
      PostQuitMessage(0);
      return 0;
    }
    case WM_CREATE: {
      elementEdit = CreateWindowEx(0, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL, 4, 4, 120, 24, window, 0, appInstance, 0);
      pushButton = CreateWindowEx(0, "BUTTON", "Push", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_DEFPUSHBUTTON, 4, 36, 56, 24, window, reinterpret_cast<HMENU>(IDC_PUSH_BUTTON), appInstance, 0);
      popButton = CreateWindowEx(0, "BUTTON", "Pop", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_DEFPUSHBUTTON, 68, 36, 56, 24, window, reinterpret_cast<HMENU>(IDC_POP_BUTTON), appInstance, 0);
      queueLabel = CreateWindowEx(0, "STATIC", "[]", WS_CHILD | WS_VISIBLE | SS_CENTER, 4, 68, 120, 24, window, 0, appInstance, 0);
      statusLabel = CreateWindowEx(0, "STATIC", "size: 0", WS_CHILD | WS_VISIBLE | SS_CENTER, 4, 100, 120, 24, window, 0, appInstance, 0);
      return 0;
    }
    case WM_COMMAND: {
      switch(LOWORD(wp)) {
        case IDC_PUSH_BUTTON: {
          size_t sz = GetWindowTextLength(elementEdit);
          std::string newElement(sz + 1, 0);
          GetWindowText(elementEdit, newElement.data(), sz + 1);
          newElement.resize(sz);
          queue.Push(newElement);

          std::ostringstream stream;
          stream << "Inserted " << newElement << ", size: " << queue.Size();
          SetWindowText(statusLabel, stream.str().c_str());

          stream.str(std::string());
          stream.clear();
          stream << queue;
          SetWindowText(queueLabel, stream.str().c_str());
          return 0;
        }
        case IDC_POP_BUTTON: {
          std::string newElement = queue.Pop();

          std::ostringstream stream;
          stream << "Deleted " << newElement << ", size: " << queue.Size();
          SetWindowText(statusLabel, stream.str().c_str());

          stream.str(std::string());
          stream.clear();
          stream << queue;
          SetWindowText(queueLabel, stream.str().c_str());
          return 0;
        }
        default: {
          return DefWindowProc(window, message, wp, lp);
        }
      }
    }
    default: {
      return DefWindowProc(window, message, wp, lp);
    }
  }
}

int APIENTRY WinMain(
    HINSTANCE hInst,
    HINSTANCE,
    LPSTR,
    int cmdShow) {
  appInstance = hInst;

  char windowClassName[256];
  char windowTitle[256];
  LoadString(appInstance, IDS_MAINWINDOWCLASSNAME, windowClassName, 256);
  LoadString(appInstance, IDS_MAINWINDOWTITLE, windowTitle, 256);

  WNDCLASSEX wc;
  wc.cbSize = sizeof(wc);
  wc.style = 0;
  wc.lpfnWndProc = &MainWindowProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = appInstance;
  wc.hIcon = 0;
  wc.hCursor = LoadCursor(0, IDC_ARROW);
  wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
  wc.lpszMenuName = 0;
  wc.lpszClassName = windowClassName;
  wc.hIconSm = 0;
  RegisterClassEx(&wc);

  DWORD windowStyle = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION;

  mainWindow = CreateWindowEx(0, windowClassName, windowTitle, windowStyle, 400, 300, 134, 160, 0, 0, appInstance, 0);
  ShowWindow(mainWindow, cmdShow);
  UpdateWindow(mainWindow);

  int retCode = 1;
  while (true) {
    MSG message;
    bool loopQuit = false;
    switch (GetMessage(&message, 0, 0, 0)) {
      case -1: {
        std::cerr << "GetMessage returned -1" << std::endl;
        loopQuit = true;
        break;
      }
      case 0: {
        retCode = message.wParam;
        loopQuit = true;
        break;
      }
      default: {
        if (IsDialogMessage(mainWindow, &message) == 0) {
          TranslateMessage(&message);
          DispatchMessage(&message);
        }
      }
    }
    if (loopQuit) {
      break;
    }
  }

  return retCode;
}
