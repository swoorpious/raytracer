#include "rtcore.hpp"
#include "sphere.hpp"
#include "hittable.hpp"
#include "camera.hpp"
#include <filesystem>
#include <getopt.h>


int main(const int argc, char* argv[]) {
    static struct option long_options[] = {
    {"width",             required_argument, 0, 'w'},
    {"samples-per-pixel", required_argument, 0, 's'},
    {"max-ray-bounces",   required_argument, 0, 'b'},
    {"output",            required_argument, 0, 'o'},
    {0, 0, 0, 0}
    };

    std::filesystem::create_directories(OUTPUT_PATH);
    
    HittableList world;
    world.add(std::make_shared<Sphere>(point3(0,0,-1), 0.5));
    world.add(std::make_shared<Sphere>(point3(0,-100.5,-1), 100));
    Camera cam(world);

    // parse args
    const char* filename = "image.ppm";
    std::shared_ptr<std::string> path = getPathTo(filename);
    int opt;
    int option_index = 0;
    while ((opt = getopt_long(argc, argv, "w:s:b:o:", long_options, &option_index)) != -1) {
        switch (opt) {
        case 'w':
            cam.setImageWidth(std::atoi(optarg));
            break;

        case 's':
            cam.setSampleCount(std::atoi(optarg));
            break;

        case 'b':
            cam.setMaxRayBounces(std::atoi(optarg));
            break;

        case 'o':
            filename = optarg;
            path = getPathTo(optarg);
            break;

        default:
            return 1;
        }
    }

    std::ofstream file(path->c_str(), std::ios::out | std::ios::trunc);
    std::clog << "filename: output/" << filename << std::endl;
    cam.setOutStream(file);
    cam.render();
    
    file.close();
    return 0;
}