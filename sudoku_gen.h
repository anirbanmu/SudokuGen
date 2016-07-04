#ifndef _SUDOKU_GEN_H_DECL_
#define _SUDOKU_GEN_H_DECL_

#include <vector>
#include <forward_list>
#include <functional>
#include <random>

struct SudokuGrid
{
    SudokuGrid(unsigned dimension);

    unsigned& cell(unsigned row, unsigned column);
    std::forward_list<unsigned>& filter_row(unsigned row, std::forward_list<unsigned>& v);
    std::forward_list<unsigned>& filter_column(unsigned col, std::forward_list<unsigned>& v);
    std::forward_list<unsigned>& filter_subgrid(unsigned row, unsigned col, std::forward_list<unsigned>& v);
    std::vector<unsigned> cell_choices(unsigned row, unsigned column);
    void print() const;

    friend std::ostream& operator<<(std::ostream&, const SudokuGrid&);

    unsigned grid_dimension;
    unsigned subgrid_dimension;
    std::vector<unsigned> grid;
    std::forward_list<unsigned> value_range;
};

// Callback function may be called on multiple threads; no guarantees.
class SudokuGenerator
{
    public:
        SudokuGenerator(unsigned dimension, std::function<void(const SudokuGrid&)> c) : grid(dimension), callback(c), mersenne_twister(rd())
        {
        }

        void generate_random_sudoku();
        void generate_all_sudoku();

    private:
        template<bool return_on_valid> static bool generate_valid_sudoku(std::function<void(const SudokuGrid&)> callback, std::mt19937 mersenne_twister, SudokuGrid& grid, unsigned x, unsigned y);

        SudokuGrid grid;
        std::function<void(const SudokuGrid&)> callback;
        std::random_device rd;
        std::mt19937 mersenne_twister;
};

#endif