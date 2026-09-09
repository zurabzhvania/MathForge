#include <calculus/ExactIntegral.h>

#include <cmath>

double ExactIntegral::compute(
    const std::string& functionName,
    double a,
    double b
)
{
    if (functionName == "x^2")
    {
        return
            (pow(b, 3) - pow(a, 3))
            / 3.0;
    }

    else if (functionName == "sin(x)")
    {
        return
            -cos(b) + cos(a);
    }

    else if (functionName == "e^x")
    {
        return
            exp(b) - exp(a);
    }

    else
    {
        return NAN;
    }
}
