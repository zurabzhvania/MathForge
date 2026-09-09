#include <calculus/Limits.h>

double Limits::leftLimit(
    std::function<double(double)> f,
    double a,
    double h
)
{
    return f(a - h);
}

double Limits::rightLimit(
    std::function<double(double)> f,
    double a,
    double h
)
{
    return f(a + h);
}
