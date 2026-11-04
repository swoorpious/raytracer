// copyright 2026 swaroop.

#include "camera.hpp"
#include "ray.hpp"


Camera::Camera(HittableList& world) : world(world)
{
    focal_length = 1.0;
    camera_center = point3(0, 0, 0);
    setImageWidth(image_width);
    setSampleCount(samples_per_pixel);
}

void Camera::render() {
    *outStrm << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    std::clog << "image width: " << image_width <<
        "\nimage height: " << image_height <<
        "\nmax ray bounces: " << ray_bounce_depth <<
        "\nsamples per pixel: " << samples_per_pixel << '\n\n';

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

void Camera::setSampleCount(int samples) {
    samples_per_pixel = samples;
    pixel_samples_scale = 1.f / samples;
}

void Camera::setImageWidth(int width) {
    image_width = width;
    image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;
    viewport_height = 2.0;
    viewport_width = viewport_height * (double(image_width)/image_height);
        viewport_u = vec3(viewport_width, 0, 0);
    viewport_v = vec3(0, -viewport_height, 0);

    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;

    viewport_upper_left = camera_center
                             - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

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
    if (depth <= 0) return color(0,0,0);

    HitRecord rec;
    if (world.hits(r, {0.001, infinity}, rec)) {
        vec3 direction = random_on_hemisphere(rec.normal); // random new ray bounce direction
        return 0.5 * rayColor(ray(rec.p, direction), depth - 1); // new ray bounce
    }

    vec3 unit_direction = unit_vector(r.getDirection());
    float a = 0.5 * (unit_direction.y() + 1.0);
    return (1.f-a) * color(1.0f,1.f,1.f) + a * color(0.5f,0.7f,0.8f);
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
