import random
import sys
import numpy

# Функция для сложения двух матриц
def add_matrices(values1, values2, rows, cols):
    result = []
    for i in range(rows * cols):
        result.append(values1[i] + values2[i])
    return result

def sub_matrices(values1, values2, rows, cols):
    result = []
    for i in range(rows * cols):
        result.append(values1[i] - values2[i])
    return result

def mul_matrices(values1, rows, cols, number):
  result = []
  for i in range(rows * cols):
      result.append(values1[i] * number)
  return result

# Шаблон для теста
test_template = """

TEST({suite}, {matrices_func}_{test_num}) {{
    S21Matrix A({rows}, {cols});
    S21Matrix B({rows}, {cols});
    
    A.filling_matrix({count_val}, {values1});
    B.filling_matrix({count_val}, {values2});
    
    A.{matrices_func}({variable});

    // Ожидаемый результат
    S21Matrix expected({rows}, {cols});
    expected.filling_matrix({count_val}, {expected_values});
    
    EXPECT_EQ (1, A.EqMatrix(expected));
}}
"""

# Генерация тестов
with open("unit_tests.cpp", "w") as f:
    f.write("#include <gtest/gtest.h>\n")
    f.write('#include "s21_matrix_oop.h"')

    for i in range(100):  # Генерируем 10 тестов
        rows = random.randint(1, 10)
        cols = random.randint(1, 10)
        count_val = rows * cols
        # Генерация случайных значений для матриц
        values1 = [random.uniform(-1000000000.0, 1000000000.0) for _ in range(count_val)]
        values2 = [random.uniform(-1000000000.0, 1000000000.0) for _ in range(count_val)]
        
        # Складываем матрицы
        expected_values = add_matrices(values1, values2, rows, cols)
        # Заполнение шаблона
        f.write(test_template.format(
            suite = "S21MatrixTest_sum",
            test_num=i,
            rows=rows, 
            cols=cols, 
            count_val = count_val,
            values1=', '.join(map(str, values1)),
            values2=', '.join(map(str, values2)),
            matrices_func = "SumMatrix",
            variable = "B",
            expected_values=', '.join(map(str, expected_values))
        ))
        

with open("unit_tests.cpp", "a") as f:

    for i in range(100):  # Генерируем 10 тестов
        rows = random.randint(1, 30)
        cols = random.randint(1, 30)
        # Генерация случайных значений для матриц
        values1 = [random.uniform(-1000000000.0, 1000000000.0) for _ in range(rows * cols)]
        values2 = [random.uniform(-1000000000.0, 1000000000.0) for _ in range(rows * cols)]
        
        # Складываем матрицы
        expected_values = sub_matrices(values1, values2, rows, cols)

        # Заполнение шаблона
        f.write(test_template.format(
            suite = "S21MatrixTest_sum",
            test_num=i, 
            rows=rows, 
            cols=cols,
            count_val = count_val,
            values1=', '.join(map(str, values1)),
            values2=', '.join(map(str, values2)),
            matrices_func = "SubMatrix",
            variable = "B",
            expected_values=', '.join(map(str, expected_values))
        ))
  




with open("unit_tests.cpp", "a") as f:

    for i in range(100):  # Генерируем 10 тестов
        rows = random.randint(1, 30)
        cols = random.randint(1, 30)
        # Генерация случайных значений для матриц
        values1 = [random.uniform(-1000000.0, 1000000.0) for _ in range(rows * cols)]
        values2 = [random.uniform(-1000000.0, 1000000.0) for _ in range(rows * cols)]
        number = random.uniform(-1000, 1000)
        # Складываем матрицы
        expected_values = mul_matrices(values1, rows, cols, number)

        # Заполнение шаблона
        f.write(test_template.format(
            suite = "S21MatrixTest_MulNumber",
            test_num=i, 
            rows=rows, 
            cols=cols,
            count_val = count_val,
            values1=', '.join(map(str, values1)),
            values2=', '.join(map(str, values2)),
            matrices_func = "MulNumber",
            variable = number,
            expected_values=', '.join(map(str, expected_values))
        ))
  
  

