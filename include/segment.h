// This is public domain software.  Feel free to do whatever you want with it
// so long as you don't hold me liable for any damages - there is no warranty.
//
// If you want to pay me back for it, you can do so by taking ten minutes or
// more out of each day to remind yourself that you are valuable and your life
// is worth living, and treating yourself like someone worth taking care of.
// This software is already free; now free yourself.


// The segments of the snake are stored in a linked list.  Each segment stores
// its own coordinates to make it easier to move them independently.


#ifndef INCLUDE_SEGMENT_H
# define INCLUDE_SEGMENT_H


typedef struct segment segment;
struct segment
{
    int x, y;

    segment *next, *previous;
};


// Adds a new segment with the given `x` and `y` values to the `current`
// segment.
void add_segment( segment *current, int x, int y );


// Recursively frees up memory allocated for all of the segments in the list,
// starting with the `current` one.
void destroy_segment( segment *current );


#endif
