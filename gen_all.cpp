#include <iostream>
#include "sudoku_gen.h"

using namespace std;

int main(int, char**)
{
    SudokuGenerator(9, [](const SudokuGrid& g)
                            {
                                g.print();
                                cout << endl;
                            }).generate_all_sudoku();
    return 0;
}