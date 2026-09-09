#include <calculus/Differentiation.h>

#include <functional>
#include <cmath>
#include <stdexcept>

namespace
{
    void validateArguments(
        const std::function<double(double)>& function,
        double x,
        double h
    )
    {
        if (!function || !std::isfinite(x) || !std::isfinite(h) || h <= 0.0)
        {
            throw std::invalid_argument("Differentiation requires a finite x and positive step size.");
        }
    }

    double evaluate(const std::function<double(double)>& function, double x)
    {
        double value = function(x);

        if (!std::isfinite(value))
        {
            throw std::domain_error("Function is not finite near the differentiation point.");
        }
        return value;
    }
}

double Differentiation::forwardDifference(
    std::function<double(double)> f,
    double x,
    double h
)
{
    validateArguments(f, x, h);
    return (evaluate(f, x + h) - evaluate(f, x)) / h;
}

double Differentiation::backwardDifference(
    std::function<double(double)> f,
    double x,
    double h
)
{
    validateArguments(f, x, h);
    return (evaluate(f, x) - evaluate(f, x - h)) / h;
}

double Differentiation::centralDifference(
    std::function<double(double)> f,
    double x,
    double h
)
{
    validateArguments(f, x, h);
    return (evaluate(f, x + h) - evaluate(f, x - h))
           / (2 * h);
}
