#ifndef LIMITS_H
#define LIMITS_H

#include <functional>

class Limits
{
public:
    static double leftLimit(
        std::function<double(double)> f,
        double a,
        double h
    );

    static double rightLimit(
        std::function<double(double)> f,
        double a,
        double h
    );
};

#endif
