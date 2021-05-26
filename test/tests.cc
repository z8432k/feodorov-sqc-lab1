#include <gtest/gtest.h>
#include <gauss.h>
#include <cstdlib>

#define SOLVE(m, v, s) \
    gsl_matrix *matrix; \
    gsl_vector *vector; \
    gsl_vector *result; \
    double det = 0; \
    gauss_init(s, m, v, &matrix, &vector, &result); \
    int pass = gauss(s, matrix, vector, result, &det); \
    gauss_print(3, result); \
    int check = gauss_check(s, m, v, result); \
    gsl_matrix_free(matrix); \
    gsl_vector_free(vector); \
    gsl_vector_free(result);


TEST(Gauss, Simple3) {
    const double d_matrix[] = {
            1., 4., 2.1,
            -1., -2., 1.,
            3., 20., 19.
    };
    const double d_vector[] = {8., 3., 71.};

    SOLVE(d_matrix, d_vector, 3);

    ASSERT_TRUE(pass);
    ASSERT_TRUE(check);

}

TEST(Gauss, Simple4) {
    const double d_matrix[] = {
            10., 4., 2.1, 2,
            -1., 5., 3, 0.6,
            3., 0., 19., 8,
            5., 0.,  2., 10
    };
    const double d_vector[] = {8., 3., 2., 10.};

    SOLVE(d_matrix, d_vector, 4);

    ASSERT_TRUE(pass);
    ASSERT_TRUE(check);
}

TEST(Gauss, Big) {
    const size_t size = 100;

    srand((unsigned) time(nullptr));

    auto big_matrix = (double *) malloc(sizeof(double) * size * size);
    auto big_vector = (double *) malloc(sizeof(double) * size);


    for (size_t i = 0; i < size * size; i++) {
        big_matrix[i] = -50 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX / (50 - -50)));;

        if (i < size) {
            big_vector[i] = -50 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX / (50 - -50)));
        }
    }

    SOLVE(big_matrix, big_vector, size);

    ASSERT_TRUE(pass);
    ASSERT_TRUE(check);

    free(big_matrix);
    free(big_vector);
}

TEST(Gauss, Unsolvable) {
    const double d_matrix[] = {
            1., 6.,  3., -2.,
            0, 12., -9.,  8.,
            0., 3., -1.,   1,
             0,  0,   0,   0
    };
    const double d_vector[] = {3., 3., 1., 7.};

    SOLVE(d_matrix, d_vector, 4);

    ASSERT_FALSE(pass);
    ASSERT_FALSE(check);
}

TEST(Gauss, Unit) {

    const double d_matrix[] = {
            1.,  0, 0,
             0, 1., 0,
             0,  0, 1.
    };
    const double d_vector[] = {1., 2., 3.};

    SOLVE(d_matrix, d_vector, 3);

    ASSERT_TRUE(pass);
    ASSERT_TRUE(check);

}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
