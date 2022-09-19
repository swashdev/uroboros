// This is public domain software.  Feel free to do whatever you want with it
// so long as you don't hold me liable for any damages - there is no warranty.
//
// If you want to pay me back for it, you can do so by taking ten minutes or
// more out of each day to remind yourself that you are valuable and your life
// is worth living, and treating yourself like someone worth taking care of.
// This software is already free; now free yourself.


#include <stdlib.h>

#include "segment.h"


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
