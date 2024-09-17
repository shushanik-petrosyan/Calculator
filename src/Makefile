.PHONY: all calc
SHELL = /bin/sh
FLAGS=-std=c11 -Wextra -Wall -Werror
C_SOURCES=$(wildcard s21_*.c)

LCHECK=-lcheck -lm
OUTNAME = calculate.app
TARGET = Calculator_v1.0.app
RUN = open ../build/$(TARGET)

ifeq ($(shell uname -s),Linux)
        LCHECK= -lsubunit -lcheck -lm
		OUTNAME = calculate
		TARGET = Calculator_v1.0
		RUN = ./../build/$(TARGET)
endif

GCOV=-fprofile-arcs -ftest-coverage

CC=gcc
TEST_FLAGS=-lm
S21_CALC_C=s21_*.c
S21_CALC_H=s21_*.h
S21_CALC_O=s21_*.o
TESTS=test
OS := $(shell uname -s)
OS_TITLE=:=$(shell cat /etc/os-release)

ifeq ($(OS),Darwin)
    LCHECK := -lcheck
	OUTNAME := front.app/Contents/MacOS/front 
endif
ifeq ($(findstring Ubuntu, $(OS_TITLE)), Ubuntu)
    LCHECK=-lcheck -lsubunit -lm
else ifeq ($(findstring Manjaro, $(OS_TITLE)), Manjaro)
	LCHECK=-lcheck -lm
endif

all: install run

sudo:
	sudo apt-get update
	sudo apt-get install g++
	sudo apt install doxygen
	sudo apt install -y qtcreator qtbase5-dev qt5-qmake cmake
	sudo apt install clang

run: 
	$(RUN)

open: install
	$(RUN)

install:       
	echo "Installation of $(TARGET):"
	mkdir -p ../build
	cd $(OUTNAME)/ && qmake && make && make clean && rm -rf Makefile && mv $(OUTNAME) ../../build/$(TARGET)
	echo "Installation completed! You can find app in the ../build/ folder!"

uninstall:
	rm -rf ../build
	echo "Uninstall completed!"
	
dist: install
	mkdir -p ../dist
	cp -R ../build/$(TARGET) ../dist
	cp -R . ../dist/src
	cd ../dist && tar cvzf $(TARGET).tgz *
	cd ../dist && rm -rf $(TARGET)
	rm -rf ../dist/src
	echo "Archive creation completed successfully!"	
	echo "You can find int in the ../dist/ folder"	

dvi: clean
	@doxygen Doxyfile
	open doxygen/html/index.html
	
s21_covered:
	$(CC) s21_*.c -c $(FLAGS) --coverage
	ar rc s21_calc.a s21_*.o
	ranlib s21_calc.a

test: clean s21_covered
	$(CC) $(TESTS).c -c $(FLAGS) --coverage
	$(CC) -o $(TESTS) $(TESTS)*.o s21_calc.a $(LCHECK) --coverage $(FLAGS) $(TEST_FLAGS)
	./$(TESTS)

gcov_report: test
	lcov -t "s21_smartcalc" -o s21_smartcalc.info -c -d .
	genhtml -o report s21_smartcalc.info
	open report/index.html

clean:
	rm -rf ../build ../dist *.o *.info doxygen ../build/$(TARGET) *.a calculate/$(OUTNAME) calculate/*.o report a.out $(TESTS) lexeme_parser *.gcda *.gcno coverage.info coverage_html doxygen valgrind.out 

