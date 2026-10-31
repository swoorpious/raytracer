#include "rtcore.hpp"
#include "sphere.hpp"
#include "hittable.hpp"
#include "camera.hpp"


int main(int argc, char* argv[]) {
    HittableList world;
    world.add(std::make_shared<Sphere>(point3(0,0,-1), 0.5));
    world.add(std::make_shared<Sphere>(point3(0,-100.5,-1), 100));

    Camera cam(world);
    // argv[1]: width of image
    // argv[2]: samples per pixel
    if (argc >= 2)
        cam.setImageWidth(atoi(argv[1]));
    if(argc == 3)
        cam.setSampleCount(atoi(argv[2]));

    cam.render();
}