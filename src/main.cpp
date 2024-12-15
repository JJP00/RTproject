#include "./class/constants.hpp"

#include "./class/hittable.hpp"
#include "./class/hittables.hpp"
#include "./class/sphere.hpp"
#include "./class/material.hpp"
#include "./class/camera.hpp"

int main()
{
    // mundo

    hittable_list world;

    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    auto material_left = make_shared<metal>(color(0.8, 0.8, 0.8), 0.5);
    auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 0.1);

    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100, material_ground));
    world.add(make_shared<sphere>(point3(0, 0, -1.2), 0.5, material_center));
    world.add(make_shared<sphere>(point3(-1.0, 0, -1.0), 0.5, material_left));
    world.add(make_shared<sphere>(point3(1.0, 0, -1.0), 0.5, material_right));

    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;

    cam.render(world);
}