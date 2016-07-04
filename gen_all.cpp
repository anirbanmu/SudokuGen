#include <iostream>
#include <thread>
#include <fstream>
#include <string>
#include <sstream>
#include <mutex>
#include <iomanip>
#include <unordered_map>

#include "sudoku_gen.h"

using namespace std;

static mutex files_mutex;
static unordered_map<thread::id, string> files;

ofstream get_thread_file()
{
    static unsigned i = 0;
    lock_guard<mutex> lock(files_mutex);

    const auto filename = "thread_part_file." + to_string(i++);
    files[this_thread::get_id()] = filename;
    return ofstream(filename, ios::out);
}

void write_valid_sudoku(const SudokuGrid& g)
{
    static thread_local ofstream thread_file = get_thread_file();
    thread_file << g << endl;
}

int main(int, char**)
{
    SudokuGenerator(9, write_valid_sudoku).generate_all_sudoku();
    return 0;
}