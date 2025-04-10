CC = g++
CFFLAGS = -Wall -Wextra -std=c++17
GTEST_FLAGS = -lgtest -pthread -lgtest_main
############################################
SRC = s21_matrix_oop.cpp
TEST_SRC = unit_tests.cpp
############################################
SRC_OBJ = s21_matrix_oop.o
TEST_SRC_OBJ = unit_tests.o
###########################################
COV_DIR = coverage_report


GREEN   =   \033[0;32m
RED		=   \033[0;31m
RESET	=   \033[0m

all: s21_matrix_oop.a 

s21_matrix_oop.a: $(SRC_OBJ)
	@printf "$(GREEN)--->THE LIBRARU HAS BEEN CREATED$(RESET)\n"
	@ar rc s21_matrix.a s21_matrix_oop.o
	@ranlib s21_matrix.a

%.o: %.cpp
	@$(CC) $(CFLAGS) -c $< -o $@

gcov_report:
	@mkdir -p $(COV_DIR)
	@printf '$(GREEN)---> THE "$(COV_DIR)" FOLDER WAS BEEN CREATED $(RESET)\n'
	@printf "$(GREEN)---> RUNNING TESTS $(RESET)\n"
	@$(CC) -O0 -g --coverage $(TEST_SRC) $(SRC) -o $(TEST_SRC_OBJ) $(GTEST_FLAGS)
	@./$(TEST_SRC_OBJ)

	@lcov --capture --directory . --output-file $(COV_DIR)/coverage.info --ignore-errors mismatch >/dev/null 2>&1
	@lcov --extract $(COV_DIR)/coverage.info "$(abspath $(SRC))" --output-file $(COV_DIR)/filtered.info >/dev/null 2>&1
	
	@# Генерация отчёта только для нужного файла
	@genhtml $(COV_DIR)/filtered.info --output-directory $(COV_DIR) --title "Coverage for s21_matrix_oop.cpp" >/dev/null 2>&1
	
	@printf "$(GREEN)---> COVERAGE REPORT GENERATED \n$(RESET)"
	@printf "$(GREEN)---> OPEN REPORT \n$(RESET)"

	@xdg-open $(COV_DIR)/index.html 2>/dev/null || true

%.o: %.cpp
	@$(CC) $(CFLAGS) -c $< -o $@

test:
	@printf "$(GREEN)---> RUNNING TESTS $(RESET)\n"
	@$(CC) $(TEST_SRC) $(SRC) -o $(TEST_SRC_OBJ) $(GTEST_FLAGS)
	@./$(TEST_SRC_OBJ)
	

clang-format:
	@printf "$(GREEN)--->MAKE CLANG $(RESET)\n"
	@clang-format -i *.cpp *.h

clean:
	@rm -rf *.o $(COV_DIR) *.gcda *.gcno s21_matrix.a 
	@printf "$(GREEN)--->CLEARING ALL FILES $(RESET)\n"
	clear

re: clean start 
	