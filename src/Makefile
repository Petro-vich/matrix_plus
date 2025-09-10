CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++17
GTEST_FLAGS = -lgtest -pthread
############################################
SRC = s21_matrix_oop.cpp
SRC_OBJ = s21_matrix_oop.o
############################################
TEST_SRC = $(wildcard tests/*.cpp)
TEST_SRC_OBJ = $(wildcard tests/*.o)
###########################################
COV_DIR = coverage_report
###########################################
TARGET = s21_matrix_oop.a
##########################################
CLEAN_LIST = *.gcda *gcno gcov_report *.o


GREEN   =   \033[0;32m
RED		=   \033[0;31m
RESET	=   \033[0m

all: $(TARGET)

$(TARGET): $(SRC_OBJ)
	@printf "$(GREEN)--->THE LIBRARU HAS BEEN CREATED$(RESET)\n"
	@ar rc $(TARGET) s21_matrix_oop.o
	@ranlib $(TARGET)
	
	@rm -rf $(CLEAN_LIST)

%.o: %.cpp
	@$(CC) $(CFLAGS) -c $< -o $@

gcov_report:
	@mkdir -p $(COV_DIR)
	@printf '$(GREEN)---> THE "$(COV_DIR)" FOLDER WAS BEEN CREATED $(RESET)\n'
	@printf "$(GREEN)---> RUNNING TESTS $(RESET)\n"
	@$(CC) $(CFLAGS) --coverage $(TEST_SRC) $(SRC) -o $@ $(GTEST_FLAGS)
	@./$@

	@# Сбор данныхThe.
	@lcov --capture --directory . --output-file $(COV_DIR)/coverage.info \
		--ignore-errors mismatch,inconsistent >$(COV_DIR)/lcov.log 2>&1
	
	@# Фильтрация только нужного файла
	@lcov --extract $(COV_DIR)/coverage.info "$(abspath $(SRC))" \
		--output-file $(COV_DIR)/filtered.info >>$(COV_DIR)/lcov.log 2>&1
	
	@# Генерация отчёта
	@genhtml $(COV_DIR)/filtered.info --output-directory $(COV_DIR) \
		--title "Coverage for s21_matrix_oop.cpp" >>$(COV_DIR)/lcov.log 2>&1
	
	@printf "$(GREEN)---> COVERAGE REPORT GENERATED $(RESET)\n"
	@xdg-open $(COV_DIR)/index.html 2>/dev/null || true
	
	@rm -rf $(CLEAN_LIST)

%.o: %.cpp
	@$(CC) $(CFLAGS) -c $< -o $@

test:
	@printf "$(GREEN)---> RUNNING TESTS $(RESET)\n"
	$(CC) $(CFLAGS) $(TEST_SRC) $(SRC) -o tests/$@ $(GTEST_FLAGS)
	./tests/$@

valgrind:
	@printf "$(GREEN)---> RUNNING TESTS WITH VALGRIND $(RESET)\n"
	@$(CC) $(CFLAGS) $(TEST_SRC) $(SRC) -o tests/test_valgrind $(GTEST_FLAGS)
	@valgrind --tool=memcheck --leak-check=yes --log-file=valgrind_report.txt ./tests/test_valgrind
	@printf "$(GREEN)---> VALGRIND REPORT GENERATED: valgrind_report.txt $(RESET)\n"
	@printf "$(GREEN)---> Checking for memory leaks... $(RESET)\n"
	@if grep -q "ERROR SUMMARY: 0" valgrind_report.txt; then \
		printf "$(GREEN)---> NO MEMORY LEAKS DETECTED! $(RESET)\n"; \
	else \
		printf "$(RED)---> MEMORY LEAKS DETECTED! Check valgrind_report.txt $(RESET)\n"; \
	fi
	@rm -f tests/test_valgrind

leak_check:
	@printf "$(GREEN)---> RUNNING TESTS WITH ADDRESS SANITIZER $(RESET)\n"
	@$(CC) $(CFLAGS) -fsanitize=address -fsanitize=leak -g $(TEST_SRC) $(SRC) -o tests/test_leak $(GTEST_FLAGS)
	@ASAN_OPTIONS=detect_leaks=1:abort_on_error=1:check_initialization_order=1:strict_init_order=1 ./tests/test_leak
	@printf "$(GREEN)---> LEAK CHECK COMPLETED $(RESET)\n"
	@rm -f tests/test_leak

clang-format:
	@printf "$(GREEN)--->MAKE CLANG $(RESET)\n"
	@clang-format -i *.cpp *.h

clean:
	rm -rf  $(CLEAN_LIST) coverage_report tests/test $(TARGET) $(TARGET) valgrind_report.txt
	clear
	@printf "$(GREEN)--->CLEARING ALL FILES $(RESET)\n"

re: clean start 
	