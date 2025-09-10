#include "unit_tests.h"

TEST(S21MatrixDef, Create_0) {
  S21Matrix A;
  S21Matrix B(3, 4);
  S21Matrix C(3, 4);

  B.filling_matrix(12, 3.7, 2.3, 3.3,
                                  5.4, 2.2, 3.3,
                                  4.2, 4.2, 2.3,
                                  3.4, 5.3, 2.4);
  
  C.filling_matrix(12, 3.7, 2.3, 3.3,
                                  5.4, 2.2, 3.3,
                                  4.2, 4.2, 2.3,
                                  3.4, 5.3, 2.4);

  EXPECT_EQ(A.get_cols(), 0);
  EXPECT_EQ(A.get_rows(), 0);
  EXPECT_TRUE(B == C);
}

TEST(S21MatrixDef, Copy_0) {
  S21Matrix A(10, 10);
  S21Matrix B = A;
}

TEST(S21MatrixDef, GetSet_0) {
  S21Matrix A(10, 10);

  A.set_rows(5);
  A.set_cols(5);
  A.set_rows(10);
  A.set_cols(10);

  // double rows = A.get_rows();
  // double cols = A.get_cols();
  A.get_rows();
  A.get_cols();
  
}

TEST(S21MatrixDef, Move_0) {
  S21Matrix B(3, 3);
  B.filling_matrix(9, 3.8, 2.3, 3.3,
                                  5.4, 2.2, 3.3,
                                  4.2, 4.2, 2.3);
  
  S21Matrix A = std::move(B);
  EXPECT_EQ(A(0, 0), 3.8);
  EXPECT_EQ(A(0, 1), 2.3);
  EXPECT_EQ(A(0, 2), 3.3);
  EXPECT_EQ(A(1, 0), 5.4);
  EXPECT_EQ(A(1, 1), 2.2);
  EXPECT_EQ(A(1, 2), 3.3);
  EXPECT_EQ(A(2, 0), 4.2);
  EXPECT_EQ(A(2, 1), 4.2);
  EXPECT_EQ(A(2, 2), 2.3);


}

TEST(S21MatrixTest_transponce, transponce_0) {
  S21Matrix A(3, 1);
  A.filling_matrix(3, 1.0,
                                  1.0,
                                  1.0);
  S21Matrix B = A.Transpose();

  S21Matrix Expected(1, 3);
  Expected.filling_matrix(3, 1.0, 1.0, 1.0);
  B.print_matrix();
  Expected.print_matrix();
  EXPECT_TRUE(B == Expected);

}

// TEST(S21MatrixTest_operator, brackets_0) {
//   S21Matrix A(3, 3);
//   const S21Matrix B(3, 3);

// EXPECT_THROW(A(4, 4) = 5, std::out_of_range);
// EXPECT_THROW(B(4, 4) = 5, std::out_of_range);

// }

TEST(S21MatrixTest_EqMatrix, Eq_Matrix_0) {
  S21Matrix A(3, 3);
  S21Matrix B(3, 3);

  A.filling_matrix(9, 1.0, 2.0, 3.0,
                                  4.0, 5.0, 6.0,
                                  7.0, 8.0, 9.0);

  B.filling_matrix(9, 1.0, 2.0, 3.0,
                                  4.0, 5.0, 6.0,
                                  7.0, 8.0, 9.0);

  A(0, 0) = 0.00000000000000000000005;    
  B(0, 0) = 0.00000000000000000000006;
  EXPECT_TRUE(A == B);
}