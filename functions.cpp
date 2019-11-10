#include "functions.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stack>

using namespace std;

bool start_num[9][9];
static int x = 0;
static int y = 0;
bool back = false;
bool correct = true;
int** field = 0;
int size = 0;
void init(int** &field_)
{
	field = field_;
}
void solve()
{
	while ((!(x > 8 || y > 8)) && (!(x < 0 || y < 0)))
	{
		if (back) {
			if (start_num[x][y]) {
				if (x > 0) {
					x--;
				}
				else {
					x = 8;
					y--;
				}
			}
			else back = false;
		}
		else {
			if (!start_num[x][y]) {
				field[x][y] = correct_put(x, y, field[x][y]);
				//print_arr(field);
			}
			if (field[x][y] == 0) {
				back = true;
				if (x > 0) {
					x--;
				}
				else {
					x = 8;
					y--;
				}
			}
			else {
				if (x < 8) {
					x++;
				}
				else {
					x = 0;
					y++;
				}
			}
		}
	}
}
int correct_put(int x, int y, int start_n)
{
	correct = true;
	for (int num = start_n + 1; num <= 9; num++) {
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
void write_arr(int** arr, string output_file_name)
{
	std::ofstream out;
	out.open(output_file_name);
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
int** read_arr(string input_file_name)
{
	int** result = new int*[9];
	for (int i = 0; i < 9; i++) result[i] = new int[9];
	char temp;
	std::ifstream in(input_file_name);
	if (in.is_open())
	{
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				if (in >> temp) {
					if (temp >= 0x31 && temp <= 0x39) {
						result[i][j] = (int)(temp - 0x30);
						start_num[i][j] = true;
					}
					else if (temp == 0x2A || temp == 0x30) {
						result[i][j] = 0;
						start_num[i][j] = false;
					}
					else {
						if (j > 0) j--;
						else {
							j = 8;
							i--;
						}
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