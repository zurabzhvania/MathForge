#include <linear_algebra/linear_algebra.h>

#include <math.h>
#include <stdint.h>
#include <stdlib.h>

static int matrix_is_valid(const CalgoMatrix *matrix) {
    return matrix != NULL && matrix->values != NULL &&
           matrix->rows > 0 && matrix->columns > 0;
}

static size_t index_of(const CalgoMatrix *matrix, size_t row, size_t column) {
    return row * matrix->columns + column;
}

CalgoLinearAlgebraStatus calgo_matrix_init(
    CalgoMatrix *matrix,
    size_t rows,
    size_t columns
) {
    size_t entries;

    if (matrix == NULL || rows == 0 || columns == 0 || rows > SIZE_MAX / columns) {
        return CALGO_LINALG_INVALID_ARGUMENT;
    }
    entries = rows * columns;
    if (entries > SIZE_MAX / sizeof(*matrix->values)) {
        return CALGO_LINALG_INVALID_ARGUMENT;
    }

    matrix->values = calloc(entries, sizeof(*matrix->values));
    if (matrix->values == NULL) {
        matrix->rows = 0;
        matrix->columns = 0;
        return CALGO_LINALG_ALLOCATION_FAILURE;
    }
    matrix->rows = rows;
    matrix->columns = columns;
    return CALGO_LINALG_SUCCESS;
}

void calgo_matrix_destroy(CalgoMatrix *matrix) {
    if (matrix == NULL) {
        return;
    }
    free(matrix->values);
    matrix->values = NULL;
    matrix->rows = 0;
    matrix->columns = 0;
}

CalgoLinearAlgebraStatus calgo_matrix_set(
    CalgoMatrix *matrix,
    size_t row,
    size_t column,
    double value
) {
    if (!matrix_is_valid(matrix) || row >= matrix->rows || column >= matrix->columns ||
        !isfinite(value)) {
        return CALGO_LINALG_INVALID_ARGUMENT;
    }
    matrix->values[index_of(matrix, row, column)] = value;
    return CALGO_LINALG_SUCCESS;
}

CalgoLinearAlgebraStatus calgo_matrix_get(
    const CalgoMatrix *matrix,
    size_t row,
    size_t column,
    double *out_value
) {
    if (!matrix_is_valid(matrix) || out_value == NULL || row >= matrix->rows ||
        column >= matrix->columns) {
        return CALGO_LINALG_INVALID_ARGUMENT;
    }
    *out_value = matrix->values[index_of(matrix, row, column)];
    return CALGO_LINALG_SUCCESS;
}

CalgoLinearAlgebraStatus calgo_solve_gaussian(
    const CalgoMatrix *coefficients,
    const double *constants,
    double *solution,
    double tolerance
) {
    size_t dimension;
    size_t width;
    size_t row;
    double *augmented;

    if (!matrix_is_valid(coefficients) || constants == NULL || solution == NULL ||
        !isfinite(tolerance) || tolerance <= 0.0) {
        return CALGO_LINALG_INVALID_ARGUMENT;
    }
    if (coefficients->rows != coefficients->columns) {
        return CALGO_LINALG_DIMENSION_MISMATCH;
    }

    dimension = coefficients->rows;
    if (dimension > SIZE_MAX - 1) {
        return CALGO_LINALG_INVALID_ARGUMENT;
    }
    width = dimension + 1;
    if (dimension > SIZE_MAX / width || dimension * width > SIZE_MAX / sizeof(*augmented)) {
        return CALGO_LINALG_INVALID_ARGUMENT;
    }
    augmented = malloc(dimension * width * sizeof(*augmented));
    if (augmented == NULL) {
        return CALGO_LINALG_ALLOCATION_FAILURE;
    }

    for (row = 0; row < dimension; row++) {
        size_t column;

        if (!isfinite(constants[row])) {
            free(augmented);
            return CALGO_LINALG_INVALID_ARGUMENT;
        }
        for (column = 0; column < dimension; column++) {
            double value = coefficients->values[index_of(coefficients, row, column)];

            if (!isfinite(value)) {
                free(augmented);
                return CALGO_LINALG_INVALID_ARGUMENT;
            }
            augmented[row * width + column] = value;
        }
        augmented[row * width + dimension] = constants[row];
    }

    for (size_t pivot = 0; pivot < dimension; pivot++) {
        size_t pivot_row = pivot;
        double largest = fabs(augmented[pivot * width + pivot]);

        for (row = pivot + 1; row < dimension; row++) {
            double candidate = fabs(augmented[row * width + pivot]);

            if (candidate > largest) {
                largest = candidate;
                pivot_row = row;
            }
        }
        if (largest <= tolerance) {
            free(augmented);
            return CALGO_LINALG_SINGULAR_MATRIX;
        }
        if (pivot_row != pivot) {
            for (size_t column = pivot; column < width; column++) {
                double temporary = augmented[pivot * width + column];
                augmented[pivot * width + column] = augmented[pivot_row * width + column];
                augmented[pivot_row * width + column] = temporary;
            }
        }

        for (row = pivot + 1; row < dimension; row++) {
            double factor = augmented[row * width + pivot] / augmented[pivot * width + pivot];

            augmented[row * width + pivot] = 0.0;
            for (size_t column = pivot + 1; column < width; column++) {
                augmented[row * width + column] -= factor * augmented[pivot * width + column];
            }
        }
    }

    for (size_t offset = 0; offset < dimension; offset++) {
        size_t current = dimension - 1 - offset;
        double sum = augmented[current * width + dimension];

        for (size_t column = current + 1; column < dimension; column++) {
            sum -= augmented[current * width + column] * solution[column];
        }
        solution[current] = sum / augmented[current * width + current];
    }

    free(augmented);
    return CALGO_LINALG_SUCCESS;
}
