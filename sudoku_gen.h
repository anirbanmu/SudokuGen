#ifndef _SUDOKU_GEN_H_DECL_
#define _SUDOKU_GEN_H_DECL_

#include <vector>
#include <forward_list>

struct SudokuGrid
{
    SudokuGrid(unsigned dimension);

    unsigned& cell(unsigned row, unsigned column);
    std::forward_list<unsigned>& filter_row(unsigned row, std::forward_list<unsigned>& v);
    std::forward_list<unsigned>& filter_column(unsigned col, std::forward_list<unsigned>& v);
    std::forward_list<unsigned>& filter_subgrid(unsigned row, unsigned col, std::forward_list<unsigned>& v);
    std::vector<unsigned> cell_choices(unsigned row, unsigned column);
    void print();

    unsigned grid_dimension;
    unsigned subgrid_dimension;
    std::vector<unsigned> grid;
    std::forward_list<unsigned> value_range;
};

SudokuGrid generate_random_sudoku(unsigned dimension);

#endif