#include "../s21_matrix.h"

int s21_check_matrices(int count, ...) {
  if (count < 1) return INCORRECT_MATRIX;

  va_list args;
  va_start(args, count);
  double rows_matrix;
  double columns_matrix;

  for (int i = 0; i < 1; i++) {
    matrix_t *matrix = va_arg(args, matrix_t *);

    if (!matrix || !matrix->matrix) {
      va_end(args);
      return INCORRECT_MATRIX;
    }
    rows_matrix = matrix->rows;
    columns_matrix = matrix->columns;
  }

  for (int j = 1; j < count; j++) {
    matrix_t *matrix = va_arg(args, matrix_t *);
    if (matrix->rows != rows_matrix || matrix->columns != columns_matrix) {
      va_end(args);
      return CALCULATION_ERROR;
    }
  }
  va_end(args);
  return OK;
}