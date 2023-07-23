#include "gtkmm/button.h"
#include <glib.h>
#include <gst/gst.h>
#include <gtkmm.h>
#include <iostream>

#include "gtkmm/widget.h"
#include "local_capture.h"

#include "main.h"

MyWindow::MyWindow() {
  set_title("flowy");

  m_localCapture = new LocalCapture();

  //GtkWidget *area;
  // g_object_get(m_localCapture->gtksink, "widget", &area, NULL);
  // Gtk::Widget *widget = Glib::wrap(area);
  // set_child(*widget);

  Gtk::Button button("start capture");
  button.signal_clicked().connect(
      sigc::mem_fun(*this, &MyWindow::toggleCapture));
  set_default_size(800, 450);
  set_child(button);
}

MyWindow::~MyWindow() {}

void MyWindow::toggleCapture() {
  if (m_localCapture->isRunning()) {
    m_localCapture->pause();
    button.set_label("start capture");
  } else {
    m_localCapture->start();
    button.set_label("stop capture");
  }
}

int main(int argc, char **argv) {
  gst_init(&argc, &argv);

  auto app = Gtk::Application::create("live.flowy.client");

  return app->make_window_and_run<MyWindow>(argc, argv);
}
