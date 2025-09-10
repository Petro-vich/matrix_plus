#include "s21_matrix_oop.h"

#include <iostream>

int S21Matrix::get_rows() const noexcept { return rows_; }

int S21Matrix::get_cols() const noexcept { return cols_; }

void S21Matrix::set_rows(int rows) {
  if (rows != rows_) {
    resize(rows, cols_);
  }
}

void S21Matrix::set_cols(int cols) {
  if (cols != cols_) {
    resize(rows_, cols);
  }
}

S21Matrix::S21Matrix() noexcept : rows_(0), cols_(0), matrix_(nullptr) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
  }
}

S21Matrix::~S21Matrix() noexcept {
  if (matrix_) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
  }
}

S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  matrix_ = new double *[rows_];

  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix &&other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

bool S21Matrix::EqMatrix(const S21Matrix &other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  }

  const double kEpsilon = 1e-6;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      double diff = matrix_[i][j] - other.matrix_[i][j];
      if (fabs(diff) > kEpsilon) {
        return false;
      }
    }
  }
  return true;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("The matrices are not equal");
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("The matrices are not equal");
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) noexcept {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.get_rows()) {
    throw std::invalid_argument(
        "The number of columns of the first matrix must match the number "
        "of rows of the second matrix");
  }

  S21Matrix temp(rows_, other.cols_);
  for (int i = 0; i < temp.rows_; ++i) {
    for (int j = 0; j < temp.cols_; ++j) {
      temp.matrix_[i][j] = 0;
      for (int k = 0; k < cols_; ++k) {
        temp.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }

  *this = std::move(temp);
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix temp(cols_, rows_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      temp.matrix_[j][i] = matrix_[i][j];
    }
  }

  return temp;
}

double S21Matrix::Determinant() const {
  if (rows_ != cols_) {
    throw std::logic_error("Determinant is only defined for square matrices");
  }

  int n = rows_;
  S21Matrix temp(*this);
  double det = 1.0;

  for (int i = 0; i < n; i++) {
    int pivot_row = i;
    for (int j = i + 1; j < n; j++) {
      if (fabs(temp(j, i)) > fabs(temp(pivot_row, i))) {
        pivot_row = j;
      }
    }

    if (fabs(temp(pivot_row, i)) < 1e-9) {
      return 0.0;
    }

    if (pivot_row != i) {
      temp.SwapRows(i, pivot_row);
      det *= -1;
    }

    det *= temp(i, i);
    for (int j = i + 1; j < n; j++) {
      double factor = temp(j, i) / temp(i, i);
      for (int k = i; k < n; k++) {
        temp(j, k) -= factor * temp(i, k);
      }
    }
  }

  return det;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (rows_ != cols_) {
    throw std::invalid_argument("Matrix must be square");
  }

  S21Matrix result(rows_, cols_);

  if (rows_ == 1) {
    result(0, 0) = 1;
    return result;
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      S21Matrix minor = GetMinor(*this, i, j);
      double det = minor.Determinant();
      result(i, j) = det * ((i + j) % 2 == 0 ? 1 : -1);
    }
  }

  return result;
}

S21Matrix S21Matrix::InverseMatrix() const {
  if (rows_ != cols_) {
    throw std::logic_error("Incorrect matrix size for Inverse");
  }

  double det = Determinant();

  if (fabs(det) < 1e-7) {
    throw std::logic_error("Determinant must be non-zero to calculate inverse");
  }
  return CalcComplements().Transpose() * (1.0 / det);
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) const {
  S21Matrix temp{*this};
  temp.SumMatrix(other);
  return temp;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) const {
  S21Matrix temp{*this};
  temp.SubMatrix(other);
  return temp;
}

S21Matrix S21Matrix::operator*(double num) const {
  S21Matrix temp{*this};
  temp.MulNumber(num);
  return temp;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) const {
  S21Matrix temp{*this};
  temp.MulMatrix(other);
  return temp;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(double num) {
  MulNumber(num);
  return *this;
}

bool S21Matrix::operator==(const S21Matrix &other) const {
  return EqMatrix(other);
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this != &other) {
    if (matrix_) {
      for (int i = 0; i < rows_; i++) {
        delete[] matrix_[i];
      }
      delete[] matrix_;
    }
  }
  rows_ = other.rows_;
  cols_ = other.cols_;

  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
  return *this;
}

S21Matrix &S21Matrix::operator=(S21Matrix &&other) {
  if (this != &other) {
    if (matrix_) {
      for (int i = 0; i < rows_; i++) {
        delete[] matrix_[i];
      }
      delete[] matrix_;
    }
    matrix_ = other.matrix_;
    rows_ = other.rows_;
    cols_ = other.cols_;

    other.matrix_ = nullptr;
    other.rows_ = 0;
    other.cols_ = 0;
  }
  return *this;
}

double &S21Matrix::operator()(int i, int j) {
  if (i >= rows_ || j >= cols_ || i < 0 || j < 0) {
    throw std::out_of_range("Incorrect input for (), index is out of range.");
  }
  return matrix_[i][j];
}

double S21Matrix::operator()(int i, int j) const {
  if (i >= rows_ || j >= cols_ || i < 0 || j < 0) {
    throw std::out_of_range("Incorrect input for (), index is out of range.");
  }
  return matrix_[i][j];
}

void S21Matrix::print_matrix() {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
    }
    putchar('\n');
  }
  putchar('\n');
}

void S21Matrix::filling_matrix(int matrix_size, ...) {
  va_list arr;
  va_start(arr, matrix_size);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      double number = va_arg(arr, double);
      matrix_[i][j] = number;
    }
  }
  va_end(arr);
}

void S21Matrix::SwapRows(int row1, int row2) {
  for (int j = 0; j < cols_; j++) {
    std::swap(matrix_[row1][j], matrix_[row2][j]);
  }
}

S21Matrix S21Matrix::GetMinor(const S21Matrix &matrix, int row, int col) const {
  S21Matrix minor(matrix.rows_ - 1, matrix.cols_ - 1);
  for (int i = 0, mi = 0; i < matrix.rows_; i++) {
    if (i == row) continue;
    for (int j = 0, mj = 0; j < matrix.cols_; j++) {
      if (j == col) continue;
      minor(mi, mj) = matrix(i, j);
      mj++;
    }
    mi++;
  }
  return minor;
}

void S21Matrix::resize(int rows, int cols) {
  double **temp = new double *[rows];
  for (int i = 0; i < rows; i++) {
    temp[i] = new double[cols]{0};
  }

  for (int i = 0; i < std::min(rows, rows_); i++) {
    for (int j = 0; j < std::min(cols, cols_); j++) {
      temp[i][j] = matrix_[i][j];
    }
  }

  if (matrix_) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
  }
  matrix_ = nullptr;

  rows_ = rows;
  cols_ = cols;

  matrix_ = temp;
}
