#include <time.h>

#include "sudoku.h"

/**
 * A puzzle is a 2d array of ints, always of size 9x9
 * A point in a puzzle can have values from 0-9 (0 being unfilled)
 * A puzzle has nine 3x3 grids
 * 
 * For a puzzle to be considered solved:
 * 	The puzzle has no empty spots
 * 	The puzzles grids contain unique digits (1-9)
 * 	The puzzles rows and columns contain unique digits (1-9)
**/

/**
 * Get a single puzzle
 * 
 * file: file containing sudoku clues, with one line per sudoku puzzle
 * puzzle: puzzle buffer to fill with puzzle data from file 
**/
void get_puzzle(FILE *file, int puzzle[9][9])
{
	fgetc(file); //Getting rid of new line
	for (int row = 0; row < 9; row++)
		for (int col = 0; col < 9; col++)
			puzzle[row][col] = fgetc(file) - 48;
}

/**
 * Prints a single puzzle to stdout
 * 
 * puzzle: puzzle to show
**/
void show_puzzle(int puzzle[9][9])
{
	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			if (col % 3 == 2)
				printf("%d   ", puzzle[row][col]);
			else
				printf("%d | ", puzzle[row][col]);
		}
		if (row % 3 == 2)
			printf("\n");
		printf("\n");
	}
}

/**
 * Checks row given by row_index
 * 
 * puzzle: puzzle to check row
 * row_index: number row to check
 * 
 * returns: true  if row  is valid
 * 			false if row  is invalid
**/
bool check_row(int puzzle[9][9], int row_index)
{
	bool found_numbers[9] = {0}; //Initialized to zero

	for (int i = 0; i < 9; i++)
	{
		int num = puzzle[row_index][i];
		if (num == 0)
			continue;
		if (found_numbers[num - 1])
			return false;
		found_numbers[num - 1] = true;
	}

	return true;
}

/**
 * Checks column given by column_index
 * 
 * puzzle: puzzle to check column
 * column_index: number column to check
 * 
 * returns: true  if column  is valid
 * 			false if column  is invalid
**/
bool check_column(int puzzle[9][9], int column_index)
{
	bool found_numbers[9] = {0};

	for (int i = 0; i < 9; i++)
	{
		int num = puzzle[i][column_index];
		if (num == 0)
			continue;
		if (found_numbers[num - 1])
			return false;
		found_numbers[num - 1] = true;
	}
	return true;
}

/**
 * Check grid given by row and column index
 * 
 * puzzle: puzzle to check grid of
 * row_index: row of grid (0-3)
 * column_index: column of grid (0-3)
 * 
 * returns: true  if grid is valid
 * 			false if grid is invalid
**/
bool check_grid(int puzzle[9][9], int row_index, int column_index)
{
	bool found_numbers[9] = {0};

	row_index *= 3;
	column_index *= 3;

	int num;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			num = puzzle[i + row_index][j + column_index];
			if (num == 0)
				continue;
			if (found_numbers[num - 1])
				return false;
			found_numbers[num - 1] = true;
		}
	}
	return true;
}

/**
 * Check a given puzzle
 * checks rows, columns, and grids
 * does not check if filled
 * 
 * puzzle: puzzle to check
 * 
 * returns: true  if puzzle is valid
 * 			false if puzzle is invalid
**/
bool check_sudoku(int puzzle[9][9])
{
	for (int i = 0; i < 9; i++)
	{
		if (!(check_row(puzzle, i) && check_column(puzzle, i)))
		{
			return false;
		}
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (!check_grid(puzzle, i, j))
			{
				return false;
			}
		}
	}
	return true;
}

/**
 * Check to make sure puzzle has no zeros
 * 
 * puzzle: puzzle to check if any unfilled spots
**/
bool check_filled(int puzzle[9][9])
{
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			if (puzzle[i][j] == 0)
				return false;
	return true;
}

/**
 * Copy values from puzzle1 to puzzle2
 * 
 * puzzle1: puzzle to copy from
 * puzzle2: puzzle to copy to
**/
void copy_puzzle(int puzzle1[9][9], int puzzle2[9][9])
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			puzzle2[i][j] = puzzle1[i][j];
		}
	}
}

/**
 * Get numbers in row
 * 
 * puzzle: puzzle to get row numbers from
 * nums: true if number-1 is contained (zero ignored)
 * row_index: row to get numbers from
**/
void get_row_nums(int puzzle[9][9], bool nums[9], int row_index)
{
	for (int i = 0; i < 9; i++)
	{
		int value = puzzle[row_index][i];
		if (value != 0)
		{
			nums[value - 1] = true;
		}
	}
}

/**
 * Get numbers in col
 * 
 * puzzle: puzzle to get col numbers from
 * nums: true if number-1 is contained (zero ignored)
 * col_index: col to get numbers from
**/ 
void get_col_nums(int puzzle[9][9], bool nums[9], int col_index)
{
	for (int i = 0; i < 9; i++)
	{
		int value = puzzle[i][col_index];
		if (value != 0)
		{
			nums[value - 1] = true;
		}
	}
}

//Get numbers in grid
/**
 * Get numbers in grid
 * 
 * puzzle: puzzle to get grid numbers from
 * nums: true if number-1 is contained (zero ignored)
 * row_index: row of grid (0-3)
 * column_index: column of grid (0-3) 
**/
void get_grid_nums(int puzzle[9][9], bool nums[9], int row_index, int column_index)
{
	row_index *= 3; //Grids are 3x3
	column_index *= 3;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			int num = puzzle[i + row_index][j + column_index];
			if (num != 0)
			{
				nums[num - 1] = true;
			}
		}
	}
}

/**
 * Find a value for row and col, that is bigger than min_value, that satisfies the given puzzle
 *
 * puzzle: puzzle to solve point on
 * row: row of point to solve
 * col: col of point to solve
 * min_value: minimum value of point
 * 
 * returns: 0 if no possible solve over min_value
 * 			value of the first found possible solve
**/
int solve_sudoku_one_point(int puzzle[9][9], int row, int col, int min_value)
{
	int grid_row_index = (int)row / 3;
	int grid_column_index = (int)col / 3;

	//These are arrays of 9, initialized with false
	bool row_nums[9] = {false};
	bool col_nums[9] = {false};
	bool grid_nums[9] = {false};

	get_row_nums(puzzle, row_nums, row);
	get_col_nums(puzzle, col_nums, col);
	get_grid_nums(puzzle, grid_nums, grid_row_index, grid_column_index);

	for (int value = min_value; value <= 9; value++)
	{
		puzzle[row][col] = value;
		if (!row_nums[value - 1] && !col_nums[value - 1] && !grid_nums[value - 1])
		{
			puzzle[row][col] = value;
			return value;
		}
	}
	puzzle[row][col] = 0;
	return 0;
}

/**
 * Solve given puzzle recursively
 * It just goes from top left, to bottom right, which is horribly inefficient
 * 
 * puzzle: puzzle to solve
 * row: row to start
 * col: col to start
 * min_value: min_value for point
 * orginal_puzzle_copy: copy of puzzle
 * 
 * returns: false if no solution
 * 			true  if puzzle solved
**/
bool solve_sudoku_recursive(int puzzle[9][9], int row, int col, int min_value, int orginal_puzzle_copy[9][9])
{
	if (row == 8 && col == 9)
		return true;

	if (col > 8)
	{
		col = 0;
		row++;
	}

	//If there is already something there
	if (orginal_puzzle_copy[row][col] != 0)
	{
		return solve_sudoku_recursive(puzzle, row, col + 1, 1, orginal_puzzle_copy);
	}

	//Get a working value, or get 0
	int value = solve_sudoku_one_point(puzzle, row, col, min_value);

	if (value == 0)
	{
		return false;
	}

	bool solution = solve_sudoku_recursive(puzzle, row, col + 1, 1, orginal_puzzle_copy);

	if (!solution)
		return solve_sudoku_recursive(puzzle, row, col, value + 1, orginal_puzzle_copy);

	return solution;
}

/**
 * Helper method, which calls solve_sudoku_recursive on single puzzle
 * 
 * puzzle: puzzle to solve
 *  
 * returns: false if no solution
 * 			true  if puzzle solved
**/
bool solve_sudoku_recursively(int puzzle[9][9])
{
	int orginal_puzzle_copy[9][9];
	copy_puzzle(puzzle, orginal_puzzle_copy);
	return solve_sudoku_recursive(puzzle, 0, 0, 1, orginal_puzzle_copy);
}

/**
 * Solve sudoku iteratively
 * Basically does the same thing as solve_sudoku_recusive
 * 
 * puzzle: puzzle to solve
**/
bool solve_sudoku_iteratively(int puzzle[9][9])
{
	int orginal_puzzle_copy[9][9];
	copy_puzzle(puzzle, orginal_puzzle_copy);

	if (!check_sudoku(puzzle))
	{
		return false;
	}

	int row = 0;
	int col = 0;
	int min_value = 1;
	int value = 0;

	while (row != 8 || col != 9)
	{

		if (col > 8)
		{
			col = 0;
			row++;
		}

		if (orginal_puzzle_copy[row][col] != 0)
		{
			col++;
			continue;
		}

		value = solve_sudoku_one_point(puzzle, row, col, min_value);

		if (value == 0)
		{
			do
			{
				if (col == 0)
				{
					if (row == 0)
					{
						return false;
					}
					row--;
					col = 8;
				}
				else
				{
					col--;
				}
			} while (orginal_puzzle_copy[row][col] != 0);
			min_value = puzzle[row][col] + 1;
			continue;
		}
		puzzle[row][col] = value;
		col++;
		min_value = 1;
	}

	return true;
}