// This is public domain software.  Feel free to do whatever you want with it
// so long as you don't hold me liable for any damages - there is no warranty.
//
// If you want to pay me back for it, you can do so by taking ten minutes or
// more out of each day to remind yourself that you are valuable and your life
// is worth living, and treating yourself like someone worth taking care of.
// This software is already free; now free yourself.


#ifndef INCLUDE_GRID_H
# define INCLUDE_GRID_H


# include <stdlib.h>


// This file defines the "collision grid," used to perform collision detection,
// as well as constants and functions related to it.


// Possible values to be stored on the collision grid.
# define EMPTY     0
# define SEGMENT   1
# define APPLE     2

// Error values which may be returned by functions which interact with the 
// collision grid.
# define BAD_VALUE  -3
# define BAD_COORDS -2
# define BAD_GRID   -1


typedef signed char grid_t;


grid_t *collision_grid = NULL;


// Returns the value contained in the collision grid at the given coordinates.
// A negative value indicates an error.
grid_t check_collision( int x, int y );


// Sets the value in the collision grid at the given coordinates.  Returns a
// negative value if there's an error with the grid - otherwise, returns the
// `value` which has been assigned.
grid_t set_collision( int x, int y, grid_t value );


#endif
