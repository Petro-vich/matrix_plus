#include "s21_matrix_plus.h"
#include <iostream>


/*=======================================SET/GET==========================================*/
int S21Matrix::get_rows() {return this->rows_;}

int S21Matrix::get_col() {return this->cols_;}

void S21Matrix::set_rows(int rows) {this->rows_ = rows;}

void S21Matrix::set_cols(int cols) {this-> rows_ = cols;}
/*===================================Default constructor===================================*/

S21Matrix::S21Matrix() noexcept : rows_(0), cols_(0), matrix_(nullptr){
  std::cout << "calling construction " << this << "\n";
}
  
S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  std::cout << "calling construction " << this << "\n";  
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
  }
} 

S21Matrix::~S21Matrix() {
  std::cout << "Calling dectructinon" << this << '\n';

  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
    //std::cout << "delete " << matrix_[i] << std::endl;   
  }
  delete[] matrix_;
  //std::cout << "delete " << matrix_ << std::endl;   

}    

S21Matrix::S21Matrix(const S21Matrix &other) : 
  rows_(other.rows_), cols_(other.cols_) {
  std::cout << "calling the copy constructor: " << this << std::endl; 
  
  matrix_ = new double *[rows_];

  for ( int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
     for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

/*===================================Operations on matrices================================*/
bool S21Matrix::EqMatrix(const S21Matrix& other) {
  bool status;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j <cols_; j++) {
      if (this->matrix_[i][j] != other.matrix_[i][j]) {
        status = 0;
        break;
      }else{
        status = 1;
      }
    }
  }
  return status;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      this->matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      this->matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      this->matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  S21Matrix temp(this->rows_, other.cols_);
  for (int i = 0; i < temp.rows_; ++i) {
    for (int j = 0; j < temp.cols_; ++j) {
      temp.matrix_[i][j] = 0;  // Обнуляем перед суммированием
      for (int k = 0; k < this->cols_; ++k) {
        temp.matrix_[i][j] += this->matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }

  *this = std::move(temp);
}

S21Matrix S21Matrix::Transpose() {
  
  S21Matrix temp(this->cols_, this->rows_);

  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
        temp.matrix_[j][i] = this->matrix_[i][j];
    }
}
return temp; 
}

double S21Matrix::Determinant() {

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

        // Меняем строки местами, если нужно
        if (pivot_row != i) {
            temp.SwapRows(i, pivot_row);
            det *= -1;  // Меняем знак детерминанта
        }

        // Приводим к верхнетреугольному виду
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

S21Matrix S21Matrix::CalcComplements() {
    if (rows_ != cols_) {
        throw std::invalid_argument("Matrix must be square");
    }

    S21Matrix result(rows_, cols_);  // Создаём новую матрицу дополнений

    if (rows_ == 1) {
        result(0, 0) = 1;  // Для матрицы 1x1 алгебраическое дополнение = 1
        return result;
    }

    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            S21Matrix minor = GetMinor(*this, i, j);  // Получаем минор
            double det = minor.Determinant();         // Вычисляем определитель минора
            result(i, j) = det * ((i + j) % 2 == 0 ? 1 : -1);  // Умножаем на (-1)^(i+j)
        }
    }

    return result;
}

/*==================================Opeartor overload==========================================*/

S21Matrix S21Matrix::operator + (const S21Matrix &other) {
  S21Matrix temp{*this};  
  temp.SumMatrix(other);
    return temp;
}

S21Matrix S21Matrix::operator - (const S21Matrix &other) {
  S21Matrix temp{*this};
  temp.SubMatrix(other);
    return temp;
}

S21Matrix S21Matrix::operator * (double num) {
  S21Matrix temp{*this};
  temp.MulNumber(num);
    return temp;
}

S21Matrix S21Matrix::operator * (const S21Matrix& other) {
  S21Matrix temp{*this};
  temp.MulMatrix(other);
    return temp;
}

S21Matrix S21Matrix::operator += (const S21Matrix &other) {
  (*this).SumMatrix(other);
    return (*this);
}

S21Matrix S21Matrix::operator -= (const S21Matrix &other) {
  (*this).SubMatrix(other);
    return (*this);
}

S21Matrix S21Matrix::operator *= (const S21Matrix &other) {
  (*this).MulMatrix(other);
  return (*this);
}

S21Matrix S21Matrix::operator *= (double num) {
  (*this).MulNumber(num);
  return (*this);
}

bool S21Matrix::  operator == (const S21Matrix& other) {
  return  EqMatrix(other);
}

S21Matrix S21Matrix::operator = (const S21Matrix &other) {
  if (this != &other) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
  }
  rows_ = other.rows_;
  cols_ = other.cols_;

  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
      for (int j = 0; j < cols_; j++) {
        this->matrix_[i][j] = other.matrix_[i][j];
      }
  }
  return *this;
} 

double& S21Matrix:: operator () (int i, int j) {
  return this->matrix_[i][j];
}

double S21Matrix::operator()(int i, int j) const {
    return matrix_[i][j];
}

/*======================================Helpers================================================*/
void S21Matrix::print_matrix () {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      std::cout << matrix_[i][j] << ' ';
    }
    putchar('\n');
  }
}

void S21Matrix::filling_matrix() {
    double count{};
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) { 
        matrix_[i][j] = count;
        count += 2;
      }
    }
  }
 
void S21Matrix::SwapRows(int row1, int row2) {
    for (int j = 0; j < cols_; j++) {
        std::swap(matrix_[row1][j], matrix_[row2][j]);
    }
}
 
S21Matrix S21Matrix::GetMinor(const S21Matrix& matrix, int row, int col) {
    S21Matrix minor(matrix.rows_ - 1, matrix.cols_ - 1);
    for (int i = 0, mi = 0; i < matrix.rows_; i++) {
        if (i == row) continue;  // Пропускаем выбранную строку
        for (int j = 0, mj = 0; j < matrix.cols_; j++) {
            if (j == col) continue;  // Пропускаем выбранный столбец
            minor(mi, mj) = matrix(i, j);
            mj++;
        }
        mi++;
    }
    return minor;
}

 
int main(void) {
  S21Matrix A(3, 3);
  S21Matrix B(3, 3);  
  A.filling_matrix();
  B.filling_matrix();

  // S21Matrix C = A + B;
  // C.print_matrix();
  // S21Matrix D = A - C;
  // D.print_matrix();
  // S21Matrix F = A * 5.0;
  // F.print_matrix();
  // S21Matrix E = A * B;
  // E.print_matrix();

  // A += A;
  // A.print_matrix();
  // A -= B;
  // B.print_matrix();
  // A *= B;
  // A.print_matrix();
  // A *= 2;
  // A.print_matrix();

  // S21Matrix C = A.Transpose();
  // C.print_matrix();
  
  return 0;
}
