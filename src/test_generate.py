import random
import sys
import numpy as np

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

# Функция для вычисления определителя матрицы
def calculate_determinant(values, rows, cols):
    if rows != cols:
        return None  # Определитель только для квадратных матриц
    matrix = np.array(values).reshape(rows, cols)
    return np.linalg.det(matrix)

# Функция для вычисления матрицы алгебраических дополнений
def calculate_complements(values, rows, cols):
    if rows != cols:
        return None  # Алгебраические дополнения только для квадратных матриц
    matrix = np.array(values).reshape(rows, cols)
    # Вычисляем матрицу алгебраических дополнений
    cofactor_matrix = np.zeros((rows, cols))
    for i in range(rows):
        for j in range(cols):
            # Создаем минор (матрица без i-й строки и j-го столбца)
            minor = np.delete(np.delete(matrix, i, axis=0), j, axis=1)
            # Вычисляем определитель минора
            minor_det = np.linalg.det(minor)
            # Алгебраическое дополнение = (-1)^(i+j) * det(minor)
            cofactor_matrix[i][j] = ((-1) ** (i + j)) * minor_det
    return cofactor_matrix.flatten().tolist()

# Функция для вычисления обратной матрицы
def calculate_inverse(values, rows, cols):
    if rows != cols:
        return None  # Обратная матрица только для квадратных матриц
    matrix = np.array(values).reshape(rows, cols)
    try:
        inverse_matrix = np.linalg.inv(matrix)
        return inverse_matrix.flatten().tolist()
    except np.linalg.LinAlgError:
        return None  # Матрица вырожденная (определитель = 0)

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
    
    {EXPECT} (1, A.EqMatrix(expected));
}}
"""

# Генерация тестов
with open("tests/S21MatrixTest_sum.cpp", "w") as f:
    f.write('#include "unit_tests.h"')

    for i in range(200):  # Генерируем 200 тестов
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
            expected_values=', '.join(map(str, expected_values)),
            EXPECT = "EXPECT_EQ"
        ))
        

with open("tests/S21MatrixTest_sub.cpp", "w") as f:
    f.write('#include "unit_tests.h"')

    for i in range(200):  # Генерируем 200 тестов
        rows = random.randint(1, 30)
        cols = random.randint(1, 30)
        # Генерация случайных значений для матриц
        values1 = [random.uniform(-1000000000.0, 1000000000.0) for _ in range(rows * cols)]
        values2 = [random.uniform(-1000000000.0, 1000000000.0) for _ in range(rows * cols)]
        
        # Складываем матрицы
        expected_values = sub_matrices(values1, values2, rows, cols)

        # Заполнение шаблона
        f.write(test_template.format(
            suite = "S21MatrixTest_sub",
            test_num=i, 
            rows=rows, 
            cols=cols,
            count_val = count_val,
            values1=', '.join(map(str, values1)),
            values2=', '.join(map(str, values2)),
            matrices_func = "SubMatrix",
            variable = "B",
            expected_values=', '.join(map(str, expected_values)),
            EXPECT = "EXPECT_EQ"

        ))


with open("tests/S21MatrixTest_MulNumber.cpp", "w") as f:
    f.write('#include "unit_tests.h"')

    for i in range(200):  # Генерируем 200 тестов
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
            expected_values=', '.join(map(str, expected_values)),
            EXPECT = "EXPECT_EQ"
        ))
  
test_template_for_Eq = """

TEST({suite}, {matrices_func}_{test_num}) {{
    S21Matrix A({rows}, {cols});
    S21Matrix B({rows}, {cols});
    
    A.filling_matrix({count_val}, {values1});
    B.filling_matrix({count_val}, {values2});
    
    EXPECT_FALSE (A == B);
}}
"""

with open("tests/S21MatrixTest_EqMatrix.cpp", "w") as f:
    f.write('#include "unit_tests.h"')

    for i in range(200):  # Генерируем 200 тестов
        rows = random.randint(1, 30)
        cols = random.randint(1, 30)
        # Генерация случайных значений для матриц
        values1 = [random.uniform(-1000000.0, 1000000.0) for _ in range(rows * cols)]
        values2 = [random.uniform(-1000000.0, 1000000.0) for _ in range(rows * cols)]
        number = random.uniform(-1000, 1000)
        
        # Заполнение шаблона
        f.write(test_template_for_Eq.format(
            suite = "S21MatrixTest_EqMatrix",
            matrices_func = "EqMatrix",
            test_num=i, 
            rows=rows,
            cols=cols,
            count_val = rows * cols,
            values1=', '.join(map(str, values1)),
            values2=', '.join(map(str, values2)),
            expected_values=', '.join(map(str, expected_values)),
        ))



test_template_for_operator_overload = """

TEST({suite}, {matrices_func}_{test_num}) {{
    S21Matrix A({rows}, {cols});
    S21Matrix B({rows}, {cols});
    S21Matrix C({rows}, {cols});

    A.filling_matrix({count_val}, {values1});
    B.filling_matrix({count_val}, {values2});

    A({rows_ind}, {cols_ind}) = B(0, 0);

 

    C = A + B;
    C = C - A;
    C = C * 1.2;
    C += B;
    C -= A;
    C *= 0.5;
    A = B;

    const S21Matrix D = A;
    double ct = D({rows_ind}, {cols_ind});
    
    S21Matrix expected({rows}, {cols});
    expected.filling_matrix({count_val}, {expected_values});

    double operator_brackets = C({rows_ind}, {cols_ind});

    EXPECT_TRUE (expected == C);
    EXPECT_EQ ({indexC}, operator_brackets);
    EXPECT_EQ (true, A == B);
    EXPECT_EQ (ct, D({rows_ind}, {cols_ind}));
}}
"""

with open("tests/S21MatrixTest_operator_overload.cpp", "w") as f:
    f.write('#include "unit_tests.h"')

    for i in range(1000):  # Генерируем 200 тестов
        rows = random.randint(1, 30)
        cols = random.randint(1, 30)
        
        # Генерация случайных значений для матриц
        values1 = [random.uniform(-100000.0, 100000.0) for _ in range(rows * cols)]
        values2 = [random.uniform(-100000.0, 100000.0) for _ in range(rows * cols)]
        
        # Преобразуем в двумерные матрицы
        A = np.array(values1).reshape(rows, cols)
        B = np.array(values2).reshape(rows, cols)
        
        rows_ind = random.randint(0, rows - 1)
        cols_ind = random.randint(0, cols - 1)
        A[rows_ind][cols_ind] = B[0][0]

        # Операции с матрицами
        C = A + B
        C = C - A
        C = C * 1.2
        C += B
        C -= A
        C *= 0.5
        
        


        def format_values(values):
          return ', '.join([str(x).replace(' -', '-') for x in values])

        # Заполнение шаблона
        f.write(test_template_for_operator_overload.format(
            suite = "S21MatrixTest_Operator_Overload",
            matrices_func = "Operator_Overload",
            test_num=i, 
            rows=rows,
            cols=cols,
            count_val = rows * cols,
            values1=', '.join(map(str, values1)),
            values2=', '.join(map(str, values2)),
            expected_values=format_values(C.flatten()),

            indexC = C[rows_ind][cols_ind], 
            rows_ind = rows_ind,
            cols_ind = cols_ind,

            
        ))

# Шаблон для тестов Determinant
test_template_for_determinant = """

TEST({suite}, {matrices_func}_{test_num}) {{
    S21Matrix A({rows}, {cols});
    
    A.filling_matrix({count_val}, {values1});
    
    double result = A.Determinant();
    
    EXPECT_NEAR({expected_det}, result, 1e-6);
}}
"""

# Генерация тестов для Determinant
with open("tests/S21MatrixTest_Determinant.cpp", "w") as f:
    f.write('#include "unit_tests.h"')

    for i in range(200):  # Генерируем 200 тестов
        # Для определителя нужны только квадратные матрицы
        size = random.randint(1, 5)  # Размеры от 1x1 до 5x5
        rows = cols = size
        count_val = rows * cols
        
        # Генерация случайных значений для матрицы
        values1 = [random.uniform(-10.0, 10.0) for _ in range(count_val)]
        
        # Вычисляем ожидаемый определитель
        expected_det = calculate_determinant(values1, rows, cols)
        
        # Заполнение шаблона
        f.write(test_template_for_determinant.format(
            suite="S21MatrixTest_Determinant",
            matrices_func="Determinant",
            test_num=i,
            rows=rows,
            cols=cols,
            count_val=count_val,
            values1=', '.join(map(str, values1)),
            expected_det=expected_det
        ))

# Шаблон для тестов CalcComplements
test_template_for_complements = """

TEST({suite}, {matrices_func}_{test_num}) {{
    S21Matrix A({rows}, {cols});
    
    A.filling_matrix({count_val}, {values1});
    
    S21Matrix result = A.CalcComplements();
    
    // Ожидаемый результат
    S21Matrix expected({rows}, {cols});
    expected.filling_matrix({count_val}, {expected_values});
    
    EXPECT_TRUE(result.EqMatrix(expected));
}}
"""

# Генерация тестов для CalcComplements
with open("tests/S21MatrixTest_CalcComplements.cpp", "w") as f:
    f.write('#include "unit_tests.h"')

    for i in range(200):  # Генерируем 200 тестов
        # Для алгебраических дополнений нужны только квадратные матрицы
        size = random.randint(2, 4)  # Размеры от 2x2 до 4x4 (для 1x1 не очень интересно)
        rows = cols = size
        count_val = rows * cols
        
        # Генерация случайных значений для матрицы
        values1 = [random.uniform(-5.0, 5.0) for _ in range(count_val)]
        
        # Вычисляем ожидаемые алгебраические дополнения
        expected_complements = calculate_complements(values1, rows, cols)
        
        # Заполнение шаблона
        f.write(test_template_for_complements.format(
            suite="S21MatrixTest_CalcComplements",
            matrices_func="CalcComplements",
            test_num=i,
            rows=rows,
            cols=cols,
            count_val=count_val,
            values1=', '.join(map(str, values1)),
            expected_values=', '.join(map(str, expected_complements))
        ))

# Шаблон для тестов InverseMatrix
test_template_for_inverse = """

TEST({suite}, {matrices_func}_{test_num}) {{
    S21Matrix A({rows}, {cols});
    
    A.filling_matrix({count_val}, {values1});
    
    S21Matrix result = A.InverseMatrix();
    
    // Ожидаемый результат
    S21Matrix expected({rows}, {cols});
    expected.filling_matrix({count_val}, {expected_values});
    
    EXPECT_TRUE(result.EqMatrix(expected));
}}
"""

# Генерация тестов для InverseMatrix
with open("tests/S21MatrixTest_InverseMatrix.cpp", "w") as f:
    f.write('#include "unit_tests.h"')

    for i in range(200):  # Генерируем 200 тестов
        # Для обратной матрицы нужны только квадратные матрицы
        size = random.randint(2, 4)  # Размеры от 2x2 до 4x4
        rows = cols = size
        count_val = rows * cols
        
        # Генерируем матрицу с ненулевым определителем
        while True:
            values1 = [random.uniform(-3.0, 3.0) for _ in range(count_val)]
            det = calculate_determinant(values1, rows, cols)
            if abs(det) > 0.1:  # Убеждаемся, что определитель не слишком близок к нулю
                break
        
        # Вычисляем ожидаемую обратную матрицу
        expected_inverse = calculate_inverse(values1, rows, cols)
        
        # Заполнение шаблона
        f.write(test_template_for_inverse.format(
            suite="S21MatrixTest_InverseMatrix",
            matrices_func="InverseMatrix",
            test_num=i,
            rows=rows,
            cols=cols,
            count_val=count_val,
            values1=', '.join(map(str, values1)),
            expected_values=', '.join(map(str, expected_inverse))
        ))


