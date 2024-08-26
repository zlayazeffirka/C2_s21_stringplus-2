CC=gcc
FLAGS=-std=c11 -Wall -Werror -Wextra -std=c11 -g
GLFLAGS=--coverage
LIBNAME=s21_string.a
OS := $(shell uname)

TEST_DIR = tests/

rebuild: clean all

all: format s21_string.a 

test: s21_string.a
ifeq ($(OS), Linux)
	$(CC) $(FLAGS) $(TEST_DIR)*.c s21_string.a -lcheck -pthread -lrt -lm -lsubunit -o s21_test
else ifeq ($(OS), Darwin)
	$(CC) $(FLAGS) $(TEST_DIR)*.c -L. s21_string.a -o s21_test -lcheck
endif
	./s21_test

s21_string.a:
		$(CC) $(FLAGS) -c s21*.c 
		ar rcs $(LIBNAME) *.o
		ranlib $(LIBNAME) s21_string.a

gcov_report: clean s21_string.a test
ifeq ($(OS), Linux)
	gcc --coverage  $(TEST_DIR)*.c s21*.c -lcheck -pthread -lrt -lm -lsubunit -o s21_test
else ifeq ($(OS), Darwin)
	gcc --coverage  $(TEST_DIR)*.c s21*.c -o s21_test -lcheck
endif
	./s21_test
	lcov -t "s21_test" -o s21_test.info -c -d . && lcov --remove s21_test.info '/usr/local/lib/*' -o s21_test.info --ignore-errors unused
	genhtml -o report s21_test.info
	open ./report/index.html

valgrind: s21_string.a
ifeq ($(OS), Linux)
	$(CC) $(FLAGS) $(TEST_DIR)*.c s21_string.a -lcheck -pthread -lrt -lm -lsubunit -g -o s21_test
else ifeq ($(OS), Darwin)
	$(CC) $(FLAGS) $(TEST_DIR)*.c -L. s21_string.a -o s21_test -lcheck
endif
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./s21_test

clean:
	rm -rf *.o s21_string.a libs21_string.a $(TEST_DIR)s21_tests s21_test  *.gcda *.gcno report s21_test.info

format-check:
	@cp ../materials/linters/.clang-format ./
	@clang-format -n *.c *.h
	@clang-format -n $(TEST_DIR)*.c $(TEST_DIR)*.h 
	@rm .clang-format

format:
	@cp ../materials/linters/.clang-format ./
	@clang-format -i *.c *.h 
	@clang-format -i $(TEST_DIR)*.c $(TEST_DIR)*.h 
	@rm .clang-format

cpp:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h $(TEST_DIR)*.c $(TEST_DIR)*.h