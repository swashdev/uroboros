// This is public domain software.  Feel free to do whatever you want with it
// so long as you don't hold me liable for any damages - there is no warranty.
//
// If you want to pay me back for it, you can do so by taking ten minutes or
// more out of each day to remind yourself that you are valuable and your life
// is worth living, and treating yourself like someone worth taking care of.
// This software is already free; now free yourself.


#ifndef INCLUDE_SNAKE_H
# define INCLUDE_SNAKE_H


# include "segment.h"


// The `snake` struct is used to store the snake in a format convenient for
// manipulating it.

typedef struct snake snake;
struct snake
{
    // The number of segments on the snake.
    unsigned int length;

    // The coordinates of the "ghost" segment used when the snake grows.
    int ghost_x, ghost_y;

    // The `head` and `tail` of the snake.
    segment *head, *tail;
};


// Adds a segment to the snake.
void grow_snake( snake *snek );


// Deallocates all memory allocated for the snake.
void destroy_snake( snake *snek );


// Moves the snake in the given direction.
void move_snake( snake *snek, signed char direction );


#endif
