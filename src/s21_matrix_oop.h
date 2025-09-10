#ifndef S21_MATRIX_PLUS_H
#define S21_MATRIX_PLUS_H

#include <algorithm>
#include <cmath>
#include <cstdarg>
#include <iostream>
class S21Matrix {
 private:
  int rows_, cols_;
  double** matrix_;

 public:
  /*=======================================SET/GET==========================================*/
  int get_rows() const noexcept;
  int get_cols() const noexcept;
  void set_rows(int rows);
  void set_cols(int cols);
  /*===================================Defaultconstructor===================================*/
  S21Matrix() noexcept;
  S21Matrix(int rows, int cols);
  ~S21Matrix() noexcept;
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  /*==========================Operations on matrices=====================*/
  bool EqMatrix(const S21Matrix& other) const;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num) noexcept;
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose() const;
  double Determinant() const;
  S21Matrix CalcComplements() const;
  S21Matrix GetMinor(const S21Matrix& matrix, int row, int col) const;
  S21Matrix InverseMatrix() const;

  /*==========================Opeartor overload===========================*/

  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix operator*(const S21Matrix& other) const;
  S21Matrix operator*(double num) const;

  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double num);

  bool operator==(const S21Matrix& other) const;
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator=(S21Matrix&& other);

  double& operator()(int i, int j);
  double operator()(int i, int j) const;
  /*======================================Helpers=================================================*/
  void SwapRows(int row1, int row2);
  void resize(int rows, int cols);
  void filling_matrix(int matrix_size, ...);
  void print_matrix();
};
#endif