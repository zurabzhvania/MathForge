#include <linear_algebra/LinearAlgebraSystem.h>

#include <iostream>
#include <vector>

#include <app/Input.h>
#include <linear_algebra/linear_algebra.h>

namespace
{
    const char *statusMessage(CalgoLinearAlgebraStatus status)
    {
        switch (status)
        {
            case CALGO_LINALG_SUCCESS:
                return "Success";
            case CALGO_LINALG_ALLOCATION_FAILURE:
                return "Not enough memory to create the system.";
            case CALGO_LINALG_DIMENSION_MISMATCH:
                return "The coefficient matrix must be square.";
            case CALGO_LINALG_SINGULAR_MATRIX:
                return "The system has no unique solution.";
            case CALGO_LINALG_INVALID_ARGUMENT:
            default:
                return "Invalid matrix or numeric input.";
        }
    }
}

void LinearAlgebraSystem::run()
{
    std::cout << "Enter the number of variables (1-10): ";
    int input_dimension = Input::getInt();

    if (input_dimension < 1 || input_dimension > 10)
    {
        std::cout << "Choose a size from 1 to 10."
                  << std::endl;
        return;
    }

    size_t dimension = static_cast<size_t>(input_dimension);
    CalgoMatrix matrix = {0, 0, nullptr};
    std::vector<double> constants(dimension);
    std::vector<double> solution(dimension);
    CalgoLinearAlgebraStatus status = calgo_matrix_init(&matrix, dimension, dimension);

    if (status != CALGO_LINALG_SUCCESS)
    {
        std::cout << statusMessage(status) << std::endl;
        return;
    }

    std::cout << "Enter each equation as " << dimension
              << " coefficients followed by its constant." << std::endl;
    for (size_t row = 0; row < dimension; row++)
    {
        for (size_t column = 0; column < dimension; column++)
        {
            std::cout << "a[" << row + 1 << "][" << column + 1 << "]: ";
            double value = Input::getDouble();
            status = calgo_matrix_set(&matrix, row, column, value);
            if (status != CALGO_LINALG_SUCCESS)
            {
                std::cout << statusMessage(status) << std::endl;
                calgo_matrix_destroy(&matrix);
                return;
            }
        }
        std::cout << "b[" << row + 1 << "]: ";
        constants[row] = Input::getDouble();
    }

    status = calgo_solve_gaussian(&matrix, constants.data(), solution.data(), 1e-12);
    calgo_matrix_destroy(&matrix);
    if (status != CALGO_LINALG_SUCCESS)
    {
        std::cout << statusMessage(status) << std::endl;
        return;
    }

    std::cout << "Solution:" << std::endl;
    for (size_t index = 0; index < dimension; index++)
    {
        std::cout << "x" << index + 1 << " = " << solution[index] << std::endl;
    }
}
