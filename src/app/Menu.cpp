#include <app/Menu.h>

#include <iostream>

void Menu::display()
{
    std::cout
        << "====================================="
        << std::endl;

    std::cout
        << "              MAIN MENU"
        << std::endl;

    std::cout
        << "====================================="
        << std::endl;

    std::cout << std::endl;

    std::cout << "1. Integration"
              << std::endl;

    std::cout << "2. Differentiation"
              << std::endl;

    std::cout << "3. Limits"
              << std::endl;

    std::cout << "4. Series"
              << std::endl;

    std::cout << "5. Applications"
              << std::endl;

    std::cout << "6. Graphing"
              << std::endl;

    std::cout << "7. Linear Algebra"
              << std::endl;

    std::cout << "8. Exit"
              << std::endl;
}
