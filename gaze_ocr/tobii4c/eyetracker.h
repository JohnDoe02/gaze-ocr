#pragma once

#include <tobii/tobii.h>
#include <tobii/tobii_streams.h>
#include <utility>

class EyeTracker{
  tobii_error_t error;
  tobii_api_t *api;
  tobii_device_t *device;

  float gazeX, gazeY;

private:
  static void url_receiver(char const *url, void *user_data); 
  static void gaze_point_callback(tobii_gaze_point_t const *gaze_point, void *user_data)
  {
    ((EyeTracker*) user_data)->gaze_point_callback(gaze_point);
  }

public:
  EyeTracker();
  ~EyeTracker();
  void gaze_point_callback(tobii_gaze_point_t const *gaze_point);
  std::pair<float, float> update();
};
