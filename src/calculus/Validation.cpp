#include <calculus/Validation.h>

#include <cmath>

namespace Validation
{
    bool isValidInput(
        const std::string& functionName,
        double x
    )
    {
        if (functionName == "ln(x)")
        {
            return x > 0;
        }

        if (functionName == "sqrt(x)")
        {
            return x >= 0;
        }

        if (functionName == "1/x")
        {
            return x != 0;
        }

        return true;
    }
}
