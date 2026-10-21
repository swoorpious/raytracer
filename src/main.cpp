#include "rtcore.hpp"
#include "sphere.hpp"
#include "hittable.hpp"


color ray_color(const ray& r, const Hittable& world) {
    HitRecord rec;
    if (world.hits(r, 0, infinity, rec)) {
        return 0.5 * (rec.normal + color(1,1,1));
    }
    
    vec3 unit_direction = unit_vector(r.getDirection());
    float a = 0.5 * unit_direction.y() + 1.0;
    return (1.f-a) * color(1.0f,1.f,1.f) + a * color(0.5f,0.7f,1.f);
}

int main() {

    float aspect_ratio = 16.0/9.0;
    int image_width = 1280;

    HittableList world;
    world.add(std::make_shared<Sphere>(point3(0,0,-1), 0.25));
    world.add(std::make_shared<Sphere>(point3(0,-100.5,-1), 100));
    
    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    float focal_length = 1.0;
    float viewport_height = 2.0;
    float viewport_width = viewport_height * (double(image_width)/image_height);
    point3 camera_center = point3(0, 0, 0);

    // calc the vectors across the horizontal and down the vertical viewport edges.
    vec3 viewport_u = vec3(viewport_width, 0, 0);
    vec3 viewport_v = vec3(0, -viewport_height, 0);

    // calc the horizontal and vertical delta vectors from pixel to pixel.
    vec3 pixel_delta_u = viewport_u / image_width;
    vec3 pixel_delta_v = viewport_v / image_height;

    // calc the location of the upper left pixel.
    vec3 viewport_upper_left = camera_center
                             - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    vec3 pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    
    // render logic
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' '
            << std::flush;
        for (int i = 0; i < image_width; i++) {
            point3 pixelij_loc = pixel00_loc + i * pixel_delta_u + j * pixel_delta_v;
            vec3 ray_direction = pixelij_loc - camera_center;
            ray r(camera_center, ray_direction);

            color pixel_color = ray_color(r, world);
            writeColor(std::cout, pixel_color);
        }
    }

    std::clog << "\rDone.                 \n";
}