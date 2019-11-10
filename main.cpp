#include <iostream>
#include <fstream>
#include "functions.h"
#include <string>
using namespace std;

int main()
{
	string input_file_name = "C:\\Users\\Кирило\\source\\repos\\Sudoku\\Sudoku\\sudoku.txt";
	string output_file_name = "C:\\Users\\Кирило\\source\\repos\\Sudoku\\Sudoku\\sudoku_solved.txt";
	int** field = read_arr(input_file_name);
	init(field);
	print_arr(field);
	solve();
	print_arr(field);
	write_arr(field, output_file_name);
	return 0;
}