// This is public domain software.  Feel free to do whatever you want with it
// so long as you don't hold me liable for any damages - there is no warranty.
//
// If you want to pay me back for it, you can do so by taking ten minutes or
// more out of each day to remind yourself that you are valuable and your life
// is worth living, and treating yourself like someone worth taking care of.
// This software is already free; now free yourself.


// This file defines functions declared in grid.h


#include "globals.h"
#include "grid.h"


// Returns the value contained in the collision grid at the given coordinates.
// A negative value indicates an error.
grid_t check_collision( int x, int y )
{
    // If the collision grid hasn't been allocated yet, or the coordinates are
    // invalid, return an error.
    if( collision_grid == NULL )
    {
        return BAD_GRID;
    }

    // If the coordinates are invalid, return an error.
    else if( x < 0 || x > max_x || y < 0 || y > max_y )
    {
        return BAD_COORDS;
    }

    // Otherwise, return the value stored at the coordinates on the grid.
    else return collision_grid[(y * max_x) + x];
}


// Sets the value in the collision grid at the given coordinates.  Returns a
// negative value if there's an error with the grid - otherwise, returns the
// `value` which has been assigned.
grid_t set_collision( int x, int y, grid_t value )
{

    // If the collision grid hasn't been allocated yet, return an error.
    if( collision_grid == NULL )
    {
        return BAD_GRID;
    }

    // If the coordinates are invalid, return an error.
    else if( x < 0 || x > max_x || y < 0 || y > max_y )
    {
        return BAD_COORDS;
    }

    // If the `value` isn't valid, return an error.
    else if( value < 0 )
    {
        return BAD_VALUE;
    }

    else
    {
        collision_grid[(y * max_x) + x] = value;

        return value;
    }

} // grid_t set_collision( int x, int y, grid_t value )
