#include "sudoku_gen.h"

int main(int, char**)
{
    generate_random_sudoku(9, [](const SudokuGrid& g){ g.print(); });
    return 0;
}