#include "unit_tests.h"

TEST(MulMatrixTest, CorrectMultiplication) {
  // Arrange
  S21Matrix A(3, 2);
  A(0, 0) = 1; A(0, 1) = 4;
  A(1, 0) = 2; A(1, 1) = 5;
  A(2, 0) = 3; A(2, 1) = 6;

  S21Matrix B(2, 3);
  B(0, 0) = 1; B(0, 1) = -1; B(0, 2) = 1;
  B(1, 0) = 2; B(1, 1) = 3;  B(1, 2) = 4;

  // Act
  A.MulMatrix(B);

  // Assert
  EXPECT_EQ(A(0, 0), 9);
  EXPECT_EQ(A(0, 1), 11);
  EXPECT_EQ(A(0, 2), 17);
  EXPECT_EQ(A(1, 0), 12);
  EXPECT_EQ(A(1, 1), 13);
  EXPECT_EQ(A(1, 2), 22);
  EXPECT_EQ(A(2, 0), 15);
  EXPECT_EQ(A(2, 1), 15);
  EXPECT_EQ(A(2, 2), 27);
}

TEST(MulMatrixTest, IdentityMatrixMultiplication) {
  // Arrange
  S21Matrix A(2, 2);
  A(0, 0) = 1; A(0, 1) = 2;
  A(1, 0) = 3; A(1, 1) = 4;

  S21Matrix B(2, 2);
  B(0, 0) = 1; B(0, 1) = 0;
  B(1, 0) = 0; B(1, 1) = 1;

  S21Matrix expected = A;

  // Act
  A.MulMatrix(B);

  // Assert
  EXPECT_TRUE(A == expected);
}

TEST(MulMatrixTest, Eq_rowsAndcols) {
  // Arrange
  S21Matrix A(3, 2);

  S21Matrix B(3, 2);


  // Assert
  EXPECT_THROW(A.MulMatrix(B), std::invalid_argument);
}