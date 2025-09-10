#include "../s21_matrix.h"

void s21_remove_matrix(matrix_t *A) {
  if (A != NULL && A->matrix != NULL && A->rows > 1 && A->columns > 1) {
    for (int j = 0; j < A->rows; j++) {
      free(A->matrix[j]);
    }
    free(A->matrix);
    A->matrix = NULL;
  }
}