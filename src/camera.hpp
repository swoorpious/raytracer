// copyright 2026 swaroop.

#ifndef CAMERA_H
#define CAMERA_H
#include <core.hpp>
#include "hittable.hpp"


class ray;

class Camera {
public:
    Camera(HittableList& world);

    float aspect_ratio = 16.0/9.0;
    int samples_per_pixel = 10;
    
    void render();
    void updateSampleCount(int samples);
    
private:
    color rayColor(const ray& r);
    ray getRay(int i, int j);
    
    inline vec3 sampleSquare()const;

    int image_width;
    int image_height;
    
    float focal_length;
    float viewport_width;
    float viewport_height;
    point3 camera_center;

    vec3 viewport_u;
    vec3 viewport_v;
    vec3 pixel_delta_u;
    vec3 pixel_delta_v;
    double pixel_samples_scale;

    vec3 viewport_upper_left;
    vec3 pixel00_loc;

    HittableList& world;

};



#endif //CAMERA_H
