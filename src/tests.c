#include<assert.h>
#include<time.h>
#include<string.h>
#include "sudoku.h"

void print_time(clock_t start, clock_t end);

int main(){
	int puzzle[9][9] = {
		{0,0,0,0,0,0,0,1,0,},
		{4,0,0,0,0,0,0,0,0,},
		{0,2,0,0,0,0,0,0,0,},
		{0,0,0,0,5,0,4,0,7,},
		{0,0,8,0,0,0,3,0,0,},
		{0,0,1,0,9,0,0,0,0,},
		{3,0,0,4,0,0,2,0,0,},
		{0,5,0,1,0,0,0,0,0,},
		{0,0,0,8,0,6,0,0,0,}
	};

	int recursive_solution[9][9];
	int iterative_solution[9][9];

	memcpy(recursive_solution, puzzle, sizeof(puzzle));
	memcpy(iterative_solution, puzzle, sizeof(puzzle));

	printf("Running recursive\n");

	clock_t start_recursive = clock();
	solve_sudoku_recursively(recursive_solution);
	clock_t end_recursive = clock();
	print_time(start_recursive, end_recursive);

	printf("Running iterative\n");

	clock_t start_iterative = clock();
	solve_sudoku_iteratively(iterative_solution);
	clock_t end_iterative = clock();
	print_time(start_iterative, end_iterative);

	int correct_solution[9][9] = {
		{6,9,3,7,8,4,5,1,2},
		{4,8,7,5,1,2,9,3,6},
		{1,2,5,9,6,3,8,7,4},
		{9,3,2,6,5,1,4,8,7},
		{5,6,8,2,4,7,3,9,1},
		{7,4,1,3,9,8,6,2,5},
		{3,1,9,4,7,5,2,6,8},
		{8,5,6,1,2,9,7,4,3},
		{2,7,4,8,3,6,1,5,9}
	};

	int iterative_num, recursive_num, solution_num;

	for(int i = 0; i < 9; i++){
		for(int j = 0; j < 9; j++){
			iterative_num = iterative_solution[i][j];
			recursive_num = recursive_solution[i][j];
			solution_num = correct_solution[i][j];

			assert(iterative_num == solution_num);
			assert(recursive_num == solution_num);
		}
	}

	printf("Tests passed!\n");
}

void print_time(clock_t start, clock_t end){
	double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
	printf("Time spent: %f\n", time_spent);
}
