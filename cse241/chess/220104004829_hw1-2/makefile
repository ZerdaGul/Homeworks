all: clean compile run

compile:main.cpp chess.cpp
	@echo "-------------------------------------------"
	@echo "Compiling..."
	@g++ -o test main.cpp chess.cpp -lm -std=c++11

run:
	@echo "-------------------------------------------"
	@echo "Running the tests...."
	@echo "======================================================================="
	@./test
	@echo "======================================================================="
	@echo "Completed tests...."

clean:
	@echo "-------------------------------------------"
	@echo "Cleaning..."
	@rm -f *.o
	@rm -f test
	@rm -f chess.txt
