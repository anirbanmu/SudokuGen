CXX := clang++
CXXFLAGS := -O2 -Wall -Werror -std=c++14

# Link
sudoku_gen: *.o
    $(CXX) $(CXXFLAGS) $(inputs) -o $(output)

main: main.cpp
    $(CXX) $(CXXFLAGS) -c $(input) -o $(output)

sudoku_gen.o: sudoku_gen.cpp
    $(CXX) $(CXXFLAGS) -c $(input) -o $(output)