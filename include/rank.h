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
# define DIRT         0.00f
# define WORM         0.01f
# define SNAKE        0.05f
# define RATTLER      0.10f
# define PYTHON       0.15f
# define COBRA        0.20f
# define KING         0.25f
# define VIPER        0.30f
# define LUCIA        0.35f
# define HOOP         0.40f
# define SNOW         0.45f
# define SNALLYGASTER 0.50f
# define ECHIDNA      0.55f
# define WYRM         0.60f
# define GLYCON       0.65f
# define NEHUSTAN     0.70f
# define QUETZALCOATL 0.75f
# define NIDHOGG      0.80f
# define MERETSEGERE  0.85f
# define SHESHNAG     0.90f
# define ATUM         0.95f
# define UROBOROS     1.00f


#endif
