#include "../s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int MatrixCheck = OK;

  if (rows < 1 || columns < 1 || result == NULL) {
    MatrixCheck = INCORRECT_MATRIX;
  } else {
    result->matrix = (double **)malloc(rows * sizeof(double *));
    if (!result->matrix) {
      MatrixCheck = INCORRECT_MATRIX;
    }
    for (int i = 0; MatrixCheck == OK && i < rows; i++) {
      result->matrix[i] = (double *)malloc(columns * sizeof(double));
      if (!result->matrix[i]) {
        MatrixCheck = INCORRECT_MATRIX;
        for (int j = 0; j < i; j++) {
          free(result->matrix[j]);
          result->matrix[j] = NULL;
        }
        free(result->matrix);
        result->matrix = NULL;
        break;
      }
      result->rows = rows;
      result->columns = columns;
    }
  }
  return MatrixCheck;
}
