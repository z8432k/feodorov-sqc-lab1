#include <gauss.h>
#include <math.h>


void gauss_init(const size_t size, const double *d_matrix, const double *d_vector, gsl_matrix **matrix, gsl_vector **vector, gsl_vector **result) {
    *matrix = gsl_matrix_alloc(size, size);
    *vector = gsl_vector_alloc(size);
    *result = gsl_vector_alloc(size);

    // Init matrix
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            gsl_matrix_set(*matrix, i, j, d_matrix[i * size + j]);
        }
    }

    // Init vector
    for (size_t j = 0; j < size; j++) {
        gsl_vector_set(*vector, j, d_vector[j]);
    }
}

void gauss_print(size_t size, gsl_vector *result) {
    printf("Result:\n");

    for (size_t i = 0; i < size; i++) {
        printf("%zu - %f\n", i, gsl_vector_get(result, i));
    }
}

int gauss_check(const size_t size, const double *d_matrix, const double *d_vector, gsl_vector *result) {
    printf("\nCheck:\n");

    for (size_t row = 0; row < size; row++) {
        double sum = 0;

        for (size_t col = 0; col < size; col++) {
          sum += d_matrix[row * size + col] * gsl_vector_get(result, col);
        }

        if (fabs(d_vector[row] - sum) > EPSILON) {
            goto err;
        }

        printf("%f = %f\n", sum, d_vector[row]);
    }

    return 1;

    err:
    printf("\t fail.\n");

    return 0;
}

int gauss(const size_t size, gsl_matrix *matrix, gsl_vector *vector, gsl_vector *result, double *det) {
    // Gauss

    // Forward

    // Steps by equations
    size_t swap_counter = 0;
    for (size_t step = 0; step < size - 1; step++) {


        // Walk by matrix rows
        for (size_t eq_idx = step + 1; eq_idx < size; eq_idx++) {
            // Multiplier

            {
                // Get vector column from submatrix
                size_t subcol_size = size - eq_idx;
                gsl_vector_view subcol = gsl_matrix_subcolumn(matrix, eq_idx, eq_idx, subcol_size);

                // Find max idx
                gsl_vector *subcol_copy = gsl_vector_alloc(subcol_size);
                gsl_vector_memcpy(subcol_copy, &subcol.vector);
                for (size_t i = 0; i < subcol_size; i++) {
                    gsl_vector_set(subcol_copy, i, fabs(gsl_vector_get(&subcol.vector, i)));
                }
                size_t eq_max_idx = gsl_vector_max_index(&subcol.vector) + eq_idx;

                // swap rows
                double cell = gsl_matrix_get(matrix, eq_max_idx, eq_idx);
                if (cell == 0) {
                    goto err;
                }
                else if (eq_idx != eq_max_idx) {
                    gsl_matrix_swap_rows(matrix, eq_idx, eq_max_idx);
                    gsl_vector_swap_elements(vector, eq_idx, eq_max_idx);

                    // gsl_matrix_swap_rows(orig_matrix, eq_idx, eq_max_idx);
                    // gsl_vector_swap_elements(orig_vector, eq_idx, eq_max_idx);

                    swap_counter++;
                }
            }

            double multiplier = gsl_matrix_get(matrix, eq_idx, step) / gsl_matrix_get(matrix, step, step);

            gsl_matrix_set(matrix, eq_idx, step, 0);

            // Update vector value
            double vector_val = gsl_vector_get(vector, eq_idx) - multiplier * gsl_vector_get(vector, step);
            gsl_vector_set(vector, eq_idx, vector_val);

            // Walk by eq cells
            for (size_t col = step + 1; col < size; col++) {
                double cell_val = gsl_matrix_get(matrix, eq_idx, col) - multiplier * gsl_matrix_get(matrix, step, col);

                gsl_matrix_set(matrix, eq_idx, col, cell_val);
            }
        }
    }

    // /Forward

    // det

    *det = 1;
    for (size_t i = 0; i < size; i++) {
        *det *= gsl_matrix_get(matrix, i, i);
    }
    if (swap_counter % 2 != 0) {
        *det *= -1;
    }


    // => printf("det = %f\n\n", det);

    // /det

    // Back

    for (ssize_t eq_idx = (ssize_t) size - 1; eq_idx >= 0; eq_idx--) { //1
        double sum = 0;

        for (size_t col = eq_idx + 1; col <= size - 1; col++) { // 2
            sum += gsl_matrix_get(matrix, eq_idx, col) * gsl_vector_get(result, col);
        }

        gsl_vector_set(result, eq_idx, (gsl_vector_get(vector, eq_idx) - sum) / gsl_matrix_get(matrix, eq_idx, eq_idx));
    }

    // /Back

    // /Gauss

    return 1;

    err:

    return 0;
}
