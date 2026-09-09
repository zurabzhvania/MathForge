#include <cassert>
#include <cmath>
#include <stdexcept>

#include <calculus/Differentiation.h>
#include <app/ExpressionParser.h>
#include <calculus/Integration.h>
#include <calculus/Series.h>

namespace
{
    bool nearlyEqual(double actual, double expected, double tolerance)
    {
        return std::abs(actual - expected) <= tolerance;
    }

    double square(double x)
    {
        return x * x;
    }
}

int main()
{
    assert(nearlyEqual(Series::sineTaylor(1.0, 0.0, 8), std::sin(1.0), 0.00001));
    assert(nearlyEqual(Series::sineTaylor(0.8, 0.3, 8), std::sin(0.8), 0.00001));
    assert(nearlyEqual(ExpressionParser::evaluate("2^3^2", 0.0), 512.0, 0.0));
    assert(nearlyEqual(Integration::simpsons(square, 0.0, 1.0, 100), 1.0 / 3.0, 1e-12));
    assert(nearlyEqual(Differentiation::centralDifference(square, 3.0, 1e-5), 6.0, 1e-5));

    bool rejectedInvalidSubdivisions = false;
    try
    {
        (void)Integration::trapezoidal(square, 0.0, 1.0, 0);
    }
    catch (const std::invalid_argument&)
    {
        rejectedInvalidSubdivisions = true;
    }
    assert(rejectedInvalidSubdivisions);

    bool rejectedOddSimpson = false;
    try
    {
        (void)Integration::simpsons(square, 0.0, 1.0, 3);
    }
    catch (const std::invalid_argument&)
    {
        rejectedOddSimpson = true;
    }
    assert(rejectedOddSimpson);
    return 0;
}
