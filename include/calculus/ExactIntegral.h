#ifndef EXACTINTEGRAL_H
#define EXACTINTEGRAL_H

#include <string>

class ExactIntegral
{
public:
    static double compute(
        const std::string& functionName,
        double a,
        double b
    );
};

#endif
