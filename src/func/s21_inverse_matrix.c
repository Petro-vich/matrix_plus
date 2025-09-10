#include "../s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result){
    matrix_t matrix_calc;
    
    if (A->rows != A->columns || A->rows < 2) {
        return CALCULATION_ERROR;
    }
    s21_check_matrices(2, A, result);

    int status_matrix = s21_calc_complements(A, &matrix_calc);
    
    if (status_matrix == OK) {
        s21_transpose(&matrix_calc, result);
    }
    
    return status_matrix;
}
