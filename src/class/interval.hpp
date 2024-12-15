#ifndef INTERVAL_H
#define INTERVAL_H

#include "constants.hpp"

class interval
{
public:
    double min, max;

    interval() : min(+infinity), max(-infinity) {}

    interval(double min, double max) : min(min), max(max) {}

    double size() const
    {
        return max - min;
    }

    bool contains(double x)
    {
        return min <= x && x <= max;
    }

    bool surrounds(double x)
    {
        return min < x && x < max;
    }

    static const interval empty, universe;
};

const interval interval::empty = interval(+infinity, -infinity);
const interval interval::universe = interval(-infinity, +infinity);

#endif