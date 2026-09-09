#include <app/UI.h>

#include <iostream>

#define RESET   "\033[0m"

#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

namespace UI
{
    void showMainHeader()
    {
        std::cout << std::endl;

        std::cout << CYAN
                  << "========================================"
                  << std::endl;

        std::cout << "   COMPUTATIONAL MATHEMATICS TOOLKIT"
                  << std::endl;

        std::cout << "========================================"
                  << RESET
                  << std::endl;
    }

    void showIntegrationHeader()
    {
        std::cout << std::endl;

        std::cout << BLUE
                  << "========================================"
                  << std::endl;

        std::cout << "         INTEGRATION RESULTS"
                  << std::endl;

        std::cout << "========================================"
                  << RESET
                  << std::endl;
    }

    void showErrorHeader()
    {
        std::cout << std::endl;

        std::cout << YELLOW
                  << "========================================"
                  << std::endl;

        std::cout << "            ERROR ANALYSIS"
                  << std::endl;

        std::cout << "========================================"
                  << RESET
                  << std::endl;
    }

    void showApplicationsHeader()
    {
        std::cout << std::endl;

        std::cout << CYAN
                  << "========================================"
                  << std::endl;

        std::cout << "         FUNCTION APPLICATIONS"
                  << std::endl;

        std::cout << "========================================"
                  << RESET
                  << std::endl;
    }

    void showDerivativeHeader()
    {
        std::cout << std::endl;

        std::cout << MAGENTA
                  << "========================================"
                  << std::endl;

        std::cout << "          DIFFERENTIATION"
                  << std::endl;

        std::cout << "========================================"
                  << RESET
                  << std::endl;
    }

    void showLimitsHeader()
    {
        std::cout << std::endl;

        std::cout << GREEN
                  << "========================================"
                  << std::endl;

        std::cout << "               LIMITS"
                  << std::endl;

        std::cout << "========================================"
                  << RESET
                  << std::endl;
    }

    void showSeriesHeader()
    {
        std::cout << std::endl;

        std::cout << CYAN
                  << "========================================"
                  << std::endl;

        std::cout << "         SERIES APPROXIMATION"
                  << std::endl;

        std::cout << "========================================"
                  << RESET
                  << std::endl;
    }

    void showDerivativeExplanation()
    {
        std::cout << std::endl;

        std::cout
            << "Derivative Explanation:"
            << std::endl;

        std::cout
            << "- Derivative measures local rate of change."
            << std::endl;

        std::cout
            << "- x determines where slope is estimated."
            << std::endl;

        std::cout
            << "- h controls approximation precision."
            << std::endl;

        std::cout
            << "- Smaller h usually improves accuracy,"
            << std::endl;

        std::cout
            << "  but too small may cause floating-point errors."
            << std::endl;
    }

    void showLimitExplanation()
    {
        std::cout << std::endl;

        std::cout
            << "Limit Explanation:"
            << std::endl;

        std::cout
            << "- Limits study nearby function behavior."
            << std::endl;

        std::cout
            << "- The point is approached from both sides."
            << std::endl;

        std::cout
            << "- h determines how close we get to the point."
            << std::endl;

        std::cout
            << "- If left and right values become close,"
            << std::endl;

        std::cout
            << "  the limit likely exists."
            << std::endl;
    }

    void showArcLengthExplanation()
    {
        std::cout << std::endl;

        std::cout
            << "Arc Length Explanation:"
            << std::endl;

        std::cout
            << "- Arc length measures curve distance."
            << std::endl;

        std::cout
            << "- Uses numerical derivatives and integration."
            << std::endl;

        std::cout
            << "- Larger slopes increase total curve length."
            << std::endl;
    }

    void showSuccessMessage(
        const std::string& message
    )
    {
        std::cout << GREEN
                  << message
                  << RESET
                  << std::endl;
    }

    void showErrorMessage(
        const std::string& message
    )
    {
        std::cout << RED
                  << message
                  << RESET
                  << std::endl;
    }
}
