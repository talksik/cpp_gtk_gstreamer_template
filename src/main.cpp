#include "gtkmm/button.h"
#include <gtkmm.h>
#include <iostream>

class MyWindow : public Gtk::Window {
public:
  MyWindow();
};

MyWindow::MyWindow() {
  set_title("Basic application");

  Gtk::Button button("Hello World");
  button.signal_clicked().connect([] { std::cout << "Hello World\n"; });
  button.set_label("Hello World");

  set_default_size(800, 450);

  set_child(button);
}

int main(int argc, char **argv) {
  auto app = Gtk::Application::create("org.gtkmm.examples.base");
  return app->make_window_and_run<MyWindow>(argc, argv);
}
