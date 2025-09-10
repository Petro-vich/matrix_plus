#include "../s21_matrix.h"

void s21_filling_matrix(matrix_t *new_matrix, double number) {
  for (int i = 0; i < new_matrix->rows; i++) {
    for (int j = 0; j < new_matrix->columns; j++) {
      new_matrix->matrix[i][j] = number;
      number = rand() % 100;
    }
  }
}