#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.hpp"
#include "vec3.hpp"
#include "constants.hpp"

class sphere : public hittable
{
public:
    // static sphere
    sphere(const point3 &center, double radius, shared_ptr<material> mat) : center(center, vec3(0, 0, 0)), radius(std::fmax(0, radius)), mat(mat)
    {
    }
    // moving sphere
    sphere(const point3 &center, const point3 &center2, double radius, shared_ptr<material> mat) : center(center, center2 - center), radius(std::fmax(0, radius)), mat(mat)
    {
    }

    bool hit(const ray &r, interval ray_t, hit_record &rec) const override
    {
        point3 current_center = center.at(r.time());
        vec3 oc = current_center - r.origin();
        auto a = r.direction().lenth_squared();
        auto h = dot(r.direction(), oc);
        auto c = oc.lenth_squared() - radius * radius;

        auto discriminant = h * h - a * c;
        if (discriminant < 0)
            return false;

        auto sqrtd = std::sqrt(discriminant);

        auto root = (h - sqrtd) / a;
        if (!ray_t.surrounds(root))
        {
            root = (h + sqrtd) / a;
            if (!ray_t.surrounds(root))
                return false;
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        vec3 outward_normal = (rec.p - current_center) / radius;
        rec.set_face_normal(r, outward_normal);
        rec.mat = mat;

        return true;
    }

private:
    ray center;
    double radius;
    shared_ptr<material> mat;
};

#endif