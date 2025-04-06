CC = g++
CFFLAGS = -Wall -Wextra -std=c++17
GTEST_GLAG = -lgtest -lgtest_main -pthread  

############################################
SRC = s21_matrix_oop.cpp
TEST_SRC = unit_tests.cpp
############################################
SRC_OBJ = s21_matrix_oop.o
TEST_SRC_OBJ = unit_tests.o


start: 
	$(CC) $(CFFLAGS) $(SRC) -o $(SRC_OBJ)
	./$(SRC_OBJ)

test:
	$(CC) -std=c++17 $(TEST_SRC) $(SRC) -o $(TEST_SRC_OBJ) $(GTEST_GLAG)
	./$(TEST_SRC_OBJ)

clean:
	rm -rf *.o

re: clean start
	