#include <time.h>
#include <stdio.h>
#include "sudoku.h"

/**
 * Opens sudoku file
 * While true:
 * 	Reads puzzle from file
 * 	Solves puzzle
 * 	Prints time to solve puzzle
**/
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