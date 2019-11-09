#include <iostream>
#include <fstream>
#include "functions.h"

using namespace std;

int main()
{
	int** field = read_arr();
	print_arr(field);
	solve(field);
	print_arr(field);
	write_arr(field);
	return 0;
}