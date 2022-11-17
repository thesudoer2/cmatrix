#include <vector>
#include <thread>
#include <chrono>
#include <stdlib.h>

#include "matrix.h"

matrix::matrix(WINDOW *board)
{
	this->board = board;

	// calling matirx::initializing_screen method to initialize
	// screen
	matrix::initializing_screen();

	// calling matrix::fill_vectors method to fill defined
	// vectors
	matrix::fill_vectors();
}

void matrix::initializing_screen()
{
	// setting some basic settings for the board
	noecho();
	curs_set(0);

	getmaxyx(this->board, this->board_max_y, this->board_max_x);
}

void matrix::fill_vectors()
{
	matrix::vector_filler<bool>(this->is_used, this->board_max_x, false);
	matrix::vector_filler<uint2_t>(this->current_y_pos, this->board_max_x, 1);
	matrix::vector_filler<uint2_t>(this->string_length, this->board_max_x, 0);
	matrix::vector_filler<char>(this->current_char, this->board_max_x, ' '); 
	matrix::vector_filler<uint2_t>(this->max_string_length, this->board_max_x, 0);
	matrix::vector_filler<bool>(this->is_end, this->board_max_x, false);
	matrix::vector_filler<uint2_t>(this->removing_pos, this->board_max_x, 1);
	matrix::vector_filler<bool>(this->is_middle, this->board_max_x, false);
}

unsigned matrix::random_engine(int start, int end)
{
	auto m_start_time_point = std::chrono::high_resolution_clock::now();
	auto start_time = std::chrono::time_point_cast<std::chrono::microseconds>(m_start_time_point).time_since_epoch().count();

	if (start > end)
	{
		// swap value of start and end
		int swap;
		swap = start;
		start = end;
		end = swap;
	}

	srand(start_time);

	unsigned random_number = rand();

	unsigned result = (random_number % (end - (start - 1))) + start;

	return result;
}

uint2_t matrix::rand_pos_in_board()
{
	int random_number = matrix::random_engine(1, this->board_max_x - 2);

	if (random_number % 2 == 0)
	{
		random_number--;
	}

	return random_number;
}

uint2_t matrix::rand_length()
{
	return matrix::random_engine(5, this->board_max_y / 2 + 3);
}

char matrix::rand_char()
{
	return static_cast<char>(matrix::random_engine(33, 126));
}

void matrix::set_colors()
{
	start_color();

	init_pair(1, COLOR_GREEN, COLOR_BLACK); // black background with green text
	init_pair(2, COLOR_WHITE, COLOR_BLACK); // black background with white text
	init_pair(3, COLOR_BLACK, COLOR_BLACK); // black background with black text
}

void matrix::start_matrix()
{
	matrix::set_colors();

	uint2_t random_number;

	while(true)
	{
		// first index is not used (from index 1 to (this->board_max_x - 2)
		for (unsigned i {1}; i < (this->board_max_x - 2); ++i)
		{
			random_number = matrix::rand_pos_in_board();

			if(!this->is_used[random_number])
			{
				this->is_used[random_number] = true;
				this->max_string_length[random_number] = matrix::rand_length();
				this->current_char[random_number] = matrix::rand_char();
			}

			if (this->is_used[i])
			{
				wattron(this->board, COLOR_PAIR(1) | A_BOLD);
				mvwaddch(this->board, this->current_y_pos[i], i, this->current_char[i]);
				wattroff(this->board, COLOR_PAIR(1) | A_BOLD);


				if (this->current_y_pos[i] == (this->board_max_y - 2))
				{
					this->is_end[i] = true;
				}

				if (this->is_end[i])
				{
					matrix::remove(i);

					if (this->string_length[i] == 0)
					{
						matrix::remove(i);
						matrix::release_index(i);
						continue;
					}
				}
				else
				{
					if (this->string_length[i] == this->max_string_length[i])
					{
						// this means removing characters from the board must be started
						this->is_middle[i] = true;
					}
	
					if (this->is_middle[i])
					{
						add(i);
						remove(i);
					}
					else
					{
						add(i);
					}
				}
	
				matrix::display();
			}

			std::this_thread::sleep_for(std::chrono::microseconds(20));
		}
	}
}

void matrix::add(uint2_t index_num)
{
	matrix::set_colors();

	this->current_char[index_num] = matrix::rand_char();
	++this->current_y_pos[index_num];
	++this->string_length[index_num];


	if (this->current_y_pos[index_num] != (this->board_max_y - 2))
	{
		wattron(this->board, COLOR_PAIR(2) | A_BOLD);
		mvwaddch(this->board, this->current_y_pos[index_num], index_num, this->current_char[index_num]);
		wattroff(this->board, COLOR_PAIR(2) | A_BOLD);
	}
}

void matrix::remove(uint2_t index_num)
{
	matrix::set_colors();

	wattron(this->board, COLOR_PAIR(3));
	mvwaddch(this->board, removing_pos[index_num], index_num, ' ');
	wattroff(this->board, COLOR_PAIR(3));

	++removing_pos[index_num];

	--this->string_length[index_num];
}

void matrix::release_index(uint2_t index_num)
{
	this->current_y_pos[index_num] = 1;
	this->is_used[index_num] = false;
	this->is_middle[index_num] = false;
	this->is_end[index_num] = false;
	this->removing_pos[index_num] = 1;
	this->string_length[index_num] = 0;
	this->max_string_length[index_num] = 0;
	this->current_char[index_num] = ' ';
}

void matrix::display()
{
	wrefresh(this->board);
}
