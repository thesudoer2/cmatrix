#include <ncurses.h>
#include <thread>

#include "matrix.h"

using namespace std;

typedef unsigned short uint2_t;

int main()
{
	uint2_t max_y, max_x;

	initscr();
	noecho();
	curs_set(0);

	getmaxyx(stdscr, max_y, max_x);

	WINDOW* screen = newwin(max_y, max_x, 0, 0);

	matrix *matrix_ptr = new matrix(screen);

	matrix_ptr->start_matrix();
	
	endwin();

	return 0;
}
