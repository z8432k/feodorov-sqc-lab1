#ifndef FEODOROV_SQC_LAB1_GAUSS_H
#define FEODOROV_SQC_LAB1_GAUSS_H

#include <gsl/gsl_matrix.h>

#define EPSILON .0000001

#ifdef __cplusplus
extern "C" {
#endif

void gauss_init(size_t size, const double *d_matrix, const double *d_vector, gsl_matrix **matrix, gsl_vector **vector, gsl_vector **result);
int gauss(size_t size, gsl_matrix *matrix, gsl_vector *vector, gsl_vector *result, double *det);
void gauss_print(size_t size, gsl_vector *result);
int gauss_check(size_t size, const double *d_matrix, const double *d_vector, gsl_vector *result);

#ifdef __cplusplus
}
#endif

#endif //FEODOROV_SQC_LAB1_GAUSS_H
