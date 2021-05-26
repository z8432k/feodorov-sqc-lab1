#include <gauss.h>

static double d_matrix[MATRIX_SIZE * MATRIX_SIZE] = {
    1., 4., 2.1,
    -1., -2., 1.,
    3., 20., 19.
};
static double d_vector[] = {8., 3., 71.};

int main(void) {
    gsl_matrix *matrix;
    gsl_vector *vector;
    gsl_vector *result;

    double det = 0;

    gauss_init(d_matrix, d_vector, &matrix, &vector, &result);

    gauss(matrix, vector, result, &det);

    gauss_print(result);

    int check = gauss_check(d_matrix, d_vector, result);

    if (!check) {
        fprintf(stderr, "No decision.\n");
    }

    gsl_matrix_free(matrix);
    gsl_vector_free(vector);
    gsl_vector_free(result);
}

