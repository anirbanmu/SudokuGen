CXX := clang++-3.8
CXXFLAGS := -O2 -Wall -Werror -std=c++14

# Link
sudoku_gen_random: random.o sudoku_gen.o sudoku_gen_all
    $(CXX) $(CXXFLAGS) random.o sudoku_gen.o -o $(output)

sudoku_gen_all: all.o sudoku_gen.o
    $(CXX) $(CXXFLAGS) $(inputs) -o $(output)

random.o: gen_random.cpp
    $(CXX) $(CXXFLAGS) -c $(input) -o $(output)

all.o: gen_all.cpp
    $(CXX) $(CXXFLAGS) -c $(input) -o $(output)

sudoku_gen.o: sudoku_gen.cpp
    $(CXX) $(CXXFLAGS) -c $(input) -o $(output)