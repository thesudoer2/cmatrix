#include <ncurses.h>
#include <time.h>
#include <random>

#ifndef MATRIX_H
#define MATRIX_H

typedef unsigned short uint2_t;

class matrix
{
public:
	matrix(WINDOW *board);

	void start_matrix();
private:
	WINDOW *board;

	uint2_t board_max_y, board_max_x;

	// making a methog to doing some initial jobs
	// for screen and data-members
	void initializing_screen();

	/*
	 *	 in the matrix program, a string with random length,
	 *	 cascades .
	 *	 in the following member-functions, 
	 *
	 *	 	- at the first one, we create a random position for 
	 *	 	  start of the string .
	 *
	 *	 	- at the second one, we create a random legth for the
	 *	 	  string
	 *
	 *	 	- at third one, we create a random char that the string
	 *	 	  made from
	 */
	unsigned random_engine(int, int); // this random engine will generate random numbers
	uint2_t rand_pos_in_board(); // between 1 to (this->max_x_board - 2)
	uint2_t rand_length(); // between 5 to (this->max_y_board / 2)
	char rand_char();


	// using this vector we can records current position of vertical string
	// (current Y position in screen (X position is clear))
	std::vector<uint2_t> current_y_pos; // we need indices 1 to (this->board_max_x - 1)

	// if a X position in screen is used, the related index must be true (each
	// X position has a index number and (index_number = x_position))
	std::vector<bool> is_used; // we need indices 1 to (this->board_max_x - 1)

	// this vector contains number of characters that
	// is used in a vertical string
	std::vector<uint2_t> string_length;

	// this method stores maximum length that a
	// vertical string can have (this number is
	// variable, because we use matrix::rand_length() method
	// for defining length.
	std::vector<uint2_t> max_string_length;

	// this method stores current (the latest) char of
	// a vertical string
	std::vector<char> current_char;

	/*
	 *	if vertical string's length is equals to
	 *	(this->board_max_y - 1), it means this string
	 *	shouldn't grow anymore and in other words ,
	 *	this is the end!!
	 */
	std::vector<bool> is_end;

	// is middle means this->string_length[i] = this->max_string_length[i]
	// and this means we must start removing chars from above to bottom
	std::vector<bool> is_middle;

	// when we are removing characters in screen, this vector records
	// where we are!
	std::vector<uint2_t> removing_pos;

	// defining a template method to fill vectors
	template <typename T>
		void vector_filler(std::vector<T> &target_vector, uint2_t elements_count, T element)
		{
			target_vector.resize(elements_count, element);
		}

	// the following function just call the vector_filler() function
	// with correct arguments
	void fill_vectors();

	// the following function adds a new character to the window
	void add(uint2_t);

	// the following function removes a character from the window
	void remove(uint2_t);

	void set_colors();

	// the following function refreshes the window
	void display();

	// after writing in a certain index (board_x_pos)
	// this function releases that index
	void release_index(uint2_t index_num);
};

#endif  // MATRIX_H
