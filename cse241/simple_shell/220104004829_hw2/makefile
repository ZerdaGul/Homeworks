all: clean compile run

compile:main.cpp directory.cpp
	@g++ -o test main.cpp directory.cpp -std=c++11

run:
	@./test
clean:
	@rm -f *.o
	@rm -f test
