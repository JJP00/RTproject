#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <math.h>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>
#include <random>

// c++ std usings

using std::make_shared;
using std::shared_ptr; // estructura de dato que tiene en cuanta cuantas referencias se le hace, por lo tanto, lleva un conteo que sirve para poder borrar el espacio sin riesgo

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degrees_to_radians(double degrees)
{
    return degrees * pi / 180.0;
}

inline double random_double(unsigned int &seed)
{
    static thread_local std::mt19937 generator(seed);
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    return distribution(generator);
}

// inline double random_double()
// {
//     return std::rand() / (RAND_MAX + 1.0);
// }

// inline double random_double(double min, double max)
// {
//     return min + (max - min) * random_double();
// }

inline double random_double(double min, double max, unsigned int &seed)
{
    static thread_local std::mt19937 generator(seed);
    std::uniform_real_distribution<double> distribution(min, max);
    return distribution(generator);
}

inline double clamp(double x, double min, double max)
{
    if (x < min)
        return min;
    if (x > max)
        return max;
    return x;
}

// Common Headers

#include "color.hpp"
#include "interval.hpp"
#include "ray.hpp"
#include "vec3.hpp"

#endif