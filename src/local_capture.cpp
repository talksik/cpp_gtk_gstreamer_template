
#include "local_capture.h"
#include "gst/gstbus.h"
#include "gst/gstelement.h"
#include "gst/gstelementfactory.h"
#include <iostream>

LocalCapture::LocalCapture() {
  std::cout << "initializing local capture" << std::endl;

  GstElement *video = gst_element_factory_make("v4l2src", "video");
  GstElement *videoconvert =
      gst_element_factory_make("videoconvert", "videoconvert");
  sink = gst_element_factory_make("appsink", "sink");

  // set callback for appsink
  g_object_set(G_OBJECT(sink), "emit-signals", TRUE, "sync", FALSE, nullptr);
  g_signal_connect(sink, "new-sample", G_CALLBACK(on_new_sample), this);

  if (!video || !videoconvert || !sink) {
    std::cerr << "failed to create elements" << std::endl;
    return;
  }

  m_pipeline = gst_pipeline_new("local_capture");

  gst_bin_add_many(GST_BIN(m_pipeline), video, videoconvert, sink, nullptr);
  if (!gst_element_link_many(video, videoconvert, sink, nullptr)) {
    g_printerr("Elements could not be linked.\n");
  }

  /* Start playing */
  gst_element_set_state(m_pipeline, GST_STATE_PAUSED);

  m_bus = gst_element_get_bus(m_pipeline);
  gst_bus_add_watch(
      m_bus,
      [](GstBus *bus, GstMessage *msg, gpointer data) {
        std::cout << "message type: " << GST_MESSAGE_TYPE(msg) << std::endl;

        switch (GST_MESSAGE_TYPE(msg)) {
        case GST_MESSAGE_ERROR: {
          GError *err;
          gchar *debug;
          gst_message_parse_error(msg, &err, &debug);
          g_printerr("Error: %s\n", err->message);
          g_error_free(err);
          g_free(debug);
          break;
        }
        case GST_MESSAGE_EOS:
          g_print("End of stream\n");
          break;
        default:
          break;
        }

        return (int)G_SOURCE_CONTINUE;
      },
      nullptr);

  std::cout << "local capture ready" << std::endl;
}

int LocalCapture::on_new_sample(GstElement *sink, gpointer data) {
  GstSample *sample;

  /* Retrieve the buffer */
  g_signal_emit_by_name(sink, "pull-sample", &sample);
  if (sample) {
    GstBuffer *buffer = gst_sample_get_buffer(sample);
    GstMapInfo map;
    gst_buffer_map(buffer, &map, GST_MAP_READ);
    std::cout << "received " << map.size << " bytes" << std::endl;

    gst_sample_unref(sample);
    return GST_FLOW_OK;
  }

  return GST_FLOW_ERROR;
}

void LocalCapture::start() {
  if (m_isRunning) {
    return;
  }

  std::cout << "starting local capture" << std::endl;
  m_isRunning = true;
  gst_element_set_state(m_pipeline, GST_STATE_PLAYING);
}

void LocalCapture::pause() {
  if (!m_isRunning) {
    return;
  }

  std::cout << "pausing local capture" << std::endl;
  m_isRunning = false;
  gst_element_set_state(m_pipeline, GST_STATE_PAUSED);
}
