#include "rtcore.hpp"
#include "sphere.hpp"
#include "hittable.hpp"
#include "camera.hpp"


int main() {


    HittableList world;
    world.add(std::make_shared<Sphere>(point3(0,0,-1), 0.25));
    world.add(std::make_shared<Sphere>(point3(0,-100.5,-1), 100));

    Camera cam(world);
    cam.updateSampleCount(100);
    cam.render();

}