#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <functional>
#include <string>
#include <vector>

struct MathFunction
{
    std::string name;

    std::function<double(double)> function;
};

std::vector<MathFunction> getFunctions();

MathFunction findFunction(
    const std::string& name
);

#endif
