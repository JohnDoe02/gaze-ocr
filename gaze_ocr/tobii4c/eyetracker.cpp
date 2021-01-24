#include <tobii/tobii.h>
#include <tobii/tobii_streams.h>
#include <assert.h>
#include <cstring>

#include<iostream>

#include"eyetracker.h"

void EyeTracker::gaze_point_callback(tobii_gaze_point_t const *gaze_point) {
    if (gaze_point->validity != TOBII_VALIDITY_VALID) return;

    gazeX = gaze_point->position_xy[0];
    gazeY = gaze_point->position_xy[1];
}

void EyeTracker::url_receiver(char const *url, void *user_data) {
    char *buffer = (char *) user_data;
    if (*buffer != '\0') return; // only keep first value

    if (strlen(url) < 256)
        strcpy(buffer, url);
}

EyeTracker::EyeTracker()
{
  tobii_error_t error = tobii_api_create(&api, NULL, NULL);
  assert(error == TOBII_ERROR_NO_ERROR);

  char url[256] = {0};
  error = tobii_enumerate_local_device_urls(api, url_receiver, url);
  assert(error == TOBII_ERROR_NO_ERROR && *url != '\0');

  error = tobii_device_create(api, url, &device);
  assert(error == TOBII_ERROR_NO_ERROR);

  error = tobii_gaze_point_subscribe(device, gaze_point_callback, (void*) this);
  assert(error == TOBII_ERROR_NO_ERROR);
}
EyeTracker::~EyeTracker()
{
  error = tobii_gaze_point_unsubscribe(device);
  assert(error == TOBII_ERROR_NO_ERROR);

  error = tobii_device_destroy(device);
  assert(error == TOBII_ERROR_NO_ERROR);

  error = tobii_api_destroy(api);
  assert(error == TOBII_ERROR_NO_ERROR);
}
std::pair<float, float> EyeTracker::update()
{
    error = tobii_wait_for_callbacks(1, &device);
    assert(error == TOBII_ERROR_NO_ERROR || error == TOBII_ERROR_TIMED_OUT);

    error = tobii_device_process_callbacks(device);
    assert(error == TOBII_ERROR_NO_ERROR);

    return {gazeX, gazeY};
}
