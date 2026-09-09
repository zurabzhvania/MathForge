#include <calculus/DifferentiationSystem.h>

#include <iostream>
#include <iomanip>
#include <functional>
#include <cmath>
#include <string>
#include <exception>

#include <calculus/Differentiation.h>
#include <app/ExpressionParser.h>
#include <calculus/SymbolicDifferentiation.h>
#include <app/Input.h>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"

void DifferentiationSystem::run()
{
    std::string expression;

    std::cout << std::endl;

    std::cout << CYAN
              << "========================================"
              << RESET
              << std::endl;

    std::cout << CYAN
              << "       DIFFERENTIATION SYSTEM"
              << RESET
              << std::endl;

    std::cout << CYAN
              << "========================================"
              << RESET
              << std::endl;

    std::cout << std::endl;

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

    std::string symbolicDerivative =
        SymbolicDifferentiation::differentiate(
            expression
        );

    double x;

    std::cout << "Enter x value: ";
    x = Input::getDouble();

    double h;

    std::cout << "Enter step size h: ";
    h = Input::getDouble();

    if (h <= 0)
    {
        std::cout << RED
                  << "Step size must be positive!"
                  << RESET
                  << std::endl;

        return;
    }

    try
    {
        double forward =
            Differentiation::forwardDifference(
                selectedFunction,
                x,
                h
            );

        double backward =
            Differentiation::backwardDifference(
                selectedFunction,
                x,
                h
            );

        double central =
            Differentiation::centralDifference(
                selectedFunction,
                x,
                h
            );

        double comparisonEstimate =
            Differentiation::centralDifference(
                selectedFunction,
                x,
                h / 2.0
            );

        std::cout << std::endl;

        std::cout << CYAN
                  << "========================================"
                  << RESET
                  << std::endl;

        std::cout << CYAN
                  << "       DIFFERENTIATION RESULTS"
                  << RESET
                  << std::endl;

        std::cout << CYAN
                  << "========================================"
                  << RESET
                  << std::endl;

        std::cout << std::left
                  << std::setw(25)
                  << "Symbolic Derivative"
                  << ": "
                  << symbolicDerivative
                  << std::endl;

        std::cout << std::left
                  << std::setw(25)
                  << "Refined Central Estimate"
                  << ": "
                  << comparisonEstimate
                  << std::endl;

        std::cout << std::endl;

        std::cout << std::left
                  << std::setw(25)
                  << "Forward Difference"
                  << ": "
                  << forward
                  << std::endl;

        std::cout << std::left
                  << std::setw(25)
                  << "Backward Difference"
                  << ": "
                  << backward
                  << std::endl;

        std::cout << std::left
                  << std::setw(25)
                  << "Central Difference"
                  << ": "
                  << central
                  << std::endl;

        double forwardError =
            std::abs(comparisonEstimate - forward);

        double backwardError =
            std::abs(comparisonEstimate - backward);

        double centralError =
            std::abs(comparisonEstimate - central);

        std::cout << std::endl;

        std::cout << CYAN
                  << "========================================"
                  << RESET
                  << std::endl;

        std::cout << CYAN
                  << "          ERROR ANALYSIS"
                  << RESET
                  << std::endl;

        std::cout << CYAN
                  << "========================================"
                  << RESET
                  << std::endl;

        std::cout << std::left
                  << std::setw(25)
                  << "Forward Difference"
                  << ": "
                  << forwardError
                  << std::endl;

        std::cout << std::left
                  << std::setw(25)
                  << "Backward Difference"
                  << ": "
                  << backwardError
                  << std::endl;

        std::cout << std::left
                  << std::setw(25)
                  << "Central Difference"
                  << ": "
                  << centralError
                  << std::endl;

        std::cout << std::endl
                  << "These are differences from a refined numerical estimate, "
                  << "not exact errors."
                  << std::endl;
    }
    catch (const std::exception& error)
    {
        std::cout << RED
                  << "Parser Error: "
                  << error.what()
                  << RESET
                  << std::endl;
    }
}
