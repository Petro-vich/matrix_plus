#include "../s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  int check_matrix = s21_check_matrices(1, A);

  if (check_matrix == OK) {
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = A->matrix[j][i];
      }
    }
  }

  return check_matrix;
}
