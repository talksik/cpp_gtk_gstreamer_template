#pragma once

#include "local_capture.h"
#include <gtkmm.h>

class MyWindow : public Gtk::Window {
public:
  MyWindow();
  virtual ~MyWindow();

public:
  Gtk::Button button;
  void toggleCapture();

private:
  LocalCapture *m_localCapture;
};
