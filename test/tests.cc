#include <gtest/gtest.h>
#include <gauss.h>
#include <cstdlib>

#define SOLVE(m, v) \
    gsl_matrix *matrix; \
    gsl_vector *vector; \
    gsl_vector *result; \
    size_t size = sizeof(v) / sizeof(double); \
    double det = 0; \
    gauss_init(size, m, v, &matrix, &vector, &result); \
    int pass = gauss(size, matrix, vector, result, &det); \
    gauss_print(size, result); \
    int check = gauss_check(size, m, v, result); \
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

    SOLVE(d_matrix, d_vector);

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

    SOLVE(d_matrix, d_vector);

    ASSERT_TRUE(pass);
    ASSERT_TRUE(check);
}

TEST(Gauss, Unsolvable) {
    const double d_matrix[] = {
            1., 6.,  3., -2.,
            0, 12., -9.,  8.,
            0., 3., -1.,   1,
             0,  0,   0,   0
    };
    const double d_vector[] = {3., 3., 1., 7.};

    SOLVE(d_matrix, d_vector);

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

    SOLVE(d_matrix, d_vector);

    ASSERT_TRUE(pass);
    ASSERT_TRUE(check);

}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
