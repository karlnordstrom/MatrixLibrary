#include "matrixlib.h"

// Return random number between a and b
double uniform(const double a, const double b) {
  return a + (b-a) * genrand64_real1();
}

// Allocates an SU(3) matrix set to identity by default
MatrixSU3 allocateSU3(void) {
  MatrixSU3 matrix = (MatrixSU3) calloc (9, sizeof(double complex)); // calloc initialises to 0.
  for(size_t i = 0; i < 3; ++i) *(matrix + 4*i) = 1. + 0. * I;
  return matrix;
}

// Allocates a random SU(3) matrix
MatrixSU3 allocateRandomSU3(const double epsilon) {
  MatrixSU3 matrix = (MatrixSU3) malloc (9 * sizeof(double complex));
  *(matrix + 0) = uniform(-1,1) + uniform(-1,1) * I;
  *(matrix + 1) = uniform(-1,1) + uniform(-1,1) * I;
  *(matrix + 2) = uniform(-1,1) + uniform(-1,1) * I;
  *(matrix + 3) = uniform(-1,1) + uniform(-1,1) * I;
  *(matrix + 4) = uniform(-1,1) + uniform(-1,1) * I;
  *(matrix + 5) = uniform(-1,1) + uniform(-1,1) * I;
  *(matrix + 6) = uniform(-1,1) + uniform(-1,1) * I;
  *(matrix + 7) = uniform(-1,1) + uniform(-1,1) * I;
  *(matrix + 8) = uniform(-1,1) + uniform(-1,1) * I;
  double norm = sqrt(cabs(*(matrix + 0))*cabs(*(matrix + 0)) + cabs(*(matrix + 3))*cabs(*(matrix + 3)) + cabs(*(matrix + 6))*cabs(*(matrix + 6)));
  *(matrix + 0) /= norm;
  *(matrix + 3) /= norm;
  *(matrix + 6) /= norm;
  double complex innerprod = *(matrix + 1) * conj(*(matrix + 0)) + *(matrix + 4) * conj(*(matrix + 3)) + *(matrix + 7) * conj(*(matrix + 6));
  *(matrix + 1) -= innerprod * *(matrix + 0);
  *(matrix + 4) -= innerprod * *(matrix + 3);
  *(matrix + 7) -= innerprod * *(matrix + 6);
  double complex norm1 = sqrt(cabs(*(matrix + 1))*cabs(*(matrix + 1)) + cabs(*(matrix + 4))*cabs(*(matrix + 4)) + cabs(*(matrix + 7))*cabs(*(matrix + 7)));
  *(matrix + 1) /= norm1;
  *(matrix + 4) /= norm1;
  *(matrix + 7) /= norm1;
  double complex innerprod1 = *(matrix + 2) * conj(*(matrix + 0)) + *(matrix + 5) * conj(*(matrix + 3)) + *(matrix + 8) * conj(*(matrix + 6));
  double complex innerprod2 = *(matrix + 2) * conj(*(matrix + 1)) + *(matrix + 5) * conj(*(matrix + 4)) + *(matrix + 8) * conj(*(matrix + 7));
  *(matrix + 2) -= (innerprod1 * *(matrix + 0) + innerprod2 * *(matrix + 1));
  *(matrix + 5) -= (innerprod1 * *(matrix + 3) + innerprod2 * *(matrix + 4));
  *(matrix + 8) -= (innerprod1 * *(matrix + 6) + innerprod2 * *(matrix + 7));
  double complex norm2 = sqrt(cabs(*(matrix + 2))*cabs(*(matrix + 2)) + cabs(*(matrix + 5))*cabs(*(matrix + 5)) + cabs(*(matrix + 8))*cabs(*(matrix + 8)));
  *(matrix + 2) /= norm2;
  *(matrix + 5) /= norm2;
  *(matrix + 8) /= norm2;
  const double len = cabs(determinant(matrix));
  multiplyScalar(matrix, cpow(1/len,1./3));
  return matrix;
}

// Set matrix to identity
void setIdentity(MatrixSU3 matrix) {
  for(size_t i = 0; i < 9; ++i) {
    if(i == 0 || i == 4 || i == 8) *(matrix + i) = 1. + 0. * I;
    else *(matrix + i) = 0. + 0. * I;
  }
}

// Sets matrix to a random SU(3) matrix
void setRandomSU3(MatrixSU3 matrix, const double epsilon) {
  *(matrix + 0) = uniform(-1,1) + uniform(-1,1) * I;
  *(matrix + 1) = uniform(-1,1) + uniform(-1,1) * I;
  *(matrix + 2) = uniform(-1,1) + uniform(-1,1) * I;
  *(matrix + 3) = uniform(-1,1) + uniform(-1,1) * I;
  *(matrix + 4) = uniform(-1,1) + uniform(-1,1) * I;
  *(matrix + 5) = uniform(-1,1) + uniform(-1,1) * I;
  *(matrix + 6) = uniform(-1,1) + uniform(-1,1) * I;
  *(matrix + 7) = uniform(-1,1) + uniform(-1,1) * I;
  *(matrix + 8) = uniform(-1,1) + uniform(-1,1) * I;
  double norm = sqrt(cabs(*(matrix + 0))*cabs(*(matrix + 0)) + cabs(*(matrix + 3))*cabs(*(matrix + 3)) + cabs(*(matrix + 6))*cabs(*(matrix + 6)));
  *(matrix + 0) /= norm;
  *(matrix + 3) /= norm;
  *(matrix + 6) /= norm;
  double complex innerprod = *(matrix + 1) * conj(*(matrix + 0)) + *(matrix + 4) * conj(*(matrix + 3)) + *(matrix + 7) * conj(*(matrix + 6));
  *(matrix + 1) -= innerprod * *(matrix + 0);
  *(matrix + 4) -= innerprod * *(matrix + 3);
  *(matrix + 7) -= innerprod * *(matrix + 6);
  double complex norm1 = sqrt(cabs(*(matrix + 1))*cabs(*(matrix + 1)) + cabs(*(matrix + 4))*cabs(*(matrix + 4)) + cabs(*(matrix + 7))*cabs(*(matrix + 7)));
  *(matrix + 1) /= norm1;
  *(matrix + 4) /= norm1;
  *(matrix + 7) /= norm1;
  double complex innerprod1 = *(matrix + 2) * conj(*(matrix + 0)) + *(matrix + 5) * conj(*(matrix + 3)) + *(matrix + 8) * conj(*(matrix + 6));
  double complex innerprod2 = *(matrix + 2) * conj(*(matrix + 1)) + *(matrix + 5) * conj(*(matrix + 4)) + *(matrix + 8) * conj(*(matrix + 7));
  *(matrix + 2) -= (innerprod1 * *(matrix + 0) + innerprod2 * *(matrix + 1));
  *(matrix + 5) -= (innerprod1 * *(matrix + 3) + innerprod2 * *(matrix + 4));
  *(matrix + 8) -= (innerprod1 * *(matrix + 6) + innerprod2 * *(matrix + 7));
  double complex norm2 = sqrt(cabs(*(matrix + 2))*cabs(*(matrix + 2)) + cabs(*(matrix + 5))*cabs(*(matrix + 5)) + cabs(*(matrix + 8))*cabs(*(matrix + 8)));
  *(matrix + 2) /= norm2;
  *(matrix + 5) /= norm2;
  *(matrix + 8) /= norm2;
  const double len = cabs(determinant(matrix));
  multiplyScalar(matrix, cpow(1/len,1./3));
}

// Print the matrix
void printMatrix(const MatrixSU3 matrix) {
  for(size_t i = 0; i < 3; ++i) {
    printf("(");
    for(size_t j = 0; j < 3; ++j) {
      printf(" %.2f + %.2f i ", creal(*(matrix + 3*i + j)), cimag(*(matrix + 3*i + j)));
    }
    printf(")\n");
  }
}

MatrixSU3 cloneMatrix(const MatrixSU3 matrix) {
  MatrixSU3 out = (MatrixSU3) malloc (9 * sizeof(double complex));
  for(size_t i = 0; i < 9; ++i) *(out + i) = *(matrix + i);
  return out;
}

// Multiply a by the matrix b, storing result in a, leaving b unchanged
void multiply(MatrixSU3 a, const MatrixSU3 b) {
  double complex tmp[3];
  for(size_t i = 0; i < 3; ++i) {
    for(size_t j = 0; j < 3; ++j) tmp[j] = *(a + 3*i) * *(b + j) + *(a + 3*i + 1) * *(b + 3 + j) + *(a + 3*i + 2) * *(b + 6 + j);
    for(size_t j = 0; j < 3; ++j) *(a + 3*i + j) = tmp[j];
  }
}

// Multiply a by the number b
void multiplyScalar(MatrixSU3 a, const double complex b) {
  for(size_t i = 0; i < 3; ++i) {
    for(size_t j = 0; j < 3; ++j) *(a + 3*i + j) *= b;
  }
}

// Add a and b, storing result in a, leaving b unchanged
void add(MatrixSU3 a, const MatrixSU3 b) {
  for(size_t i = 0; i < 3; ++i) {
    for(size_t j = 0; j < 3; ++j) *(a + 3*i + j) += *(b + 3*i + j);
  }
}

// Subtract a and b, storing result in a, leaving b unchanged
void subtract(MatrixSU3 a, const MatrixSU3 b) {
  for(size_t i = 0; i < 3; ++i) {
    for(size_t j = 0; j < 3; ++j) *(a + 3*i + j) -= *(b + 3*i + j);
  }
}

// Return the determinant of matrix
double complex determinant(const MatrixSU3 a) {
  return *(a) * (*(a+4) * *(a+8) - *(a+5) * *(a+7)) - *(a+1) * (*(a+3) * *(a+8) - *(a+5) * *(a+6)) + *(a+2) * (*(a+3) * *(a+7) - *(a+4) * *(a+6));
}

// Return the trace of matrix
double complex trace(const MatrixSU3 a) {
  return *(a) + *(a+4) + *(a+8);
}

// Return the inverse of matrix
MatrixSU3 invert(const MatrixSU3 matrix) {
  double complex det = determinant(matrix);
  MatrixSU3 inverse = (MatrixSU3) malloc (9 * sizeof(double complex));
  *(inverse + 0) = *(matrix+4) * *(matrix+8) - *(matrix+5) * *(matrix+7);
  *(inverse + 1) = *(matrix+2) * *(matrix+7) - *(matrix+1) * *(matrix+8);
  *(inverse + 2) = *(matrix+1) * *(matrix+5) - *(matrix+2) * *(matrix+4);
  *(inverse + 3) = *(matrix+5) * *(matrix+6) - *(matrix+3) * *(matrix+8);
  *(inverse + 4) = *(matrix+0) * *(matrix+8) - *(matrix+2) * *(matrix+6);
  *(inverse + 5) = *(matrix+2) * *(matrix+3) - *(matrix+0) * *(matrix+5);
  *(inverse + 6) = *(matrix+3) * *(matrix+7) - *(matrix+4) * *(matrix+6);
  *(inverse + 7) = *(matrix+1) * *(matrix+6) - *(matrix+0) * *(matrix+7);
  *(inverse + 8) = *(matrix+0) * *(matrix+4) - *(matrix+1) * *(matrix+3);
  multiplyScalar(inverse, 1/det);
  return inverse;
}

MatrixSU3 conjugate(const MatrixSU3 matrix) {
  MatrixSU3 conjugate = (MatrixSU3) malloc (9 * sizeof(double complex));
  *(conjugate + 0) = conj(*(matrix + 0));
  *(conjugate + 1) = conj(*(matrix + 3));
  *(conjugate + 2) = conj(*(matrix + 6));
  *(conjugate + 3) = conj(*(matrix + 1));
  *(conjugate + 4) = conj(*(matrix + 4));
  *(conjugate + 5) = conj(*(matrix + 7));
  *(conjugate + 6) = conj(*(matrix + 2));
  *(conjugate + 7) = conj(*(matrix + 5));
  *(conjugate + 8) = conj(*(matrix + 8));
  return conjugate;
}

