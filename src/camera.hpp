// copyright 2026 swaroop.

#ifndef CAMERA_H
#define CAMERA_H
#include <core.hpp>
#include "hittable/hittable.hpp"


class ray;

class Camera {
public:
    Camera(HittableList& world);

    float aspect_ratio = 16.0 / 9.0;
    int samples_per_pixel = 10;
    int ray_bounce_depth = 50;

    double vfov = 90.0;                     // vertical field of view, in degrees
    point3 lookfrom = point3(0, 0, 0);
    point3 lookat = point3(0, 0, -1);
    vec3 vup = vec3(0, 1, 0);               // camera-relative "up" direction
    double defocus_angle = 0;               // variation angle of rays through each pixel
    double focus_dist = 10;                 // distance from camera lookfrom point to plane of perfect focus

    void render();
    void setSampleCount(int samples);
    void setImageWidth(int width);
    void setRayDepth(int depth);
    void setOutStream(std::ofstream& strm);
    void setMaxRayBounces(int bounces);

private:
    void initialize();
    color rayColor(const ray& r, int depth);
    ray getRay(int i, int j);

    inline vec3 sampleSquare() const;
    point3 defocusDiskSample() const;

private:
    int image_width = 400;
    int image_height;

    double focal_length;
    double viewport_width;
    double viewport_height;
    point3 camera_center;

    // camera frame basis vectors
    vec3 u, v, w;
    vec3 defocus_disk_u; // defocus disk horizontal radius
    vec3 defocus_disk_v; // defocus disk vertical radius

    vec3 viewport_u;
    vec3 viewport_v;
    vec3 pixel_delta_u;
    vec3 pixel_delta_v;
    double pixel_samples_scale;

    vec3 viewport_upper_left;
    vec3 pixel00_loc;

    HittableList& world;
    std::ofstream* outStrm = nullptr;
};


#endif //CAMERA_H
