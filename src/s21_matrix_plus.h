#ifndef S21_MATRIX_PLUS_H
#define S21_MATRIX_PLUS_H

#include <iostream>

class S21Matrix {
  private:
      
      int rows_, cols_;         
      double **matrix_;        \

  public:
  /*===================================Default constructor===================================*/
      S21Matrix() noexcept;
      S21Matrix(int rows, int cols);
      ~S21Matrix(); 
      S21Matrix(const S21Matrix &other);

  /*===================================Operations on matrices================================*/
      bool EqMatrix(const S21Matrix& other);
      void SumMatrix(const S21Matrix& other);
      void SubMatrix(const S21Matrix& other);
      void MulNumber(const double num);
      void MulMatrix(const S21Matrix& other);
/*==================================Opeartor overload==========================================*/
      S21Matrix operator + (const S21Matrix& other);
/*======================================Helpers================================================*/
     void filling_matrix();
     void print_matrix();
};


  
#endif