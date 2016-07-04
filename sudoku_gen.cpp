#include <vector>
#include <random>
#include <assert.h>
#include <algorithm>
#include <iostream>
#include <iomanip>

#include "sudoku_gen.h"

using namespace std;

template<bool return_on_valid> bool generate_valid_sudoku(function<void(const SudokuGrid&)> callback, mt19937 mersenne_twister, SudokuGrid& grid, unsigned x, unsigned y)
{
    // We have filled the whole sudoku grid once we reach the beginning of dimension + 1 row, i.e. found a solution.
    if (x == grid.grid_dimension && y == 0)
    {
        callback(grid);
        return true;
    }

    // Shuffle our choices to generate a random puzzle
    auto choices = grid.cell_choices(x, y);
    if (return_on_valid)
    {
        shuffle(choices.begin(), choices.end(), mersenne_twister);
    }

    for (auto choice : choices)
    {
        grid.cell(x, y) = choice;
        const unsigned next_x = y + 1 == grid.grid_dimension ? x + 1 : x;
        const unsigned next_y = y + 1 == grid.grid_dimension ? 0 : y + 1;
        if (generate_valid_sudoku<return_on_valid>(callback, mersenne_twister, grid, next_x, next_y) && return_on_valid)
        {
            return true;
        }
    }

    // Mark this cell unoccupied before returning control.
    grid.cell(x, y) = 0;
    return false;
}

SudokuGrid generate_random_sudoku(unsigned dimension, function<void(const SudokuGrid&)> callback)
{
    random_device rd;

    SudokuGrid s(dimension);
    generate_valid_sudoku<true>(callback, mt19937(rd()), s, 0, 0);

    return s;
}

void generate_all_sudoku(unsigned dimension, function<void(const SudokuGrid&)> callback)
{
    random_device rd;

    auto s = SudokuGrid(dimension);
    generate_valid_sudoku<false>(callback, mt19937(rd()), s, 0, 0);
}

template<typename T> forward_list<T> range(T start, T end)
{
    forward_list<T> v;
    for (T x = end - 1; x >= start; --x)
    {
        v.push_front(x);
    }
    return v;
}

SudokuGrid::SudokuGrid(unsigned dimension) : grid_dimension(dimension), subgrid_dimension(sqrt(float(dimension))), grid(dimension * dimension, 0), value_range(range(unsigned(1), dimension + 1))
{
    assert(subgrid_dimension * subgrid_dimension == grid_dimension);
}

unsigned& SudokuGrid::cell(unsigned row, unsigned column)
{
    return grid[row * grid_dimension + column];
}

forward_list<unsigned>& SudokuGrid::filter_row(unsigned row, forward_list<unsigned>& v)
{
    for (unsigned i = 0; i < grid_dimension; ++i)
    {
        v.remove(cell(row, i));
    }
    return v;
}

forward_list<unsigned>& SudokuGrid::filter_column(unsigned col, forward_list<unsigned>& v)
{
    for (unsigned i = 0; i < grid_dimension; ++i)
    {
        v.remove(cell(i, col));
    }
    return v;
}

forward_list<unsigned>& SudokuGrid::filter_subgrid(unsigned row, unsigned col, forward_list<unsigned>& v)
{
    const unsigned row_start = subgrid_dimension * (row / subgrid_dimension);
    const unsigned col_start = subgrid_dimension * (col / subgrid_dimension);

    for (unsigned r = row_start * subgrid_dimension; r < row_start + subgrid_dimension; ++r)
    {
        for (unsigned c = col_start * subgrid_dimension; c < col_start + subgrid_dimension; ++c)
        {
            v.remove(cell(r, c));
        }
    }

    return v;
}

vector<unsigned> SudokuGrid::cell_choices(unsigned row, unsigned column)
{
    auto v = value_range;
    filter_row(row, filter_column(column, filter_subgrid(row, column, v)));

    return vector<unsigned>(v.begin(), v.end());
}

void SudokuGrid::print() const
{
    for (unsigned r = 0; r < grid_dimension; ++r)
    {
        for (unsigned c = 0; c < grid_dimension; ++c)
        {
            cout << setw(5) << grid[r * grid_dimension + c];
        }
        cout << endl;
    }
}