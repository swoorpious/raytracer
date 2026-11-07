// copyright 2026 swaroop.

#include "camera.hpp"

#include "material.hpp"
#include "ray.hpp"


Camera::Camera(HittableList& world) : world(world) {}

void Camera::initialize() {
    image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    pixel_samples_scale = 1.0 / samples_per_pixel;

    camera_center = lookfrom;

    // viewport dimensions. vfov is the full vertical angle, so the half-angle is used.
    focal_length = (lookfrom - lookat).length();
    double theta = degreesToRadians(vfov);
    double h = std::tan(theta / 2);
    viewport_height = 2 * h * focal_length;
    viewport_width = viewport_height * (double(image_width) / image_height);

    // orthonormal basis for the camera frame: u = right, v = up, w = backward (camera looks along -w)
    w = unit_vector(lookfrom - lookat);
    u = unit_vector(cross(vup, w));
    v = cross(w, u);

    // vectors across the horizontal and down the vertical viewport edges
    viewport_u = viewport_width * u;
    viewport_v = viewport_height * -v;

    // pixel to pixel delta vectors
    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;

    // location of the upper left pixel
    viewport_upper_left = camera_center - (focal_length * w) - viewport_u / 2 - viewport_v / 2;
    pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
}

void Camera::render() {
    initialize();

    *outStrm << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    std::clog << "image width: " << image_width <<
        "\nimage height: " << image_height <<
        "\nmax ray bounces: " << ray_bounce_depth <<
        "\nsamples per pixel: " << samples_per_pixel << "\n\n";

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;

        for (int i = 0; i < image_width; i++) {
            color pixel_color(0, 0, 0);
            for (int k = 0; k < samples_per_pixel; k++) {
                ray t = getRay(i, j);
                pixel_color += rayColor(t, ray_bounce_depth);
            }
            writeColor(*outStrm, pixel_samples_scale * pixel_color);
        }
    }

    std::clog << "\rDone.                 \n";
}

// these setters only store values now; initialize() (called from render) derives the rest,
// so nothing can go stale regardless of the order you set things in.
void Camera::setSampleCount(int samples) {
    samples_per_pixel = samples;
}

void Camera::setImageWidth(int width) {
    image_width = width;
}

void Camera::setRayDepth(int depth) {
    ray_bounce_depth = depth;
}

void Camera::setOutStream(std::ofstream& strm) {
    outStrm = &strm;
}

void Camera::setMaxRayBounces(int bounces) {
    ray_bounce_depth = bounces;
}


// cpu shader stuff
color Camera::rayColor(const ray& r, int depth) {
    // if we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0) return color(0, 0, 0);

    HitRecord rec;
    if (world.hits(r, {0.001, infinity}, rec)) {
        ray scattered;
        color attenuation;

        if (rec.mat->scatter(r, rec, attenuation, scattered))
            return attenuation * rayColor(scattered, depth - 1); // new ray bounce

        return color(0, 0, 0);
    }

    vec3 unit_direction = unit_vector(r.getDirection());
    double a = 0.5 * (unit_direction.y() + 1.0);
    return (1.f - a) * color(1.0f, 1.f, 1.f) + a * color(0.5f, 0.7f, 1.f);
}

ray Camera::getRay(int i, int j) {
    point3 offset = sampleSquare();
    vec3 pixel_sample = pixel00_loc + ((i + offset.x()) * pixel_delta_u) + ((j + offset.y()) * pixel_delta_v);
    vec3 ray_direction = pixel_sample - camera_center;
    return ray(camera_center, ray_direction);
}

vec3 Camera::sampleSquare() const {
    return vec3(randomDouble() - 0.5, randomDouble() - 0.5, 0);
}