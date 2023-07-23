#include <gtkmm.h>

class MyWindow : public Gtk::Window {
public:
  MyWindow();
  virtual ~MyWindow();

public:
  Gtk::Button button;
  void startCapture();
};
