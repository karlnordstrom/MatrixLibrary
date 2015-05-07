#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include "mt64.h"

typedef double complex *MatrixSU3;

// Return random number between a and b
double uniform(const double a, const double b);

// Allocates an SU(3) matrix set to identity by default
MatrixSU3 allocateSU3(void);

// Allocates a random SU(3) matrix
MatrixSU3 allocateRandomSU3(const double epsilon);

// Set matrix to identity
void setIdentity(MatrixSU3 matrix);

// Set matrix to a random SU(3)
void setRandomSU3(MatrixSU3 matrix, const double epsilon);

// Print the matrix supplied
void printMatrix(const MatrixSU3 matrix);

// Clone the matrix supplied
MatrixSU3 cloneMatrix(const MatrixSU3 matrix);

// Multiply a by b, storing result in a, leaving b unchanged
void multiply(MatrixSU3 a, const MatrixSU3 b);

// Multiply a by the number b
void multiplyScalar(MatrixSU3 a, const double complex b);

// Add a and b, storing result in a, leaving b unchanged
void add(MatrixSU3 a, const MatrixSU3 b);

// Subtract a and b, storing result in a, leaving b unchanged
void subtract(MatrixSU3 a, const MatrixSU3 b);

// Return the inverse of matrix
double complex determinant(const MatrixSU3 a);

// Return the trace of matrix
double complex trace(const MatrixSU3 a);

// Return the inverse of matrix
MatrixSU3 invert(const MatrixSU3 matrix);

// Return the conjugate of matrix
MatrixSU3 conjugate(const MatrixSU3 matrix);
