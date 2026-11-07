#include "rtcore.hpp"
#include "hittable/sphere.hpp"
#include "hittable/hittable.hpp"
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
    const auto startTime = std::chrono::high_resolution_clock::now();

    HittableList world;
    Camera cam(world);

    auto ground_material = std::make_shared<Lambertian>(color(0.5, 0.5, 0.5));
    world.add(std::make_shared<Sphere>(point3(0, -1000, 0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = randomDouble();
            point3 center(a + 0.9 * randomDouble(), 0.2, b + 0.9 * randomDouble());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                std::shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = std::make_shared<Lambertian>(albedo);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
                else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = randomDouble(0, 0.5);
                    sphere_material = std::make_shared<Metal>(albedo, fuzz);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
                else {
                    // glass
                    sphere_material = std::make_shared<Glass>(1.5);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = std::make_shared<Glass>(1.5);
    world.add(std::make_shared<Sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<Lambertian>(color(0.4, 0.2, 0.1));
    world.add(std::make_shared<Sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<Metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(std::make_shared<Sphere>(point3(4, 1, 0), 1.0, material3));

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

    // position cam
    cam.vfov = 20;
    cam.lookfrom = point3(13, 2, 3);
    cam.lookat = point3(0, 0, 0);
    cam.vup = vec3(0, 1, 0);

    cam.defocus_angle = 0.6;
    cam.focus_dist = 10.0;

    cam.render();

    file.close();

    postRender(filename, path);
    const auto endTime = std::chrono::high_resolution_clock::now();
    auto totalSeconds = std::chrono::duration_cast<std::chrono::seconds>(
        endTime - startTime
    ).count();

    auto hours = totalSeconds / 3600;
    auto minutes = (totalSeconds % 3600) / 60;
    auto seconds = totalSeconds % 60;

    std::clog << "\n\ntotal execution time: "
        << hours << "h "
        << minutes << "m "
        << seconds << "s\n"
        << std::endl;

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
