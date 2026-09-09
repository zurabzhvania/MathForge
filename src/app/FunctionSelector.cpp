#include <app/FunctionSelector.h>

#include <iostream>
#include <vector>

#include <app/Functions.h>
#include <app/Input.h>

MathFunction FunctionSelector::selectFunction()
{
    std::vector<MathFunction> functions =
        getFunctions();

    std::cout << std::endl;

    std::cout << "Available functions:"
              << std::endl;

    for (const auto& function : functions)
    {
        std::cout << "- "
                  << function.name
                  << std::endl;
    }

    std::string functionName;

    std::cout << std::endl;

    std::cout << "Enter function name: ";

    functionName =
        Input::getFunctionName();

    MathFunction selectedMathFunction =
        findFunction(functionName);

    if (selectedMathFunction.function == nullptr)
    {
        std::cout
            << "Function not found!"
            << std::endl;
    }

    return selectedMathFunction;
}
