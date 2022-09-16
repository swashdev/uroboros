// This is public domain software.  Feel free to do whatever you want with it
// so long as you don't hold me liable for any damages - there is no warranty.
//
// If you want to pay me back for it, you can do so by taking ten minutes or
// more out of each day to remind yourself that you are valuable and your life
// is worth living, and treating yourself like someone worth taking care of.
// This software is already free; now free yourself.


#include <stdlib.h>

#include "segment.h"


// Returns whether or not the given `node` is the final node in the list.
char is_tail( segment *node )
{
    return node->next == NULL;
}


// Gets the `next` segment in the list from the `current` segment.
segment *get_next_segment( segment *current )
{
    return current->next;
}


// Moves the `current` segment to the given `x` and `y` coordinates, and
// recursively moves all of the segments following it.
void move_segment( segment *current, int x, int y )
{
    // First check to see if this is the tail.  If it is not, we have to move
    // the next segment first.
    if( current->next != NULL )
    {
        // Move the `next` segment to the coordinates of the `current`
        // segment.
        move_segment( current->next, current->x, current->y );
    }

    current->x = x;
    current->y = y;
}


// Adds a new segment with the given `x` and `y` values to the `current`
// segment.
void add_segment( segment *current, int x, int y )
{
    // Allocate memory for the new segment.
    if( current->next == NULL )
    {
        current->next = (segment*) malloc( sizeof( segment ) );
    }

    current->next->previous = current;

    current = current->next;

    current->x = x;
    current->y = y;
    current->next = NULL;
}


// Recursively frees up memory allocated for all of the segments in the list,
// starting with the `current` one.
void destroy_segment( segment *current )
{
    if( current->next != NULL )
    {
        destroy_segment( current->next );
    }

    free( current );
}
