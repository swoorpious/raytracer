#include "rtcore.hpp"
#include "sphere.hpp"
#include "hittable.hpp"
#include "camera.hpp"
#include <filesystem>
#include <getopt.h>

void postRender(std::string& filename, std::shared_ptr<std::string> path);

int main(const int argc, char* argv[]) {
    static struct option long_options[] = {
            {"width", required_argument, 0, 'w'},
            {"samples-per-pixel", required_argument, 0, 's'},
            {"max-ray-bounces", required_argument, 0, 'b'},
            {"output", required_argument, 0, 'o'},
            {0, 0, 0, 0}
        };

    std::filesystem::create_directories(OUTPUT_PATH);

    HittableList world;
    world.add(std::make_shared<Sphere>(point3(0, 0, -1), 0.5));
    world.add(std::make_shared<Sphere>(point3(0, -100.5, -1), 100));
    Camera cam(world);

    // parse args
    std::string filename = "image"; // file will be image.ppm
    std::shared_ptr<std::string> path = getPathTo(std::string(filename) + ".ppm", EPathType::Output);
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
            filename = std::string(optarg); // preferred input is filename without the extension
            path = getPathTo(filename + ".ppm", EPathType::Output);
            break;

        default:
            return 1;
        }
    }


    std::ofstream file(path->c_str(), std::ios::out | std::ios::trunc);
    cam.setOutStream(file);
    cam.render();

    file.close();

    postRender(filename, path);

    return 0;
}


void postRender(std::string& filename, std::shared_ptr<std::string> path) {
    namespace fs = std::filesystem;
#ifdef __unix__
    std::shared_ptr<std::string> s = getPathTo("convertPpmToPng.sh", EPathType::Project);
    if (fs::exists(*s.get()) && fs::exists(*path.get())) {
        std::string cmd = "bash \"" + *s.get() + "\" \"" + *path.get() + "\" \"" +
            *getPathTo(filename, EPathType::Output).get() + ".png\"";

        if (!system(cmd.c_str())) {
            std::clog << "\nfilename: output/" << filename << ".png" << std::endl;
        }
        else {
            std::clog << "\nimage conversion failed;\n";
            std::clog << "filename: output/" << filename << ".ppm" << std::endl;
        }
    }

#else
    std::clog << "\nfilename: output/" << filename << ".ppm" << std::endl;
#endif
}
