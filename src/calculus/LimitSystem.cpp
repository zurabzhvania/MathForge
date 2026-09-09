#include <calculus/LimitSystem.h>

#include <iostream>
#include <algorithm>
#include <functional>
#include <cmath>
#include <app/Input.h>
#include <app/ExpressionParser.h>
#include <calculus/Limits.h>
#include <calculus/Validation.h>
#include <app/UI.h>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"

void LimitSystem::run()
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

    UI::showLimitsHeader();

    UI::showLimitExplanation();

    double limitPoint;
    double limitH;

    std::cout << std::endl;

    std::cout
        << "Enter point the function approaches: ";

    std::cin >> limitPoint;

    std::cout
        << "Enter h distance from point: ";

    limitH = Input::getDouble();

    if (limitH <= 0)
    {
        std::cout << RED
                  << "h must be positive!"
                  << RESET
                  << std::endl;

        return;
    }

    try
    {
        double leftLimit =
            Limits::leftLimit(
                selectedFunction,
                limitPoint,
                limitH
            );

        double rightLimit =
            Limits::rightLimit(
                selectedFunction,
                limitPoint,
                limitH
            );

        std::cout << "Left-Hand Limit: "
                  << leftLimit
                  << std::endl;

        std::cout << "Right-Hand Limit: "
                  << rightLimit
                  << std::endl;

        double difference =
            std::abs(rightLimit - leftLimit);

        if (!std::isfinite(leftLimit) ||
            !std::isfinite(rightLimit))
        {
            std::cout << RED
                      << "The function is not finite near this point."
                      << RESET
                      << std::endl;
            return;
        }

        std::cout << "Limit Difference: "
                  << difference
                  << std::endl;

        double estimatedLimit =
            (leftLimit + rightLimit)
            / 2.0;

        std::cout << "Estimated Limit: "
                  << estimatedLimit
                  << std::endl;

        double scale =
            std::max(1.0,
                     std::max(std::abs(leftLimit),
                              std::abs(rightLimit)));

        double tolerance =
            1e-6 * scale;

        if (difference < tolerance)
        {
            std::cout << GREEN
                      << "The sampled left and right values are close."
                      << RESET
                      << std::endl;
        }
        else
        {
            std::cout << RED
                      << "The sampled left and right values differ."
                      << RESET
                      << std::endl;
        }

        std::cout << "This finite sample cannot prove that a limit exists; "
                  << "try smaller h values to investigate further."
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
