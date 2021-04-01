#include <time.h>
#include <stdio.h>
#include <stdbool.h>

//A puzzle, is a 2d array of ints, always of size 9x9
//It can have values from 0-9 (0 being unfilled)

//Get a single puzzle
void get_puzzle(FILE *file, int puzzle[9][9])
{
	fgetc(file); //Getting rid of new line
	for (int row = 0; row < 9; row++)
		for (int col = 0; col < 9; col++)
			puzzle[row][col] = fgetc(file) - 48;
}

//Prints a single puzzle to stdout
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

//Checks row given by row_index
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

//Checks column given by column_index
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

//Check grid given by row and column index (A grid is a 3x3 in sudoku)
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

//Check a given puzzle
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

//Check to make sure puzzle has no zeros
bool is_filled(int puzzle[9][9])
{
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			if (puzzle[i][j] == 0)
				return false;
	return true;
}

//Copy values from puzzle1 to puzzle2
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

//Get numbers in row
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

//Get numbers in col
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
void get_grid_nums(int puzzle[9][9], bool grid_numbers[9], int row_index, int column_index)
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
				grid_numbers[num - 1] = true;
			}
		}
	}
}

//Find a value for row and col, that is bigger than min_value, that satisfies the given puzzle
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

//Solve given puzzle recursively
//It just goes from top left, to bottom right, which is horribly inefficient
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

//Helper method, which calls solve_sudoku_recursive
bool solve_sudoku_recursively(int puzzle[9][9])
{
	int orginal_puzzle_copy[9][9];
	copy_puzzle(puzzle, orginal_puzzle_copy);
	return solve_sudoku_recursive(puzzle, 0, 0, 1, orginal_puzzle_copy);
}

//Solve sudoku iteratively
//But this basically does the same thing as solve_sudoku_recusive
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

int main()
{
	FILE *file;
	file = fopen("17_clue_puzzles.txt", "r");
	if (file == NULL)
	{
		printf("File can't be opened");
		return -1;
	}

	int number_of_puzzles;
	if (!fscanf(file, "%d", &number_of_puzzles))
	{
		return -1;
	}
	printf("Solving %d number of puzzles\n", number_of_puzzles);
	// number_of_puzzles = 10;

	int puzzle[9][9];

	clock_t start_of_program = clock();

	while (number_of_puzzles-- > 0)
	{
		get_puzzle(file, puzzle);
		printf("Number of Puzzles Left: %d\n\n", number_of_puzzles);
		show_puzzle(puzzle);

		clock_t start = clock();
		solve_sudoku_recursively(puzzle);
		clock_t end = clock();

		printf("\n\n");
		show_puzzle(puzzle);

		double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
		printf("Time spent: %f\n", time_spent);
		printf("CHECK: %s\n\n", check_sudoku(puzzle) ? "PASS" : "FAIL");
	}

	clock_t end_of_program = clock();
	double time_spent = (double)(end_of_program - start_of_program) / CLOCKS_PER_SEC;

	printf("\nTime spent total: %f\n", time_spent);

	fclose(file);
	return 0;
}