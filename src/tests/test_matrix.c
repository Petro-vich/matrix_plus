#include <check.h>
#include "../s21_matrix.h"

START_TEST(create_matrix_1){

    matrix_t A;
    matrix_t B;

    int result = s21_create_matrix(2, 2, &A);
    int result2 = s21_create_matrix(10,10, &B);
    ck_assert_int_eq(result, OK);
    ck_assert_int_eq(result2, OK);

    s21_remove_matrix(&A); 
    s21_remove_matrix(&B); 

}   
END_TEST

START_TEST(create_matrix_2){

    matrix_t A;
    
    int result = s21_create_matrix(3, 1, &A);
    ck_assert_int_eq(result, OK);
    
    int result2 = s21_create_matrix(-1, 3, &A);
    ck_assert_int_eq(result2, INCORRECT_MATRIX);

    int result3 = s21_create_matrix(3, 3, NULL);
    ck_assert_int_eq(result3, INCORRECT_MATRIX);

}   
END_TEST

START_TEST(remove_matrix_1){
    
    matrix_t A;
    int result = s21_create_matrix(3,3, &A);

    s21_remove_matrix(&A);
    s21_remove_matrix(&A);
    
    ck_assert_ptr_eq(A.matrix, NULL);

    
}
END_TEST

START_TEST(eq_matrix_1){
    matrix_t A;
    matrix_t B;

    s21_create_matrix(3, 3, &A);
    s21_create_matrix(3, 3, &B);

    for (int i = 0; i < A.rows; i++) {
        for (int j = 0; j < A.columns; j++) {
            A.matrix[i][j] = 5;
        }
    }

    for (int i = 0; i < B.rows; i++) {
        for (int j = 0; j < B.columns; j++) {
            B.matrix[i][j] = 5;
        }
    }

    int result1 = s21_eq_matrix(&A, &B);
    ck_assert_int_eq(result1, SUCCESS);
    
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}
END_TEST

END_TEST

START_TEST(eq_matrix_2){
    
    matrix_t A;
    matrix_t B;

    s21_create_matrix(3, 3, &A);
    s21_create_matrix(3, 3, &B);

    s21_filling_matrix(&A, 5);
    s21_filling_matrix(&B, 10);
    
    int result1 = s21_eq_matrix(&A, &B);
    ck_assert_int_eq(result1, FAILURE); 

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_matrix_3){
    
    matrix_t A;
    matrix_t B;

    s21_create_matrix(3, 3, &A);
    s21_create_matrix(3, 2, &B);

    s21_filling_matrix(&A, 5);
    s21_filling_matrix(&B, 5);
    
    int result1 = s21_eq_matrix(&A, &B);
    ck_assert_int_eq(result1, FAILURE); 

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_matrix_4){
    matrix_t A;
    matrix_t B;

    s21_create_matrix(3, 3, &A);
    s21_create_matrix(3, 3, &B);

    s21_filling_matrix(&A, 5);
    s21_filling_matrix(&B, 4);
    
    int result1 = s21_eq_matrix(&A, &B);
    ck_assert_int_eq(result1, FAILURE);
    
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);

}
END_TEST

START_TEST(sum_matrix_1){
    
    matrix_t A;
    matrix_t B;
    matrix_t C;

    s21_create_matrix(3, 3, &A);
    s21_create_matrix(3, 3, &B);
    s21_create_matrix(3, 3, &C);

    s21_filling_matrix(&A, 5);
    s21_filling_matrix(&B, 5);

    int result = s21_sum_matrix(&A, &B, &C);

    ck_assert_int_eq(result, OK);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&C);
    
}
END_TEST

START_TEST(sum_matrix_2){
    
    matrix_t A = {0};
    matrix_t B = {0};
    matrix_t C = {0};

    
    int result = s21_sum_matrix(&A, &B, &C);

    ck_assert_int_eq(result, INCORRECT_MATRIX);
}
END_TEST

START_TEST(sum_matrix_3){
    
    matrix_t A;
    matrix_t B;
    matrix_t C;

    s21_create_matrix(3, 3, &A);
    s21_create_matrix(3, 3, &B);
    s21_create_matrix(3, 4, &C);

    s21_filling_matrix(&A, 5);
    s21_filling_matrix(&B, 5);

    int result = s21_sum_matrix(&A, &B, &C);

    ck_assert_int_eq(result, CALCULATION_ERROR);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&C);

}
END_TEST

START_TEST(sub_matrix_1){
    
    matrix_t A;
    matrix_t B;
    matrix_t C;

    s21_create_matrix(3, 3, &A);
    s21_create_matrix(3, 3, &B);
    s21_create_matrix(3, 3, &C);

    s21_filling_matrix(&A, 5);
    s21_filling_matrix(&B, 5);

    int result = s21_sub_matrix(&A, &B, &C);

    ck_assert_int_eq(result, OK);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&C);
    
}
END_TEST

START_TEST(sub_matrix_2){
    
    matrix_t A = {0};
    matrix_t B = {0};
    matrix_t C = {0};

    
    int result = s21_sub_matrix(&A, &B, &C);

    ck_assert_int_eq(result, INCORRECT_MATRIX);
}
END_TEST

START_TEST(sub_matrix_3){
    
    matrix_t A;
    matrix_t B;
    matrix_t C;

    s21_create_matrix(3, 3, &A);
    s21_create_matrix(3, 3, &B);
    s21_create_matrix(3, 4, &C);

    s21_filling_matrix(&A, 5);
    s21_filling_matrix(&B, 5);

    int result = s21_sub_matrix(&A, &B, &C);

    ck_assert_int_eq(result, CALCULATION_ERROR);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&C);

}
END_TEST

START_TEST (transpose_1) {

    matrix_t A = {};
    matrix_t B;

    s21_create_matrix(5, 8, &A);
    s21_filling_matrix(&A, 5.0);

    int result = s21_transpose(&A, &B);

    ck_assert_int_eq(result, OK);

    s21_remove_matrix(&A);   
    s21_remove_matrix(&B);
}
END_TEST    

START_TEST (transpose_2) {

    matrix_t A = {};
    matrix_t B;

    s21_create_matrix(1, 5, &A);
    s21_filling_matrix(&A, 5.0);

    int result = s21_transpose(&A, &B);

    ck_assert_int_eq(result, OK);

    s21_remove_matrix(&A);   
    s21_remove_matrix(&B);
}
END_TEST

START_TEST (transpose_3) {

    matrix_t A = {};
    matrix_t B;

    s21_create_matrix(5, 1, &A);
    s21_filling_matrix(&A, 5.0);

    int result = s21_transpose(&A, &B);

    ck_assert_int_eq(result, OK);

    s21_remove_matrix(&A);   
    s21_remove_matrix(&B);
}
END_TEST

START_TEST (transpose_4) {

    matrix_t A = {};
    matrix_t B;

    int result = s21_transpose(&A, &B);

    ck_assert_int_eq(result, INCORRECT_MATRIX);

}
END_TEST

















START_TEST(determinant_1) {
  matrix_t A;
  double my_dtr;
  double detRes = 2526440;
  s21_create_matrix(4, 4, &A);

  A.matrix[0][0] = 25;
  A.matrix[0][1] = 16;
  A.matrix[0][2] = 46;
  A.matrix[0][3] = 0;
  A.matrix[1][0] = 45;
  A.matrix[1][1] = 34;
  A.matrix[1][2] = 3;
  A.matrix[1][3] = 41;
  A.matrix[2][0] = 35;
  A.matrix[2][1] = 61;
  A.matrix[2][2] = 34;
  A.matrix[2][3] = 11;
  A.matrix[3][0] = 7;
  A.matrix[3][1] = 3;
  A.matrix[3][2] = 34;
  A.matrix[3][3] = 3;  

  int result = s21_determinant(&A, &my_dtr);
  ck_assert_int_eq(result, OK);
  double rounded_result = round(my_dtr * 1e6) / 1e6;
  ck_assert_double_eq(rounded_result, 1010938);
  s21_remove_matrix(&A);    
}
END_TEST

START_TEST(determinant_2) {
  matrix_t A = {0};
  double detM, detRes = 73055   ;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 25;
  A.matrix[0][1] = 16;
  A.matrix[0][2] = 46;
  A.matrix[1][0] = 45;
  A.matrix[1][1] = 34;
  A.matrix[1][2] = 3;
  A.matrix[2][0] = 35;
  A.matrix[2][1] = 61;
  A.matrix[2][2] = 34;

  int ret = s21_determinant(&A, &detM);
  ck_assert_int_eq(ret, OK);
  ck_assert_int_eq(detRes, detM);
  s21_remove_matrix(&A);
}

START_TEST(determinant_3) {
  matrix_t A = {0};
  double detM, detRes = 48730;
  s21_create_matrix(3, 3, &A);
                                A.matrix[0][0] = 0;
                                A.matrix[0][1] = 16;
                                A.matrix[0][2] = 46;
                                A.matrix[1][0] = 45;
                                A.matrix[1][1] = 34;
                                A.matrix[1][2] = 3;
                                A.matrix[2][0] = 35;
                                A.matrix[2][1] = 61;
                                A.matrix[2][2] = 34;

  int ret = s21_determinant(&A, &detM);
  ck_assert_int_eq(ret, OK);
  ck_assert_int_eq(detRes, detM);
  s21_remove_matrix(&A);
}

START_TEST(determinant_4) {
  matrix_t M_1;
  double detM, detRes = 0;
  s21_create_matrix(3, 3, &M_1);
  M_1.matrix[0][0] = 1;
  M_1.matrix[0][1] = 2;
  M_1.matrix[0][2] = 3;
  M_1.matrix[1][0] = 4;
  M_1.matrix[1][1] = 5;
  M_1.matrix[1][2] = 6;
  M_1.matrix[2][0] = 7;
  M_1.matrix[2][1] = 8;
  M_1.matrix[2][2] = 9;
  int ret = s21_determinant(&M_1, &detM);
  ck_assert_int_eq(ret, OK);
  ck_assert_int_eq(detRes, detM);
  s21_remove_matrix(&M_1);
}
END_TEST

START_TEST(determinant_5) {
  matrix_t A;
  double result;

  s21_create_matrix(1, 1, &A);

  A.matrix[0][0] = 6;

  int ret = s21_determinant(&A, &result);
  ck_assert_int_eq(ret, OK);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_6) {
  matrix_t A = {0};
  double result;
  s21_create_matrix(3, 2, &A);
  int ret = s21_determinant(&A, &result);
  ck_assert_int_eq(ret, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST


START_TEST(determinant_7) {
  matrix_t A = {0};
  double result = 0;
  s21_create_matrix(3, 0, &A);
  int ret = s21_determinant(&A, &result);
  ck_assert_int_eq(ret, INCORRECT_MATRIX);
}
END_TEST

START_TEST(calc_complements_1) {
    matrix_t A;
    matrix_t result;
    
    s21_create_matrix(2, 2, &A);
    A.matrix[0][0] = 1;
    A.matrix[0][1] = 2;
    A.matrix[1][0] = 3;
    A.matrix[1][1] = 4;
    
    int ret = s21_calc_complements(&A, &result);
    ck_assert_int_eq(ret, OK);
    
    
    ck_assert_double_eq(result.matrix[0][0], 4);
    ck_assert_double_eq(result.matrix[0][1], -3);
    ck_assert_double_eq(result.matrix[1][0], -2);
    ck_assert_double_eq(result.matrix[1][1], 1);
    
    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(calc_complements_2) {
    matrix_t A;
    matrix_t result;
    
    s21_create_matrix(3, 3, &A);
    A.matrix[0][0] = 1;
    A.matrix[0][1] = 2;
    A.matrix[0][2] = 3;
    A.matrix[1][0] = 0;
    A.matrix[1][1] = 4;
    A.matrix[1][2] = 2;
    A.matrix[2][0] = 5;
    A.matrix[2][1] = 2;
    A.matrix[2][2] = 1;
    
    int ret = s21_calc_complements(&A, &result);
    ck_assert_int_eq(ret, OK);
    
    
    ck_assert_double_eq(result.matrix[0][0], 0);
    ck_assert_double_eq(result.matrix[0][1], 10);
    ck_assert_double_eq(result.matrix[0][2], -20);
    ck_assert_double_eq(result.matrix[1][0], 4);
    ck_assert_double_eq(result.matrix[1][1], -14);
    ck_assert_double_eq(result.matrix[1][2], 8);
    ck_assert_double_eq(result.matrix[2][0], -8);
    ck_assert_double_eq(result.matrix[2][1], -2);
    ck_assert_double_eq(result.matrix[2][2], 4);
    
    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(calc_complements_3) {
    matrix_t A;
    matrix_t result;
    
    s21_create_matrix(1, 1, &A);
    A.matrix[0][0] = 5;

    
    int ret = s21_calc_complements(&A, &result);
    ck_assert_int_eq(ret, CALCULATION_ERROR);
    
    s21_remove_matrix(&A);
}
END_TEST

START_TEST(calc_complements_4) {
    matrix_t A;
    matrix_t result;
    
    s21_create_matrix(2, 3, &A);
    
    
    int ret = s21_calc_complements(&A, &result);
    ck_assert_int_eq(ret, CALCULATION_ERROR);
    
    s21_remove_matrix(&A);
}
END_TEST

START_TEST(calc_complements_5) {
    matrix_t A;
    matrix_t result;
    
    s21_create_matrix(4, 4, &A);
    A.matrix[0][0] = 1;
    A.matrix[0][1] = 0;
    A.matrix[0][2] = 0;
    A.matrix[0][3] = 0;
    A.matrix[1][0] = 0;
    A.matrix[1][1] = 1;
    A.matrix[1][2] = 0;
    A.matrix[1][3] = 0;
    A.matrix[2][0] = 0;
    A.matrix[2][1] = 0;
    A.matrix[2][2] = 1;
    A.matrix[2][3] = 0;
    A.matrix[3][0] = 0;
    A.matrix[3][1] = 0;
    A.matrix[3][2] = 0;
    A.matrix[3][3] = 1;
    
    int ret = s21_calc_complements(&A, &result);
    ck_assert_int_eq(ret, OK);
    
    
    ck_assert_double_eq(result.matrix[0][0], 1);
    ck_assert_double_eq(result.matrix[1][1], 1);
    ck_assert_double_eq(result.matrix[2][2], 1);
    ck_assert_double_eq(result.matrix[3][3], 1);
    
    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_mult_matrix_3) {
    matrix_t A, B, result;
    s21_create_matrix(2, 2, &A);
    s21_create_matrix(2, 2, &B);
    
    int res = s21_mult_matrix(NULL, &B, &result);
    ck_assert_int_eq(res, 1);
    
    res = s21_mult_matrix(&A, NULL, &result);
    ck_assert_int_eq(res, 1);
    
    res = s21_mult_matrix(&A, &B, NULL);
    ck_assert_int_eq(res, 1);
    
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}

START_TEST(test_mult_matrix_1) {
    matrix_t A, B, result;
    s21_create_matrix(2, 3, &A);
    s21_create_matrix(3, 2, &B);
    
    A.matrix[0][0] = 1; A.matrix[0][1] = 2; A.matrix[0][2] = 3;
    A.matrix[1][0] = 4; A.matrix[1][1] = 5; A.matrix[1][2] = 6;
    
    B.matrix[0][0] = 7;  B.matrix[0][1] = 8;
    B.matrix[1][0] = 9;  B.matrix[1][1] = 10;
    B.matrix[2][0] = 11; B.matrix[2][1] = 12;
    
    int res = s21_mult_matrix(&A, &B, &result);
    
    ck_assert_int_eq(res, 0);
    ck_assert_double_eq_tol(result.matrix[0][0], 58, 1e-6);
    ck_assert_double_eq_tol(result.matrix[0][1], 64, 1e-6);
    ck_assert_double_eq_tol(result.matrix[1][0], 139, 1e-6);
    ck_assert_double_eq_tol(result.matrix[1][1], 154, 1e-6);
    
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&result);
}

START_TEST(test_mult_matrix_2) {
    matrix_t A, B, result;
    s21_create_matrix(2, 2, &A);
    s21_create_matrix(3, 3, &B);
    
    int res = s21_mult_matrix(&A, &B, &result);
    ck_assert_int_eq(res, 2);
    
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_mult_number_1) {
    matrix_t A, result;
    s21_create_matrix(2, 2, &A);

    A.matrix[0][0] = 1; A.matrix[0][1] = 2;
    A.matrix[1][0] = 3; A.matrix[1][1] = 4;
    
    double number = 2.5;
    int res = s21_mult_number(&A, number, &result);
    
    ck_assert_int_eq(res, 0);
    ck_assert_double_eq_tol(result.matrix[0][0], 2.5, 1e-6);
    ck_assert_double_eq_tol(result.matrix[0][1], 5.0, 1e-6);
    ck_assert_double_eq_tol(result.matrix[1][0], 7.5, 1e-6);
    ck_assert_double_eq_tol(result.matrix[1][1], 10.0, 1e-6);
    
    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
}
END_TEST


START_TEST(test_mult_number_2) {
    matrix_t A, result;
    s21_create_matrix(2, 2, &A);

    int res = s21_mult_number(NULL, 2.0, &result);
    ck_assert_int_eq(res, 1);
    
    res = s21_mult_number(&A, 2.0, NULL);
    ck_assert_int_eq(res, 1);
    
    s21_remove_matrix(&A);
}
END_TEST

START_TEST(mult_matrix_1) {
    matrix_t A, B, result;
    s21_create_matrix(2, 3, &A);
    s21_create_matrix(3, 2, &B);
    
    A.matrix[0][0] = 1; A.matrix[0][1] = 2; A.matrix[0][2] = 3;
    A.matrix[1][0] = 4; A.matrix[1][1] = 5; A.matrix[1][2] = 6;
    
    B.matrix[0][0] = 7;  B.matrix[0][1] = 8;
    B.matrix[1][0] = 9;  B.matrix[1][1] = 10;
    B.matrix[2][0] = 11; B.matrix[2][1] = 12;
    
    int res = s21_mult_matrix(&A, &B, &result);
    
    ck_assert_int_eq(res, 0);
    ck_assert_double_eq_tol(result.matrix[0][0], 58, 1e-6);
    ck_assert_double_eq_tol(result.matrix[0][1], 64, 1e-6);
    ck_assert_double_eq_tol(result.matrix[1][0], 139, 1e-6);
    ck_assert_double_eq_tol(result.matrix[1][1], 154, 1e-6);
    
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&result);
}

START_TEST(mult_matrix_2) {
    matrix_t A, B, result;
    s21_create_matrix(2, 2, &A);
    s21_create_matrix(3, 3, &B);
    
    int res = s21_mult_matrix(&A, &B, &result);
    ck_assert_int_eq(res, 2);
    
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}

START_TEST(mult_matrix_3) {
    matrix_t A, B, result;
    s21_create_matrix(2, 2, &A);
    s21_create_matrix(2, 2, &B);
    
    int res = s21_mult_matrix(NULL, &B, &result);
    ck_assert_int_eq(res, 1);
    
    res = s21_mult_matrix(&A, NULL, &result);
    ck_assert_int_eq(res, 1);
    
    res = s21_mult_matrix(&A, &B, NULL);
    ck_assert_int_eq(res, 1);
    
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}

START_TEST(mult_matrix_4) {
    matrix_t A, B, result;
    s21_create_matrix(3, 3, &A);
    s21_create_matrix(3, 3, &B);
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            A.matrix[i][j] = 1;
            B.matrix[i][j] = 1;
        }
    }
    
    int res = s21_mult_matrix(&A, &B, &result);
    ck_assert_int_eq(res, 0);
    ck_assert_double_eq_tol(result.matrix[0][0], 3, 1e-6);
    
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&result);
}

START_TEST(mult_matrix_5) {
    matrix_t A, B, result;
    s21_create_matrix(1, 3, &A);
    s21_create_matrix(3, 1, &B);
    
    A.matrix[0][0] = 1; A.matrix[0][1] = 2; A.matrix[0][2] = 3;
    B.matrix[0][0] = 4; B.matrix[1][0] = 5; B.matrix[2][0] = 6;
    
    int res = s21_mult_matrix(&A, &B, &result);
    
    ck_assert_int_eq(res, 0);
    ck_assert_double_eq_tol(result.matrix[0][0], 32, 1e-6);
    
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&result);
}



    Suite *matrix_suite(void){
    Suite *s;
    TCase *tc_core;

    s = suite_create("s21_matrix");
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, create_matrix_1);
    tcase_add_test(tc_core, create_matrix_2);
    tcase_add_test(tc_core, remove_matrix_1);
    tcase_add_test(tc_core, eq_matrix_1);
    tcase_add_test(tc_core, eq_matrix_2);
    tcase_add_test(tc_core, eq_matrix_3);
    tcase_add_test(tc_core, eq_matrix_4);
    tcase_add_test(tc_core, sum_matrix_1);
    tcase_add_test(tc_core, sum_matrix_2);
    tcase_add_test(tc_core, sum_matrix_3);
    tcase_add_test(tc_core, sub_matrix_1);
    tcase_add_test(tc_core, sub_matrix_2);
    tcase_add_test(tc_core, sub_matrix_3);
    tcase_add_test(tc_core, transpose_1);
    tcase_add_test(tc_core, transpose_2);
    tcase_add_test(tc_core, transpose_3);
    tcase_add_test(tc_core, transpose_4);
    tcase_add_test(tc_core, determinant_1);
    tcase_add_test(tc_core, determinant_2);
    tcase_add_test(tc_core, determinant_3);
    tcase_add_test(tc_core, determinant_4);
    tcase_add_test(tc_core, determinant_5);
    tcase_add_test(tc_core, determinant_6);
    tcase_add_test(tc_core, determinant_7);
    tcase_add_test(tc_core, calc_complements_1);
    tcase_add_test(tc_core, calc_complements_2);
    tcase_add_test(tc_core, calc_complements_3);
    tcase_add_test(tc_core, calc_complements_4);
    tcase_add_test(tc_core, test_mult_matrix_1);
    tcase_add_test(tc_core, test_mult_matrix_2);
    tcase_add_test(tc_core, test_mult_matrix_3);    
    tcase_add_test(tc_core, test_mult_number_1);  
    tcase_add_test(tc_core, test_mult_number_2);        

    suite_add_tcase(s, tc_core);

    return s;
}

int main(void){
    Suite *s = matrix_suite();
    SRunner *sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    srunner_free(sr);
    return 0;
}
