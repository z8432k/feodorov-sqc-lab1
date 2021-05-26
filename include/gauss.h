#ifndef FEODOROV_SQC_LAB1_GAUSS_H
#define FEODOROV_SQC_LAB1_GAUSS_H

#include <gsl/gsl_matrix.h>
#include <math.h>

#define EPSILON .00001

void gauss_init(size_t size, double *d_matrix, double *d_vector, gsl_matrix **matrix, gsl_vector **vector, gsl_vector **result);
int gauss(size_t size, gsl_matrix *matrix, gsl_vector *vector, gsl_vector *result, double *det);
void gauss_print(size_t size, gsl_vector *result);
int gauss_check(size_t size, const double *d_matrix, double *d_vector, gsl_vector *result);


#endif //FEODOROV_SQC_LAB1_GAUSS_H
