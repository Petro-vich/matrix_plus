CC = g++
CFFLAGS = -Wall -Wextra -std=c++17
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
	@$(CC) --coverage $(TEST_SRC) $(SRC) -o $@ $(GTEST_FLAGS)
	@./$@

	@# Сбор данных с игнорированием ошибок
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
	$(CC) $(TEST_SRC) $(SRC) -o tests/$@ $(GTEST_FLAGS)
	./tests/$@
	

clang-format:
	@printf "$(GREEN)--->MAKE CLANG $(RESET)\n"
	@clang-format -i *.cpp *.h

clean:
	rm -rf  $(CLEAN_LIST) coverage_report tests/test $(TARGET) $(TARGET) s21_matrix_oop
	clear
	@printf "$(GREEN)--->CLEARING ALL FILES $(RESET)\n"

re: clean start 
	