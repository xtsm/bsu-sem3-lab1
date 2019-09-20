#include <sstream>
#include "include/view.h"
#include "include/resource.h"

char* MainWindowView::_className = nullptr;
char* MainWindowView::_title = nullptr;

MainWindowView::MainWindowView(HINSTANCE hInst, int cmdShow, QueueModel& model) : 
    appInstance(hInst),
    mainWindow(0),
    queueLabel(0),
    statusLabel(0),
    elementEdit(0),
    pushButton(0),
    popButton(0),
    model(model)
{
  if (_className == nullptr) {
    _className = new char[256];
    _title = new char[256];
    LoadString(appInstance, IDS_MAINWINDOWCLASSNAME, _className, 256);
    LoadString(appInstance, IDS_MAINWINDOWTITLE, _title, 256);

    WNDCLASSEX wc;
    wc.cbSize = sizeof(wc);
    wc.style = 0;
    wc.lpfnWndProc = &WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = appInstance;
    wc.hIcon = 0;
    wc.hCursor = LoadCursor(0, IDC_ARROW);
    wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
    wc.lpszMenuName = 0;
    wc.lpszClassName = _className;
    wc.hIconSm = 0;
    RegisterClassEx(&wc);
  }
  DWORD windowStyle = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION;
  mainWindow = CreateWindowEx(0, _className, _title, windowStyle, 400, 300, 134, 160, 0, 0, appInstance, this);
  ShowWindow(mainWindow, cmdShow);
  UpdateWindow(mainWindow);
}

HWND MainWindowView::GetWindowHandle() const {
  return mainWindow;
}

LRESULT MainWindowView::ProcessMessage(HWND window, UINT message, WPARAM wp, LPARAM lp) {
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
          model.Push(newElement);

          SetWindowText(statusLabel, model.GetStatusString().c_str());
          SetWindowText(queueLabel, model.GetQueueString().c_str());
          return 0;
        }
        case IDC_POP_BUTTON: {
          model.Pop();

          SetWindowText(statusLabel, model.GetStatusString().c_str());
          SetWindowText(queueLabel, model.GetQueueString().c_str());
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

LRESULT CALLBACK MainWindowView::WndProc(HWND window, UINT message, WPARAM wp, LPARAM lp) {
  MainWindowView* viewPtr;
  if (message == WM_CREATE) {
    viewPtr = reinterpret_cast<MainWindowView*>(reinterpret_cast<LPCREATESTRUCT>(lp)->lpCreateParams);
    SetWindowLongPtr(window, GWLP_USERDATA, reinterpret_cast<LONG>(viewPtr));
  } else {
    viewPtr = reinterpret_cast<MainWindowView*>(GetWindowLongPtr(window, GWLP_USERDATA));
  }
  return viewPtr->ProcessMessage(window, message, wp, lp);
}
