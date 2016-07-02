#include "sudoku_gen.h"

int main(int, char**)
{
    generate_random_sudoku(9).print();
    return 0;
}