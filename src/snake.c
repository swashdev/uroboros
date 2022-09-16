// This is public domain software.  Feel free to do whatever you want with it
// so long as you don't hold me liable for any damages - there is no warranty.
//
// If you want to pay me back for it, you can do so by taking ten minutes or
// more out of each day to remind yourself that you are valuable and your life
// is worth living, and treating yourself like someone worth taking care of.
// This software is already free; now free yourself.


#include <stdlib.h>

#include "globals.h"
#include "segment.h"
#include "snake.h"


// Adds a segment to the snake.
void grow_snake( snake *snek )
{
    // The new segment will use the coordinates of the ghost segment the snake
    // has stored.
    int x = snek->ghost_x;
    int y = snek->ghost_y;

    // Add the new segment.
    add_segment( snek->tail, x, y );

    // Assign the new segment to be the snake's tail.
    snek->tail = snek->tail->next;

    // Increment snake length.
    snek->length++;
}


// Deallocates all memory allocated for the snake.
void destroy_snake( snake *snek )
{
    snek->length = 0;
    destroy_segment( snek->head );
}


// Moves the snake in the given direction.
void move_snake( snake *snek, signed char direction )
{
    int x, y;

    // Decide the x & y modifiers based on the current `direction`.
    switch( direction )
    {

        default:
            x =  0;
            y =  0;
            break;

        case UP:
            x =  0;
            y = -1;
            break;

        case DOWN:
            x =  0;
            y =  1;
            break;

        case LEFT:
            x = -1;
            y =  0;
            break;

        case RIGHT:
            x =  1;
            y =  0;
            break;

    } // switch( direction )

    // Store the tail's old position as a ghost.
    if( x != 0 || y != 0 )
    {
        snek->ghost_x = snek->tail->x;
        snek->ghost_y = snek->tail->y;
    }

    // Add the current coordinates to the modifiers.
    x += snek->head->x;
    y += snek->head->y;

    // Wrap around if the snake goes beyond the boundaries of the screen.
    if( x >= max_x )  x -= max_x;
    else if( x < 0 )  x = max_x - 1;
    if( y >= max_y )  y -= max_y;
    else if( y < 0 )  y = max_y - 1;

    // Allocate a new segment.
    segment *new_head = (segment*) malloc( sizeof( segment ) );
    new_head->previous = NULL;
    new_head->x = x;
    new_head->y = y;

    // Set the head as the "next" segment.
    new_head->next = snek->head;
    snek->head->previous = new_head;

    // Set the new segment as the new snake head.
    snek->head = new_head;

    // Remove the old tail.
    snek->tail = snek->tail->previous;
    destroy_segment( snek->tail->next );
    snek->tail->next = NULL;

} // void move_snake( snake*, signed char )
