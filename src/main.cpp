#include <iostream>
#include <app/Input.h>
#include <app/Menu.h>
#include <calculus/IntegrationSystem.h>
#include <calculus/LimitSystem.h>
#include <calculus/SeriesSystem.h>
#include <calculus/ApplicationsSystem.h>
#include <app/GraphSystem.h>
#include <calculus/DifferentiationSystem.h>
#include <linear_algebra/LinearAlgebraSystem.h>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"

int main()
{
    while (true)
    {
        Menu::display();

        int choice;

        std::cout << std::endl;
        std::cout << "Enter choice: ";

        choice = Input::getInt();

        switch (choice)
        {
            case 1:
                IntegrationSystem::run();
                break;

            case 2:
               DifferentiationSystem::run();
               break;

            case 3:
                LimitSystem::run();
                break;

            case 4:
                SeriesSystem::run();
                break;

            case 5:
                ApplicationsSystem::run();
                break;

            case 6:
                GraphSystem::run();
                break;

            case 7:
                LinearAlgebraSystem::run();
                break;

            case 8:
                std::cout << GREEN
                          << "Program terminated."
                          << RESET
                          << std::endl;

                return 0;

            default:
                std::cout << RED
                          << "Invalid choice!"
                          << RESET
                          << std::endl;
        }
    }

    return 0;
}
