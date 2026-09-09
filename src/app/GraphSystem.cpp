#include <app/GraphSystem.h>

#include <iostream>
#include <functional>

#include <app/ExpressionParser.h>
#include <app/Graph.h>
#include <app/Input.h>

void GraphSystem::run()
{
    std::string expression;

    std::cout << "Enter expression: ";

    std::cin >> expression;

    std::function<double(double)> selectedFunction =
        [expression](double x)
    {
        return ExpressionParser::evaluate(
            expression,
            x
        );
    };

    double xMin;
    double xMax;

    std::cout << "Enter xMin: ";
    xMin = Input::getDouble();

    std::cout << "Enter xMax: ";
    xMax = Input::getDouble();

    if (xMin >= xMax)
    {
        std::cout << "Invalid interval!"
                  << std::endl;

        return;
    }

    Graph::plot(
        selectedFunction,
        xMin,
        xMax
    );
}
