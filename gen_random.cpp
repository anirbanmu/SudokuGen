#include "sudoku_gen.h"

int main(int, char**)
{
    SudokuGenerator(9, [](const SudokuGrid& g){ g.print(); }).generate_random_sudoku();
    return 0;
}