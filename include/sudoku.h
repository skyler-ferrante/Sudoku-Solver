#ifndef SUDOKU
#define SUDOKU

#include <stdio.h>
#include <stdbool.h>

int check_file(FILE *file);
void get_puzzle(FILE *file, int puzzle[9][9]);
void show_puzzle(int puzzle[9][9]);

bool check_row(int puzzle[9][9], int row_index);
bool check_column(int puzzle[9][9], int column_index);
bool check_grid(int puzzle[9][9], int row_index, int column_index);
bool check_sudoku(int puzzle[9][9]);
bool check_filled(int puzzle[9][9]);

void copy_puzzle(int puzzle1[9][9], int puzzle2[9][9]);

int get_amount_in_row(int puzzle[9][9], int row_index);
int get_amount_in_col(int puzzle[9][9], int col_index);

void get_row_nums(int puzzle[9][9], bool nums[9], int row_index);
void get_col_nums(int puzzle[9][9], bool nums[9], int col_index);
void get_grid_nums(int puzzle[9][9], bool nums[9], int row_index, int column_index);

int  solve_sudoku_one_point(int puzzle[9][9], int row, int col, int min_value);
bool solve_sudoku_recursive(int puzzle[9][9], int row, int col, int min_value, int orginal_puzzle_copy[9][9]);
bool solve_sudoku_recursively(int puzzle[9][9]);
bool solve_sudoku_iteratively(int puzzle[9][9]);

#endif