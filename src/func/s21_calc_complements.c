#include "../s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (A->rows != A->columns || A->rows < 2) {
    return CALCULATION_ERROR;
  }

  s21_create_matrix(A->rows, A->columns, result);
  s21_check_matrices(2, A, result);

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      matrix_t minor;
      s21_create_matrix(A->rows - 1, A->columns - 1, &minor);

      for (int m = 0, p = 0; m < A->rows; m++) {
        if (m == i) continue;
        for (int n = 0, q = 0; n < A->columns; n++) {
          if (n == j) continue;
          minor.matrix[p][q] = A->matrix[m][n];
          q++;
        }
        p++;
      }

      double minor_det;

      s21_determinant(&minor, &minor_det);

      result->matrix[i][j] = ((i + j) % 2 == 0 ? 1 : -1) * minor_det;

      s21_remove_matrix(&minor);
    }
  }
  return OK;
}
