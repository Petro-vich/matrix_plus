#include "../s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int check_matrix = s21_check_matrices(2, A, B) ? FAILURE : SUCCESS;

  if (check_matrix) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (A->matrix[i][j] != B->matrix[i][j]) {
          check_matrix = FAILURE;
          break;
        }
      }
    }
  }
  return check_matrix;
}