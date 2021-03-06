#include "matrixlib.h"
#include "stdio.h"
#include "time.h"

int main(void) {

  init_genrand64(time(NULL));

  printf("Attempting to create a 3 by 3 matrix... \n");

  MatrixSU3 matrix1 = allocateRandomSU3(0.5);
  printMatrix(matrix1);

  MatrixSU3 inverse = conjugate(matrix1);
  printMatrix(inverse);
  printf("%f + %fi \n", creal(determinant(matrix1)), cimag(determinant(matrix1)));
  printf("%f + %fi \n", creal(determinant(inverse)), cimag(determinant(inverse)));

  multiply(inverse, matrix1);
  printMatrix(inverse);

  free(matrix1); free(inverse);

  return 0;
}
