#ifndef S21_AUX_FUNC_H
#define S21_AUX_FUNC_H

void s21_print_matrix(matrix_t *  A);
void s21_copy_matrix(matrix_t *A, matrix_t *result);
void s21_filling_matrix(matrix_t *new_matrix, double number);
int s21_memcmp(const void *str1, const void *str2, int n);
int s21_check_matrices(int count, ...);

#endif