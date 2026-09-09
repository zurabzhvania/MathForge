#include <app/ExpressionParser.h>
#include <calculus/SeriesSystem.h>

#include <iostream>
#include <cmath>
#include <iomanip>
#include <app/Input.h>
#include <calculus/Series.h>
#include <app/UI.h>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"

void SeriesSystem::run()
{
    UI::showSeriesHeader();

    int seriesChoice;

    std::cout << "1. e^x Maclaurin"
              << std::endl;

    std::cout << "2. sin(x) Maclaurin"
              << std::endl;

    std::cout << "3. e^x Taylor"
              << std::endl;

    std::cout << "4. sin(x) Taylor"
              << std::endl;

    std::cout << "5. General Series Summation"
              << std::endl;

    std::cout << "6. Infinite Series Approximation"
              << std::endl;

    std::cout << "0. Back"
              << std::endl;

    seriesChoice = Input::getInt();

    if (seriesChoice == 0)
    {
        return;
    }

    if (seriesChoice < 0 ||
        seriesChoice > 6)
    {
        std::cout << RED
                  << "Invalid choice!"
                  << RESET
                  << std::endl;

        return;
    }

    if (seriesChoice == 5)
    {
        std::string expression;

        std::cout << "Enter series term expression in x: ";
        std::cin >> expression;

        int startX;
        int endX;

        std::cout << "Enter starting x: ";
        startX = Input::getInt();

        std::cout << "Enter ending x: ";
        endX = Input::getInt();

        if (startX > endX)
        {
            std::cout << RED
                      << "Invalid interval!"
                      << RESET
                      << std::endl;

            return;
        }

        double sum = 0.0;

        try
        {
            for (int x = startX;
                 x <= endX;
                 x++)
            {
                double term =
                    ExpressionParser::evaluate(
                        expression,
                        x
                    );

                sum += term;
            }

            std::cout << std::endl;

            std::cout
                << "========================================"
                << std::endl;

            std::cout
                << "         SERIES SUMMATION"
                << std::endl;

            std::cout
                << "========================================"
                << std::endl;

            std::cout << std::left
                      << std::setw(30)
                      << "Expression"
                      << ": "
                      << expression
                      << std::endl;

            std::cout << std::left
                      << std::setw(30)
                      << "Start x"
                      << ": "
                      << startX
                      << std::endl;

            std::cout << std::left
                      << std::setw(30)
                      << "End x"
                      << ": "
                      << endX
                      << std::endl;

            std::cout << std::left
                      << std::setw(30)
                      << "Series Sum"
                      << ": "
                      << sum
                      << std::endl;

            double lastTerm =
                ExpressionParser::evaluate(
                    expression,
                    endX
                );

            std::cout << std::left
                      << std::setw(30)
                      << "Last Term"
                      << ": "
                      << lastTerm
                      << std::endl;

            if (std::abs(lastTerm) < 0.0001)
            {
                std::cout << GREEN
                          << "Series terms appear to converge toward zero."
                          << RESET
                          << std::endl;
            }
            else
            {
                std::cout << YELLOW
                          << "Series may diverge or converge slowly."
                          << RESET
                          << std::endl;
            }
        }
        catch (const std::exception& error)
        {
            std::cout << RED
                      << "Parser Error: "
                      << error.what()
                      << RESET
                      << std::endl;
        }

        return;
    }

    if (seriesChoice == 6)
    {
        std::string expression;

        std::cout
            << "Enter infinite series expression in x: ";

        std::cin >> expression;

        double tolerance;

        std::cout
            << "Enter tolerance: ";

        tolerance = Input::getDouble();

        int maxIterations;

        std::cout
            << "Enter maximum iterations: ";

        maxIterations = Input::getInt();

        if (tolerance <= 0)
        {
            std::cout << RED
                      << "Tolerance must be positive!"
                      << RESET
                      << std::endl;

            return;
        }

        if (maxIterations <= 0)
        {
            std::cout << RED
                      << "Maximum iterations must be positive!"
                      << RESET
                      << std::endl;

            return;
        }

        double sum = 0.0;

        double lastTerm = 0.0;

        int iterationsUsed = 0;

        bool termToleranceReached = false;

        try
        {
            for (int x = 1;
                 x <= maxIterations;
                 x++)
            {
                double term =
                    ExpressionParser::evaluate(
                        expression,
                        x
                    );

                sum += term;

                lastTerm = term;

                iterationsUsed = x;

                if (std::abs(term) < tolerance)
                {
                    termToleranceReached = true;
                    break;
                }
            }

            std::cout << std::endl;

            std::cout
                << "========================================"
                << std::endl;

            std::cout
                << "   INFINITE SERIES APPROXIMATION"
                << std::endl;

            std::cout
                << "========================================"
                << std::endl;

            std::cout << std::left
                      << std::setw(30)
                      << "Expression"
                      << ": "
                      << expression
                      << std::endl;

            std::cout << std::left
                      << std::setw(30)
                      << "Approximate Sum"
                      << ": "
                      << sum
                      << std::endl;

            std::cout << std::left
                      << std::setw(30)
                      << "Iterations Used"
                      << ": "
                      << iterationsUsed
                      << std::endl;

            std::cout << std::left
                      << std::setw(30)
                      << "Last Term"
                      << ": "
                      << lastTerm
                      << std::endl;

            if (termToleranceReached)
            {
                std::cout << GREEN
                          << "Term tolerance reached; this alone does not prove convergence."
                          << RESET
                          << std::endl;
            }
            else
            {
                std::cout << YELLOW
                          << "Term tolerance was not reached."
                          << RESET
                          << std::endl;
            }
        }
        catch (const std::exception& error)
        {
            std::cout << RED
                      << "Parser Error: "
                      << error.what()
                      << RESET
                      << std::endl;
        }

        return;
    }

    double x;
    int terms;
    double center = 0.0;

    std::cout << "Enter x: ";
    x = Input::getDouble();

    std::cout << "Enter number of terms: ";
    terms = Input::getInt();

    if (seriesChoice == 3 ||
        seriesChoice == 4)
    {
        std::cout
            << "Enter Taylor center a: ";

        center = Input::getDouble();
    }

    if (terms <= 0)
    {
        std::cout << RED
                  << "Terms must be positive!"
                  << RESET
                  << std::endl;

        return;
    }

    double approximation = 0;
    double actualValue = 0;

    if (seriesChoice == 1)
    {
        approximation =
            Series::exponentialMaclaurin(
                x,
                terms
            );

        actualValue =
            exp(x);
    }
    else if (seriesChoice == 2)
    {
        approximation =
            Series::sineMaclaurin(
                x,
                terms
            );

        actualValue =
            sin(x);
    }
    else if (seriesChoice == 3)
    {
        approximation =
            Series::exponentialTaylor(
                x,
                center,
                terms
            );

        actualValue =
            exp(x);
    }
    else if (seriesChoice == 4)
    {
        approximation =
            Series::sineTaylor(
                x,
                center,
                terms
            );

        actualValue =
            sin(x);
    }

    double error =
        std::abs(
            actualValue -
            approximation
        );

    std::cout << std::endl;

    std::cout
        << "========================================"
        << std::endl;

    std::cout
        << "          SERIES ANALYSIS"
        << std::endl;

    std::cout
        << "========================================"
        << std::endl;

    std::cout << std::left
              << std::setw(30)
              << "Approximation"
              << ": "
              << approximation
              << std::endl;

    std::cout << std::left
              << std::setw(30)
              << "Actual Value"
              << ": "
              << actualValue
              << std::endl;

    std::cout << std::left
              << std::setw(30)
              << "Absolute Error"
              << ": "
              << error
              << std::endl;
}
