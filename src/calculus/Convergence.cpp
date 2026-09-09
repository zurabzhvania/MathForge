#include <calculus/Convergence.h>
#include <calculus/Integration.h>

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

namespace Convergence
{
    void showIntegrationConvergence(
        std::function<double(double)> f,
        double exactIntegral,
        double a,
        double b
    )
    {
        std::vector<int> subdivisions =
        {
            10,
            100,
            1000,
            10000
        };

        std::cout << std::endl;

        std::cout
            << "========================================"
            << std::endl;

        std::cout
            << "        CONVERGENCE ANALYSIS"
            << std::endl;

        std::cout
            << "========================================"
            << std::endl;

        std::cout << std::left
                  << std::setw(10) << "n"
                  << std::setw(20) << "Midpoint Error"
                  << std::setw(20) << "Trap Error"
                  << std::endl;

        for (int n : subdivisions)
        {
            double midpoint =
                Integration::midpoint(
                    f,
                    a,
                    b,
                    n
                );

            double trapezoidal =
                Integration::trapezoidal(
                    f,
                    a,
                    b,
                    n
                );

            double midpointError =
                std::abs(
                    exactIntegral - midpoint
                );

            double trapError =
                std::abs(
                    exactIntegral - trapezoidal
                );

            std::cout << std::left
                      << std::setw(10) << n
                      << std::setw(20) << midpointError
                      << std::setw(20) << trapError
                      << std::endl;
        }
    }
}
