#ifndef CONVERGENCE_H
#define CONVERGENCE_H

#include <functional>

namespace Convergence
{
    void showIntegrationConvergence(
        std::function<double(double)> f,
        double exactIntegral,
        double a,
        double b
    );
}

#endif
