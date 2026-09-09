#ifndef INTEGRATION_H
#define INTEGRATION_H

#include <functional>

class Integration
{
public:
    static double leftRiemann(
        std::function<double(double)> f,
        double a,
        double b,
        int n
    );

    static double rightRiemann(
        std::function<double(double)> f,
        double a,
        double b,
        int n
    );
    static double trapezoidal(
        std::function<double(double)> f,
        double a,
        double b,
        int n
    );
    static double midpoint(
        std::function<double(double)> f,
        double a,
        double b,
        int n
    );
    static double simpsons(
        std::function<double(double)> f,
        double a,
        double b,
        int n
    );
};

#endif
