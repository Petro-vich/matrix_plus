#ifndef S21_MATRIX_PLUS_H
#define S21_MATRIX_PLUS_H

#include <math.h>
#include <stdarg.h>

#include <iostream>
class S21Matrix {
 private:
  int rows_, cols_;
  double** matrix_;

 public:
  /*=======================================SET/GET==========================================*/

  int get_rows();
  int get_cols();
  void set_rows(int rows);
  void set_cols(int cols);

  /*===================================Default
   * constructor===================================*/
  S21Matrix() noexcept;
  S21Matrix(int rows, int cols);
  ~S21Matrix();
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  /*===================================Operations on
   * matrices================================*/
  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  double Determinant();
  S21Matrix CalcComplements();
  S21Matrix GetMinor(const S21Matrix& matrix, int row, int col);
  S21Matrix InverseMatrix();
  /*==================================Opeartor
   * overload==========================================*/
  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator*(double num);

  S21Matrix operator+=(const S21Matrix& other);
  S21Matrix operator-=(const S21Matrix& other);
  S21Matrix operator*=(const S21Matrix& other);
  S21Matrix operator*=(const double num);

  bool operator==(const S21Matrix& other);
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator=(S21Matrix&& other);

  double& operator()(int i, int j);
  double operator()(int i, int j) const;
  /*======================================Helpers================================================*/
  void SwapRows(int row1, int row2);
  void resize(int rows, int cols);
  void filling_matrix(int matrix_size, ...);
  void print_matrix();
  int matrix_size = rows_ * cols_;
};

#endif