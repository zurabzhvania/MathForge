#include <calculus/Applications.h>
#include <calculus/Integration.h>
#include <calculus/Differentiation.h>

#include <cmath>

namespace Applications
{
    double averageValue(
        std::function<double(double)> f,
        double a,
        double b,
        int n
    )
    {
        double integral =
            Integration::trapezoidal(
                f,
                a,
                b,
                n
            );

        return integral / (b - a);
    }

    double arcLength(
        std::function<double(double)> f,
        double a,
        double b,
        int n,
        double h
    )
    {
        auto integrand =
            [f, h](double x)
        {
            double derivative =
                Differentiation::centralDifference(
                    f,
                    x,
                    h
                );

            return std::sqrt(
                1 +
                derivative * derivative
            );
        };

        return Integration::trapezoidal(
            integrand,
            a,
            b,
            n
        );
    }
}
