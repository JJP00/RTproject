#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.hpp"
#include "material.hpp"
#include <atomic>
class camera
{
public:
    unsigned int seed;
    // imagen
    double aspect_ratio = 1.0;
    int image_width = 100;
    int samples_per_pixel = 10;
    int max_depth = 10;

    double vfov = 90;
    point3 lookfrom = point3(0, 0, 0);
    point3 lookat = point3(0, 0, -1);
    vec3 vup = vec3(0, 1, 0);

    double defocus_angle = 0;
    double focus_dist = 10;

    void
    render(const hittable &world, unsigned int &seed)
    {
        initialize();

        // std::cout
        //     << "P3\n"
        //    << image_width << " " << image_height << "\n255\n";

        std::vector<color> image(image_width * image_height);
        std::atomic<int> remaining_scanlines(image_height); // Atomic counter for scanlines

#pragma omp parallel for schedule(dynamic, 1) firstprivate(seed)
        for (int j = 0; j < image_height; j++)
        {
            for (int i = 0; i < image_width; i++)
            {
                color pixel_color(0, 0, 0);

                for (int sample = 0; sample < samples_per_pixel; sample++)
                {
                    ray r = get_ray(i, j, seed);
                    pixel_color += ray_color(r, max_depth, world);
                }
                int index = j * image_width + i;
                image[index] = pixel_color;
                // write_color(std::cout, pixel_samples_scale * pixel_color);
            }
            remaining_scanlines--;
#pragma omp critical
            {
                std::clog << "\rScanlines remaning: " << remaining_scanlines << ' ' << std::flush;
            }
        }

        std::clog << "\rDone.                 \n";

        std::cout << "P3\n"
                  << image_width << ' ' << image_height << "\n255\n";
        for (int j = 0; j < image_height; j++)
        {
            for (int i = 0; i < image_width; i++)
            {
                int index = j * image_width + i;
                write_color(std::cout, image[index], samples_per_pixel);
            }
        }
    }

private:
    int image_height;
    double pixel_samples_scale;
    point3 camera_center;
    point3 pixel00_loc;
    vec3 pixel_delta_u;
    vec3 pixel_delta_v;
    vec3 u, v, w;
    vec3 defocus_disk_u;
    vec3 defocus_disk_v;

    void initialize()
    {
        // calcular la altura de la imagen
        image_height = int(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;

        pixel_samples_scale = 1.0 / samples_per_pixel;

        // camera
        camera_center = lookfrom;
        auto theta = degrees_to_radians(vfov);
        auto h = std::tan(theta / 2);
        auto viewport_height = 2 * h * focus_dist;
        auto viewport_width = viewport_height * (double(image_width) / image_height);

        // vectores base de la camara

        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(vup, w));
        v = cross(w, u);

        // vectores del viewport

        auto viewport_u = viewport_width * u;
        auto viewport_v = viewport_height * -v;

        // calcular el delta horizontal como vertical

        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        // calcular coordenadas del pixel arriba izquierda
        auto viewport_upper_left = camera_center - (focus_dist * w) - viewport_u / 2 - viewport_v / 2;
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

        // calcular vectores base del disco
        auto defocus_radius = focus_dist * std::tan(degrees_to_radians(defocus_angle / 2));
        defocus_disk_u = u * defocus_radius;
        defocus_disk_v = v * defocus_radius;
    }

    ray get_ray(int i, int j, unsigned int &seed)
    {
        auto offset = sample_square(seed);
        auto pixel_sample = pixel00_loc + ((i + offset.x()) * pixel_delta_u) + ((j + offset.y()) * pixel_delta_v);

        auto ray_origin = (defocus_angle <= 0) ? camera_center : defocus_disk_sample(seed);
        auto ray_direction = pixel_sample - ray_origin;

        return ray(ray_origin, ray_direction);
    }

    point3 defocus_disk_sample(unsigned int &seed) const
    {
        auto p = random_in_unit_disk(seed);
        return camera_center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
    }

    vec3 sample_square(unsigned int &seed) const
    {
        // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
        return vec3(random_double(seed) - 0.5, random_double(seed) - 0.5, 0);
    }

    color ray_color(const ray &r, int depth, const hittable &world) const
    {
        if (depth <= 0)
            return color(0, 0, 0);

        hit_record rec;

        if (world.hit(r, interval(0.001, infinity), rec))
        {
            ray scattered;
            color attenuation;
            if (rec.mat->scatter(r, rec, attenuation, scattered, seed))
                return attenuation * ray_color(scattered, depth - 1, world);
            return vec3(0, 0, 0);
        }

        vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
    }
};

#endif