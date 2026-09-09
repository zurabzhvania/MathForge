#ifndef APPLICATIONS_H
#define APPLICATIONS_H

#include <functional>

namespace Applications
{
    double averageValue(
        std::function<double(double)> f,
        double a,
        double b,
        int n
    );

    double arcLength(
        std::function<double(double)> f,
        double a,
        double b,
        int n,
        double h
    );
}

#endif
