#ifndef DIFFERENTIATION_H
#define DIFFERENTIATION_H

#include <functional>

class Differentiation
{
public:
    static double forwardDifference(
        std::function<double(double)> f,
        double x,
        double h
    );

    static double backwardDifference(
        std::function<double(double)> f,
        double x,
        double h
    );

    static double centralDifference(
        std::function<double(double)> f,
        double x,
        double h
    );
};

#endif
