#include <iostream>
#include "sudoku_gen.h"

using namespace std;

int main(int, char**)
{
    generate_all_sudoku(9, [](const SudokuGrid& g)
                            {
                                g.print();
                                cout << endl;
                            });
    return 0;
}