#pragma once

#include <tobii/tobii.h>
#include <tobii/tobii_streams.h>
#include <utility>

class EyeTracker{
  float gazeX, gazeY;

  public:
    EyeTracker();
    ~EyeTracker();
    void gaze_point_callback(tobii_gaze_point_t const *gaze_point);
    void url_receiver(char const *url, void *user_data); 
    std::pair<float, float> update();

};
