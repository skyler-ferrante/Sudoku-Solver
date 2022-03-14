#include<assert.h>
#include "sudoku.h"

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
	
	//show_puzzle(puzzle);
	solve_sudoku_recursively(puzzle);

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

	int puzzle_num, solution_num;

	for(int i = 0; i < 9; i++){
		for(int j = 0; j < 9; j++){
			puzzle_num = puzzle[i][j];
			solution_num = correct_solution[i][j];

			assert(puzzle_num == solution_num);
		}
	}

	printf("Tests passed!\n");
}
