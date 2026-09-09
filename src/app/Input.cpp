#include <app/Input.h>
#include <string>
#include <iostream>
#include <limits>

int Input::getInt()
{
    int value;

    while (!(std::cin >> value))
    {
        std::cin.clear();

        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n'
        );

        std::cout
            << "Invalid integer. Try again: ";
    }

    return value;
}

double Input::getDouble()
{
    double value;

    while (!(std::cin >> value))
    {
        std::cin.clear();

        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n'
        );

        std::cout
            << "Invalid number. Try again: ";
    }

    return value;
}

std::string Input::getFunctionName()
{
    std::string value;

    while (true)
    {
        std::cin >> value;

        if (!std::cin.fail())
        {
            return value;
        }

        std::cin.clear();
        std::cin.ignore(10000, '\n');

        std::cout << "Invalid input. Try again: ";
    }
}