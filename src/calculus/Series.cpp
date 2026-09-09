#include <calculus/Series.h>

#include <cmath>

namespace Series
{
    double exponentialMaclaurin(
        double x,
        int terms
    )
    {
        double sum = 0.0;

        for (int n = 0;
             n < terms;
             n++)
        {
            double factorial = 1.0;

            for (int i = 1;
                 i <= n;
                 i++)
            {
                factorial *= i;
            }

            double term =
                std::pow(x, n)
                / factorial;

            sum += term;
        }

        return sum;
    }

    double sineMaclaurin(
        double x,
        int terms
    )
    {
        double sum = 0.0;

        for (int n = 0;
             n < terms;
             n++)
        {
            double factorial = 1.0;

            for (int i = 1;
                 i <= (2 * n + 1);
                 i++)
            {
                factorial *= i;
            }

            double term =
                std::pow(-1, n)
                *
                std::pow(x,
                         2 * n + 1)
                /
                factorial;

            sum += term;
        }

        return sum;
    }

    double exponentialTaylor(
        double x,
        double a,
        int terms
    )
    {
        double sum = 0.0;

        for (int n = 0;
             n < terms;
             n++)
        {
            double factorial = 1.0;

            for (int i = 1;
                 i <= n;
                 i++)
            {
                factorial *= i;
            }

            double term =
                std::exp(a)
                *
                std::pow(x - a,
                         n)
                /
                factorial;

            sum += term;
        }

        return sum;
    }

    double sineTaylor(
        double x,
        double a,
        int terms
    )
    {
        double sum = 0.0;

        for (int n = 0; n < terms; n++)
        {
            double factorial = 1.0;

            for (int i = 1; i <= n; i++)
            {
                factorial *= i;
            }

            double derivativeValue;

            int cycle = n % 4;

            if (cycle == 0)
            {
                derivativeValue =
                    std::sin(a);
            }
            else if (cycle == 1)
            {
                derivativeValue =
                    std::cos(a);
            }
            else if (cycle == 2)
            {
                derivativeValue =
                    -std::sin(a);
            }
            else
            {
                derivativeValue =
                    -std::cos(a);
            }

            double term =
                derivativeValue
                *
                std::pow(x - a,
                         n)
                /
                factorial;

            sum += term;
        }

        return sum;
    }
}
