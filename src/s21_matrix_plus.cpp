#include "s21_matrix_plus.h"
#include <iostream>


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
    std::cout << "delete " << matrix_[i] << std::endl;   
  }
  delete[] matrix_;
  std::cout << "delete " << matrix_ << std::endl;   

}    

S21Matrix::S21Matrix(const S21Matrix &other) {
  std::cout << "calling the copy constructor: " << this << std::endl; 

}

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

void S21Matrix::filling_matrix() {
    double count{};
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) { 
        matrix_[i][j] = count;
        count += 2;
      }
    }
  }

void S21Matrix::SumMatrix(const S21Matrix& other) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      this->matrix_[i][j] =+ other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      this->matrix_[i][j] =+ other.matrix_[i][j];
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
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = 0;
      for (int k = 0; k < cols_; k++) {
        matrix_[i][j] += matrix_[i][k] * matrix_[k][j];
      }
    }
  }
}

// S21Matrix::S21Matrix operator + (const S21Matrix& other) {
//   S21Matrix temp;
//   for (int i = 0; i < rows_; i++) {
//     for (int j = 0; j < cols_; j++) {
//       this->matrix_[i][j] =+ other.matrix_[i][j];
//     }
//   }
//     return temp;
// }

void S21Matrix::print_matrix () {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      std::cout << matrix_[i][j] << ' ';
    }
    putchar('\n');
  }
}


void temp (S21Matrix X) {
  std::cout << "Calling temp \n"  << std::endl;
}
 
int main(void) {
  S21Matrix A(3, 3);
  A.filling_matrix();
  temp(A);
  return 0;
}
