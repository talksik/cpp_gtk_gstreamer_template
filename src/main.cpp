#include "gtkmm/button.h"
#include <gst/gst.h>
#include <gtkmm.h>
#include <iostream>

#include "main.h"

void test_gstreamer() {
  GstElement *pipeline = nullptr;
  GstBus *bus = nullptr;
  GstMessage *msg = nullptr;

  // building pipeline
  pipeline =
      gst_parse_launch("playbin "
                       "uri=https://www.freedesktop.org/software/gstreamer-sdk/"
                       "data/media/sintel_trailer-480p.webm",
                       nullptr);

  // start playing
  gst_element_set_state(pipeline, GST_STATE_PLAYING);

  // wait until error or EOS ( End Of Stream )
  bus = gst_element_get_bus(pipeline);
  msg = gst_bus_timed_pop_filtered(
      bus, GST_CLOCK_TIME_NONE,
      static_cast<GstMessageType>(GST_MESSAGE_ERROR | GST_MESSAGE_EOS));

  // free memory
  if (msg != nullptr)
    gst_message_unref(msg);
  gst_object_unref(bus);
  gst_element_set_state(pipeline, GST_STATE_NULL);
  gst_object_unref(pipeline);
}

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
  gst_init(&argc, &argv);
  test_gstreamer();

  auto app = Gtk::Application::create("org.gtkmm.examples.base");

  return app->make_window_and_run<MyWindow>(argc, argv);
}
