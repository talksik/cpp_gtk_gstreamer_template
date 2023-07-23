#pragma once

#include <gst/gst.h>

class LocalCapture {
public:
  LocalCapture();
  void start();
  void pause();
  ~LocalCapture() {
    gst_object_unref(m_bus);
    gst_element_set_state(m_pipeline, GST_STATE_NULL);
    gst_object_unref(m_pipeline);
  }
  bool isRunning() const { return m_isRunning; }
  GstElement *gtksink;

private:
  bool m_isRunning;
  gboolean bus_watch(GMainLoop *loop);
  GstElement *m_pipeline;
  GstBus *m_bus;
};
