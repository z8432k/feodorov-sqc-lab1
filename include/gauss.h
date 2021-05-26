#ifndef FEODOROV_SQC_LAB1_GAUSS_H
#define FEODOROV_SQC_LAB1_GAUSS_H

#include <gsl/gsl_matrix.h>
#include <math.h>

#define MATRIX_SIZE 3
#define EPSILON .00001

void gauss_init(double *d_matrix, double *d_vector, gsl_matrix **matrix, gsl_vector **vector, gsl_vector **result);
int gauss(gsl_matrix *matrix, gsl_vector *vector, gsl_vector *result, double *det);
void gauss_print(gsl_vector *result);
int gauss_check(const double *d_matrix, double *d_vector, gsl_vector *result);


#endif //FEODOROV_SQC_LAB1_GAUSS_H
