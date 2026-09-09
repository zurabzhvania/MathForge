#include <calculus/IntegrationSystem.h>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <functional>
#include <string>
#include <calculus/Integration.h>
#include <calculus/Validation.h>
#include <calculus/ExactIntegral.h>
#include <app/UI.h>
#include <calculus/Convergence.h>
#include <app/FunctionSelector.h>
#include <app/Input.h>
#include <app/ExpressionParser.h>
#include <sstream>
#include <regex>
#include <vector>
#include <cctype>


#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"

namespace
{
    std::string removeSpaces(const std::string& text)
    {
        std::string result;

        for (char c : text)
        {
            if (!std::isspace(c))
            {
                result += c;
            }
        }

        return result;
    }

    std::string integratePolynomial(
        const std::string& expression
    )
    {
        std::string expr =
            removeSpaces(expression);

        std::vector<std::string> terms;

        std::string current;

        for (size_t i = 0; i < expr.size(); i++)
        {
            char c = expr[i];

            if ((c == '+' || c == '-') && i != 0)
            {
                terms.push_back(current);
                current.clear();
            }

            current += c;
        }

        if (!current.empty())
        {
            terms.push_back(current);
        }

        std::string result;

        for (const auto& term : terms)
        {
            std::smatch match;

            std::regex powerPattern(
                R"(([+-]?\d*\.?\d*)\*?x\^(\d+))"
            );

            std::regex linearPattern(
                R"(([+-]?\d*\.?\d*)\*?x)"
            );

            std::regex constantPattern(
                R"(([+-]?\d+\.?\d*))"
            );

            if (std::regex_match(term, match, powerPattern))
            {
                std::string coefficientText = match[1];

                double coefficient = 1.0;

                if (coefficientText == "-")
                {
                    coefficient = -1.0;
                }
                else if (!coefficientText.empty() &&
                         coefficientText != "+")
                {
                    coefficient = std::stod(coefficientText);
                }

                int power =
                    std::stoi(match[2]);

                int newPower =
                    power + 1;

                double newCoefficient =
                    coefficient / newPower;

                result +=
                    std::to_string(newCoefficient) +
                    "*x^" +
                    std::to_string(newPower) +
                    " + ";
            }
            else if (std::regex_match(term, match, linearPattern))
            {
                std::string coefficientText = match[1];

                double coefficient = 1.0;

                if (coefficientText == "-")
                {
                    coefficient = -1.0;
                }
                else if (!coefficientText.empty() &&
                         coefficientText != "+")
                {
                    coefficient = std::stod(coefficientText);
                }

                double newCoefficient =
                    coefficient / 2.0;

                result +=
                    std::to_string(newCoefficient) +
                    "*x^2 + ";
            }
            else if (std::regex_match(term, match, constantPattern))
            {
                double constant =
                    std::stod(match[1]);

                result +=
                    std::to_string(constant) +
                    "*x + ";
            }
            else
            {
                return "Symbolic integration not supported yet.";
            }
        }

        if (result.size() >= 3)
        {
            result.erase(result.size() - 3);
        }

        result += " + C";

        return result;
    }
}

void IntegrationSystem::run()
{
    std::string expression;

    std::cout << std::endl;

    std::cout << CYAN
              << "========================================"
              << RESET
              << std::endl;

    std::cout << CYAN
              << "         NUMERICAL INTEGRATION"
              << RESET
              << std::endl;

    std::cout << CYAN
              << "========================================"
              << RESET
              << std::endl;

    std::cout << std::endl;

    std::cout << "Enter expression: ";

    std::cin >> expression;

    std::string symbolicIntegral =
        integratePolynomial(expression);

    std::function<double(double)> selectedFunction =
        [expression](double x)
    {
        return ExpressionParser::evaluate(
            expression,
            x
        );
    };

    double a;
    double b;

    std::cout << "Enter lower bound a: ";
    a = Input::getDouble();

    std::cout << "Enter upper bound b: ";
    b = Input::getDouble();

    if (a >= b)
    {
        std::cout << RED
                  << "Invalid interval!"
                  << RESET
                  << std::endl;

        return;
    }

    int n;

    std::cout << "Enter number of subdivisions: ";
    n = Input::getInt();

    if (n <= 0)
    {
        std::cout << RED
                  << "Subdivisions must be positive!"
                  << RESET
                  << std::endl;

        return;
    }

    if (n % 2 != 0)
    {
        std::cout << RED
                  << "Subdivisions must be even so Simpson's rule can be calculated."
                  << RESET
                  << std::endl;
        return;
    }

    try
    {
        double left =
            Integration::leftRiemann(
                selectedFunction,
                a,
                b,
                n
            );

        double right =
            Integration::rightRiemann(
                selectedFunction,
                a,
                b,
                n
            );

        double midpoint =
            Integration::midpoint(
                selectedFunction,
                a,
                b,
                n
            );

        double trapezoidal =
            Integration::trapezoidal(
                selectedFunction,
                a,
                b,
                n
            );

        double simpson =
            Integration::simpsons(
                selectedFunction,
                a,
                b,
                n
            );

        // High-precision reference integral for error analysis
        int referenceN = 100000;
        if (referenceN % 2 != 0)
        {
            referenceN++;
        }
        double referenceIntegral =
            Integration::simpsons(
                selectedFunction,
                a,
                b,
                referenceN
            );

        std::cout << std::endl;

        std::cout << CYAN
                  << "========================================"
                  << RESET
                  << std::endl;

        std::cout << CYAN
                  << "          INTEGRATION RESULTS"
                  << RESET
                  << std::endl;

        std::cout << CYAN
                  << "========================================"
                  << RESET
                  << std::endl;

        std::cout << std::left
                  << std::setw(25)
                  << "Reference Integral"
                  << ": "
                  << referenceIntegral
                  << std::endl;

        std::cout << std::left
                  << std::setw(25)
                  << "Indefinite Integral"
                  << ": "
                  << symbolicIntegral
                  << std::endl;

        std::cout << std::endl;

        std::cout << std::left
                  << std::setw(25)
                  << "Left Riemann"
                  << ": "
                  << left
                  << std::endl;

        std::cout << std::left
                  << std::setw(25)
                  << "Right Riemann"
                  << ": "
                  << right
                  << std::endl;

        std::cout << std::left
                  << std::setw(25)
                  << "Midpoint"
                  << ": "
                  << midpoint
                  << std::endl;

        std::cout << std::left
                  << std::setw(25)
                  << "Trapezoidal"
                  << ": "
                  << trapezoidal
                  << std::endl;

        std::cout << std::left
                  << std::setw(25)
                  << "Simpson"
                  << ": "
                  << simpson
                  << std::endl;

        double spread =
            std::abs(right - left);

        std::cout << std::left
                  << std::setw(25)
                  << "Riemann Spread"
                  << ": "
                  << spread
                  << std::endl;

        // Error analysis section
        std::cout << std::endl;

        std::cout << CYAN
                  << "========================================"
                  << RESET
                  << std::endl;

        std::cout << CYAN
                  << "            ERROR ANALYSIS"
                  << RESET
                  << std::endl;

        std::cout << CYAN
                  << "========================================"
                  << RESET
                  << std::endl;

        double leftError =
            std::abs(referenceIntegral - left);

        double rightError =
            std::abs(referenceIntegral - right);

        double midpointError =
            std::abs(referenceIntegral - midpoint);

        double trapezoidalError =
            std::abs(referenceIntegral - trapezoidal);

        double simpsonError =
            std::abs(referenceIntegral - simpson);

        std::cout << std::left
                  << std::setw(25)
                  << "Left Error"
                  << ": "
                  << leftError
                  << std::endl;

        std::cout << std::left
                  << std::setw(25)
                  << "Right Error"
                  << ": "
                  << rightError
                  << std::endl;

        std::cout << std::left
                  << std::setw(25)
                  << "Midpoint Error"
                  << ": "
                  << midpointError
                  << std::endl;

        std::cout << std::left
                  << std::setw(25)
                  << "Trapezoidal Error"
                  << ": "
                  << trapezoidalError
                  << std::endl;

        std::cout << std::left
                  << std::setw(25)
                  << "Simpson Error"
                  << ": "
                  << simpsonError
                  << std::endl;

        std::cout << std::endl;

        // Accuracy-based recommendation system
        std::string recommendedMethod = "Left Riemann";
        std::string reason = "Lowest numerical error.";

        double bestError = leftError;

        if (rightError < bestError)
        {
            bestError = rightError;
            recommendedMethod = "Right Riemann";
        }

        if (midpointError < bestError)
        {
            bestError = midpointError;
            recommendedMethod = "Midpoint";
        }

        if (trapezoidalError < bestError)
        {
            bestError = trapezoidalError;
            recommendedMethod = "Trapezoidal";
        }

        if (simpsonError < bestError)
        {
            bestError = simpsonError;
            recommendedMethod = "Simpson";
        }

        std::cout << GREEN
                  << "Recommended Method: "
                  << recommendedMethod
                  << RESET
                  << std::endl;

        std::cout << YELLOW
                  << "Reason: "
                  << reason
                  << RESET
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
