#include "functions.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stack>

bool start_num[9][9];
int x = 0;
int y = 0;
//std::stack<int> stack;
bool back = false;
bool correct = true;
unsigned short count = 0;
void solve(int** &field)
{
	count++;
	if (count == 3992) {
		std::cout << "\n 1long";
		return;
	}
	if (x > 8 || y > 8) return;
	if (x < 0 || y < 0) {
		std::cout << "\nError!";
		return;
	}
	if (back) {
		if (start_num[x][y]) {
			if (x > 0) {
				x--;
				return solve(field);
			}
			else {
				x = 8;
				y--;
				return solve(field);
			}
		}
		else back = false;
	}
	if (!start_num[x][y]) {
		field[x][y] = correct_put(field, x, y, field[x][y]);
		//print_arr(field);
	}
	if (field[x][y] == 0) {
		back = true;
		if (x > 0) {
			x--;
			return solve(field);
		}
		else {
			x = 8;
			y--;
			return solve(field);
		}
	}
	else {
		if (x < 8) {
			x++;
			return solve(field);
		}
		else {
			x = 0;
			y++;
			return solve(field);
		}
	}
}
int correct_put(int** &field, int x, int y, int start_n)
{
	correct = true;
	for (int num = start_n+1; num <= 9; num++) {
		correct = true;
		for (int row = 0; row < 9; row++) {
			if (row != y && field[x][row] == num) {
				correct = false;
				break;
			}
		}
		if (!correct) continue;
		for (int col = 0; col < 9; col++) {
			if (col != x && field[col][y] == num) {
				correct = false;
				break;
			}
		}
		if (!correct) continue;
		int hor_section = x / 3;
		int ver_section = y / 3;
		for (int i = 3 * hor_section; i < 3 * hor_section + 3; i++) {
			for (int j = 3 * ver_section; j < 3 * ver_section + 3; j++) {
				if (i != x || j != y) {
					if (field[i][j] == num) correct = false;
				}
			}
		}
		if (correct) {
			return num;
		}
	}
	return 0;
}
void write_arr(int** arr)
{
	std::ofstream out;
	out.open("C:\\Users\\Кирило\\source\\repos\\Sudoku\\Sudoku\\sudoku_solved.txt");
	if (out.is_open())
	{
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				out << arr[i][j] << " ";
			}
			out << "\n";
		}
	}
}
int** read_arr()
{
	int** result = new int*[9];
	for (int i = 0; i < 9; i++) result[i] = new int[9];
	char temp;
	std::ifstream in("C:\\Users\\Кирило\\source\\repos\\Sudoku\\Sudoku\\sudoku.txt");
	if (in.is_open())
	{
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				if (in >> temp) {
					if (temp >= 0x31 && temp <= 0x39) {
						result[i][j] = (int)(temp - 0x30);
						start_num[i][j] = true;
					}
					else if (temp == 0x2A || 1) {
						result[i][j] = 0;
						start_num[i][j] = false;
					}
				}
				else	result[i][j] = 0;
			}
		}

	}
	else std::cout << "\nError";
	in.close();
	return result;
}
void print_arr(int** arr)
{
	std::cout << "\n";
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			std::cout << arr[i][j] << " ";
		}
		std::cout << "\n";
	}
}