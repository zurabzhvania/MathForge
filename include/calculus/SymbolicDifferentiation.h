#ifndef SYMBOLIC_DIFFERENTIATION_H
#define SYMBOLIC_DIFFERENTIATION_H

#include <string>

class SymbolicDifferentiation
{
public:
    static std::string differentiate(
        const std::string& expression
    );
};

#endif