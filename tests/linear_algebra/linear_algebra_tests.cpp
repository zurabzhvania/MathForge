#include <cassert>
#include <cmath>

#include <linear_algebra/linear_algebra.h>

namespace
{
    bool nearlyEqual(double actual, double expected)
    {
        return std::abs(actual - expected) < 1e-12;
    }
}

int main()
{
    CalgoMatrix matrix = {0, 0, nullptr};
    double constants[] = {5.0, 1.0};
    double solution[2];

    assert(calgo_matrix_init(&matrix, 2, 2) == CALGO_LINALG_SUCCESS);
    assert(calgo_matrix_set(&matrix, 0, 0, 2.0) == CALGO_LINALG_SUCCESS);
    assert(calgo_matrix_set(&matrix, 0, 1, 1.0) == CALGO_LINALG_SUCCESS);
    assert(calgo_matrix_set(&matrix, 1, 0, 1.0) == CALGO_LINALG_SUCCESS);
    assert(calgo_matrix_set(&matrix, 1, 1, -1.0) == CALGO_LINALG_SUCCESS);
    assert(calgo_solve_gaussian(&matrix, constants, solution, 1e-12) == CALGO_LINALG_SUCCESS);
    assert(nearlyEqual(solution[0], 2.0));
    assert(nearlyEqual(solution[1], 1.0));

    assert(calgo_matrix_set(&matrix, 1, 0, 2.0) == CALGO_LINALG_SUCCESS);
    assert(calgo_matrix_set(&matrix, 1, 1, 1.0) == CALGO_LINALG_SUCCESS);
    assert(calgo_solve_gaussian(&matrix, constants, solution, 1e-12) == CALGO_LINALG_SINGULAR_MATRIX);
    calgo_matrix_destroy(&matrix);
    return 0;
}
