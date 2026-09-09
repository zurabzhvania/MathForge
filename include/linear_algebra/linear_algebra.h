#ifndef CALGO_LINEAR_ALGEBRA_H
#define CALGO_LINEAR_ALGEBRA_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    CALGO_LINALG_SUCCESS,
    CALGO_LINALG_INVALID_ARGUMENT,
    CALGO_LINALG_ALLOCATION_FAILURE,
    CALGO_LINALG_DIMENSION_MISMATCH,
    CALGO_LINALG_SINGULAR_MATRIX
} CalgoLinearAlgebraStatus;

typedef struct {
    size_t rows;
    size_t columns;
    double *values;
} CalgoMatrix;

CalgoLinearAlgebraStatus calgo_matrix_init(
    CalgoMatrix *matrix,
    size_t rows,
    size_t columns
);

void calgo_matrix_destroy(CalgoMatrix *matrix);

CalgoLinearAlgebraStatus calgo_matrix_set(
    CalgoMatrix *matrix,
    size_t row,
    size_t column,
    double value
);

CalgoLinearAlgebraStatus calgo_matrix_get(
    const CalgoMatrix *matrix,
    size_t row,
    size_t column,
    double *out_value
);

/* Solve A x = b without changing A or b. Tolerance must be positive. */
CalgoLinearAlgebraStatus calgo_solve_gaussian(
    const CalgoMatrix *coefficients,
    const double *constants,
    double *solution,
    double tolerance
);

#ifdef __cplusplus
}
#endif

#endif
