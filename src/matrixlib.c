#include "matrixlib.h"

// Return random number between a and b
double uniform(const double a, const double b) {
  return a + (b-a) * genrand64_real1();
}

// Allocates an SU(3) matrix set to identity by default
MatrixSU3 allocateSU3(void) {
  MatrixSU3 matrix = (MatrixSU3) calloc (9, sizeof(double complex)); // calloc initialises to 0.
  size_t i = 0;
  while (i < 3) { *(matrix + 4*i) = 1. + 0. * I; ++i; }
  return matrix;
}

// Allocates a random SU(3) matrix
MatrixSU3 allocateRandomSU3(const double epsilon) {
  MatrixSU3 matrix = (MatrixSU3) calloc (9, sizeof(double complex)); // calloc initialises to 0.
  *(matrix + 0) += uniform(-1,1) + 0. * I;
  *(matrix + 1) += uniform(-1,1) + 0. * I;
  *(matrix + 2) += uniform(-1,1) + 0. * I;
  *(matrix + 3) =  *(matrix + 1) + 0. * I;
  *(matrix + 4) += uniform(-1,1) + 0. * I;
  *(matrix + 5) += uniform(-1,1) + 0. * I;
  *(matrix + 6) =  *(matrix + 2) + 0. * I;
  *(matrix + 7) =  *(matrix + 5) + 0. * I;
  *(matrix + 8) += uniform(-1,1) + 0. * I;
  multiplyScalar(matrix, epsilon * I);
  MatrixSU3 identity = allocateSU3();
  add(matrix,identity);
  free(identity);
  double det = determinant(matrix);
  multiplyScalar(matrix, cpow(1/det,1./3));
  return matrix;
}

// Print the matrix
void printMatrix(const MatrixSU3 matrix) {
  size_t i = 0, j = 0;
  while (i < 3) {
    printf("(");
    while(j < 3) {
      printf(" %.2f + %.2f i ", creal(*(matrix + 3*i + j)), cimag(*(matrix + 3*i + j)));
      ++j;
    }
    printf(")\n");
    j = 0;
    ++i;
  }
}

// Multiply a by the matrix b, storing result in a, leaving b unchanged
void multiply(MatrixSU3 a, const MatrixSU3 b) {
  double tmp[3];
  size_t i = 0, j = 0;
  while(i < 3) {
    while(j < 3) { tmp[j] = *(a + 3*i) * *(b + j) + *(a + 3*i + 1) * *(b + 3 + j) + *(a + 3*i + 2) * *(b + 6 + j); ++j; }
    j = 0;
    while(j < 3) { *(a + 3*i + j) = tmp[j]; ++j; }
    j = 0;
    ++i;
  }
}

// Multiply a by the number b
void multiplyScalar(MatrixSU3 a, const double complex b) {
  size_t i = 0, j = 0;
  while(i < 3) {
    while(j < 3) { *(a + 3*i + j) *= b; ++j; }
    j = 0;
    ++i;
  }
}

// Add a and b, storing result in a, leaving b unchanged
void add(MatrixSU3 a, const MatrixSU3 b) {
  size_t i = 0, j = 0;
  while(i < 3) {
    while(j < 3) { *(a + 3*i + j) += *(b + 3*i + j); ++j; }
    j = 0;
    ++i;
  }
}

// Subtract a and b, storing result in a, leaving b unchanged
void subtract(MatrixSU3 a, const MatrixSU3 b) {
  size_t i = 0, j = 0;
  while(i < 3) {
    while(j < 3) { *(a + 3*i + j) -= *(b + 3*i + j); ++j; }
    j = 0;
    ++i;
  }
}

// Return the inverse of matrix
complex double determinant(const MatrixSU3 a) {
  return *(a) * (*(a+4) * *(a+8) - *(a+5) * *(a+7)) - *(a+1) * (*(a+3) * *(a+8) - *(a+5) * *(a+6)) + *(a+2) * (*(a+3) * *(a+7) - *(a+4) * *(a+6));
}

// Return the inverse of matrix
MatrixSU3 invert(const MatrixSU3 matrix) {
  double det = determinant(matrix);
  MatrixSU3 inverse = (MatrixSU3) malloc (9 * sizeof(complex double));
  *(inverse + 0) = *(matrix+4) * *(matrix+8) - *(matrix+5) * *(matrix+7);
  *(inverse + 1) = *(matrix+2) * *(matrix+7) - *(matrix+1) * *(matrix+8);
  *(inverse + 2) = *(matrix+1) * *(matrix+5) - *(matrix+2) * *(matrix+4);
  *(inverse + 3) = *(matrix+5) * *(matrix+6) - *(matrix+3) * *(matrix+8);
  *(inverse + 4) = *(matrix+0) * *(matrix+8) - *(matrix+2) * *(matrix+6);
  *(inverse + 5) = *(matrix+2) * *(matrix+3) - *(matrix+0) * *(matrix+5);
  *(inverse + 6) = *(matrix+3) * *(matrix+7) - *(matrix+4) * *(matrix+6);
  *(inverse + 7) = *(matrix+1) * *(matrix+6) - *(matrix+0) * *(matrix+7);
  *(inverse + 8) = *(matrix+0) * *(matrix+4) - *(matrix+1) * *(matrix+3);
  return inverse;
}
