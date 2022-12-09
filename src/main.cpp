#include <ncurses.h>
#include <thread>
#include <chrono>

#include "matrix.h"

using namespace std;

typedef unsigned short uint2_t;

void run_thread(matrix*);

int main()
{
	uint2_t max_y, max_x;

	initscr();
	noecho();
	curs_set(0);

	getmaxyx(stdscr, max_y, max_x);

	WINDOW* screen = newwin(max_y, max_x, 0, 0);
	nodelay(screen, true);

	matrix *matrix_ptr = new matrix(screen);
	std::thread th; // thread for executing start_matrix() method (from matrix class)

//	while (wgetch(screen) != 'q')
	while (1)
	{
		th = std::thread(run_thread, matrix_ptr);

		if (th.joinable())
			th.join();

		std::this_thread::sleep_for(std::chrono::milliseconds(3));
	}
	
	endwin();

	return 0;
}

void run_thread(matrix* self)
{
	self->start_matrix();
}
