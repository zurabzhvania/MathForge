#include <calculus/Integration.h>
#include <cmath>
#include <stdexcept>

namespace
{
    void validateArguments(
        const std::function<double(double)>& function,
        double a,
        double b,
        int n
    )
    {
        if (!function || !std::isfinite(a) || !std::isfinite(b) || n <= 0)
        {
            throw std::invalid_argument("Integration requires finite bounds and positive subdivisions.");
        }
    }

    double evaluate(const std::function<double(double)>& function, double x)
    {
        double value = function(x);

        if (!std::isfinite(value))
        {
            throw std::domain_error("Function is not finite on the integration interval.");
        }
        return value;
    }
}

double Integration::leftRiemann(
    std::function<double(double)> f,
    double a,
    double b,
    int n
)
{
    validateArguments(f, a, b, n);
    double dx = (b - a) / n;

    double sum = 0;

    for (int i = 0; i < n; i++)
    {
        double x = a + i * dx;

        sum += evaluate(f, x);
    }

    return sum * dx;
}
double Integration::rightRiemann(
    std::function<double(double)> f,
    double a,
    double b,
    int n
)
{
    validateArguments(f, a, b, n);
    double dx = (b - a) / n;

    double sum = 0;

    for (int i = 0; i < n; i++)
    {
        double x = a + (i + 1) * dx;

        sum += evaluate(f, x);
    }

    return sum * dx;
}
double Integration::trapezoidal(
    std::function<double(double)> f,
    double a,
    double b,
    int n
)
{
    validateArguments(f, a, b, n);
    double dx = (b - a) / n;

    double sum = evaluate(f, a) + evaluate(f, b);

    for (int i = 1; i < n; i++)
    {
        double x = a + i * dx;

        sum += 2 * evaluate(f, x);
    }

    return (dx / 2) * sum;
}
double Integration::midpoint(
    std::function<double(double)> f,
    double a,
    double b,
    int n
)
{
    validateArguments(f, a, b, n);
    double dx = (b - a) / n;

    double sum = 0;

    for (int i = 0; i < n; i++)
    {
        double x =
            a + i * dx + dx / 2;

        sum += evaluate(f, x);
    }

    return sum * dx;
}
double Integration::simpsons(

    std::function<double(double)> f,

    double a,

    double b,

    int n

)

{
    validateArguments(f, a, b, n);

    if (n % 2 != 0)
    {
        throw std::invalid_argument("Simpson's rule requires an even number of subdivisions.");
    }

    double h =

        (b - a) / n;

    double sum =

        evaluate(f, a) + evaluate(f, b);

    for (int i = 1; i < n; i++)

    {

        double x =

            a + i * h;

        if (i % 2 == 0)

        {

            sum +=

                2 * evaluate(f, x);

        }

        else

        {

            sum +=

                4 * evaluate(f, x);

        }

    }

    return

        (h / 3.0) * sum;

}
