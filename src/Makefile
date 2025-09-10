CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -lcheck -lm -lsubunit
GCOV_FLAG = --coverage

TARGET = s21_matrix.a

SRC = $(wildcard func/*.c)
AUX_SRC = $(wildcard aux_func/*.c)

OBJ_DIR = f_obj


SRC_OBJ = $(SRC:func/%.c=$(OBJ_DIR)/%.o)
AUX_SRC_OBJ = $(AUX_SRC:aux_func/%.c=$(OBJ_DIR)/%.o)


CLEAN_LIST = $(OBJ_DIR)/*.o s21_matrix.a coverage_report tests/test_matrix f_obj

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

all: $(TARGET)


s21_matrix.a: $(SRC_OBJ) $(AUX_SRC_OBJ)
	ar r s21_matrix.a $(SRC_OBJ) $(AUX_SRC_OBJ)


$(OBJ_DIR)/%.o: func/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: aux_func/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


test: s21_matrix.a
	$(CC) -o tests/test_matrix tests/test_matrix.c -L -l s21_matrix.a $(LDFLAGS)
	./tests/test_matrix

test_valgrind: s21_matrix.a
	$(CC) -o tests/test_matrix tests/test_matrix.c -L -l s21_matrix.a $(LDFLAGS)
	valgrind --tool=memcheck --leak-check=summary ./tests/test_matrix


gcov_report: 
	mkdir -p coverage_report
	mkdir -p coverage_report/gcda_gcno

	$(CC) -o tests/test_matrix  --coverage $(SRC) $(AUX_SRC) tests/test_matrix.c $(LDFLAGS)
	./tests/test_matrix
	lcov -t "Coverage Report" -c -d tests --output-file coverage_report/coverage.info
	genhtml coverage_report/coverage.info --output-directory coverage_report/
	xdg-open coverage_report/index.html
	mv tests/*.gcda tests/*gcno coverage_report/gcda_gcno
	
clang-format:
	clang-format -i *.c *.h aux_func/*.c test_matrix/*.c

clean:
	rm -rf $(CLEAN_LIST)


re: clean all
