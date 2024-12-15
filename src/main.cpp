#include "./class/constants.hpp"

#include "./class/hittable.hpp"
#include "./class/hittables.hpp"
#include "./class/sphere.hpp"
#include "./class/camera.hpp"

int main()
{
    // mundo

    hittable_list world;

    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 100;

    cam.render(world);
}