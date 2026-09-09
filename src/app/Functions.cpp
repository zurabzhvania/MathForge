#include <app/Functions.h>

#include <cmath>

double square(double x)
{
    return x * x;
}

double sine(double x)
{
    return sin(x);
}

double exponential(double x)
{
    return exp(x);
}

double sinc(double x)
{
    return sin(x) / x;
}

double cosine(double x)
{
    return cos(x);
}

double logarithm(double x)
{
    return log(x);
}

double squareRoot(double x)
{
    return sqrt(x);
}

double reciprocal(double x)
{
    return 1.0 / x;
}

double cube(double x)
{
    return x * x * x;
}

std::vector<MathFunction> getFunctions()
{
    return
    {
        {"x^2", square},
        {"sin(x)", sine},
        {"e^x", exponential},
        {"sin(x)/x", sinc},
        {"cos(x)", cosine},
        {"ln(x)", logarithm},
        {"sqrt(x)", squareRoot},
        {"1/x", reciprocal},
        {"x^3", cube}
    };
}

MathFunction findFunction(
    const std::string& name
)
{
    std::vector<MathFunction> functions =
        getFunctions();

    for (const auto& function : functions)
    {
        if (function.name == name)
        {
            return function;
        }
    }

    return {"INVALID", nullptr};
}
