// This is public domain software.  Feel free to do whatever you want with it
// so long as you don't hold me liable for any damages - there is no warranty.
//
// If you want to pay me back for it, you can do so by taking ten minutes or
// more out of each day to remind yourself that you are valuable and your life
// is worth living, and treating yourself like someone worth taking care of.
// This software is already free; now free yourself.


#ifndef INCLUDE_RANK_H
# define INCLUDE_RANK_H


// This file defines the various "ranks" and how to calculate them.


typedef float rank_t;


// Calculates the player's rank based on the input `length` and `max`.
rank_t get_rank( unsigned int length, unsigned int max );


// Copies a string appropriate to the given `rank` into `str`.
void get_rank_name( char **str, rank_t rank );


// Each rank is a floating-point value.  Scores >= that value qualify for the
// rank.  Uroboros is reserved only for perfect scores.  Negative values are
// special-cased.
# define DIRT         0.000f
# define WORM         0.010f
# define SNAKE        0.025f
# define RATTLER      0.050f
# define PYTHON       0.075f
# define KING         0.100f
# define SNALLYGASTER 0.250f
# define WYRM         0.500f
# define QUETZALCOATL 0.750f
# define NIDHOGG      0.900f
# define ATUM         0.950f
# define UROBOROS     1.000f


#endif
