#include <calculus/ApplicationsSystem.h>

#include <iostream>
#include <vector>
#include <functional>

#include <app/Functions.h>
#include <calculus/Applications.h>
#include <calculus/Validation.h>
#include <app/UI.h>
#include <app/FunctionSelector.h>
#include <app/Input.h>
void ApplicationsSystem::run()
{
    std::cout << std::endl;

    std::cout << "1. Average Value"
              << std::endl;

    std::cout << "2. Arc Length"
              << std::endl;

    std::cout << "0. Back"
              << std::endl;

    int choice;

    std::cout << std::endl;
    std::cout << "Enter choice: ";

    choice = Input::getInt();

    if (choice != 1 && choice != 2)
    {
        std::cout << "Invalid choice!"
                  << std::endl;
        return;
    }
    if (choice == 0)
    {
        return;
    }

    MathFunction selectedMathFunction =
        FunctionSelector::selectFunction();

    if (selectedMathFunction.function == nullptr)
    {
        return;
    }

    std::function<double(double)> selectedFunction =
        selectedMathFunction.function;

    double a;
    double b;

    std::cout << "Enter a: ";
    a = Input::getDouble();

    std::cout << "Enter b: ";
    b = Input::getDouble();

    if (a >= b)
    {
        std::cout << "Invalid interval!"
                  << std::endl;

        return;
    }

    int n;

    std::cout
        << "Enter subdivisions: ";

    n = Input::getInt();

    if (n <= 0)
    {
        std::cout << "Subdivisions must be positive!"
                  << std::endl;
        return;
    }

    if (choice == 1)
    {
        double average =
            Applications::averageValue(
                selectedFunction,
                a,
                b,
                n
            );

        UI::showApplicationsHeader();

        std::cout
            << "Average Value: "
            << average
            << std::endl;
    }

    else if (choice == 2)
    {
        double arc =
            Applications::arcLength(
                selectedFunction,
                a,
                b,
                n,
                0.0001
            );

        UI::showApplicationsHeader();

        std::cout
            << "Arc Length: "
            << arc
            << std::endl;
    }
}
