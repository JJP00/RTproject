#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <math.h>
#include <iostream>
#include <limits>
#include <memory>

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

// Common Headers

#include "color.hpp"
#include "interval.hpp"
#include "ray.hpp"
#include "vec3.hpp"

#endif