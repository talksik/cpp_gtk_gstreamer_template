#include "gtkmm/button.h"
#include <gtkmm.h>
#include <iostream>

#include "main.h"

MyWindow::MyWindow() {
  set_title("Basic application");

  Gtk::Button button("start capture");

  button.signal_clicked().connect(
      sigc::mem_fun(*this, &MyWindow::startCapture));

  set_default_size(800, 450);

  set_child(button);
}

MyWindow::~MyWindow() {}

void MyWindow::startCapture() { std::cout << "start capture" << std::endl; }

int main(int argc, char **argv) {
  auto app = Gtk::Application::create("org.gtkmm.examples.base");

  return app->make_window_and_run<MyWindow>(argc, argv);
}
