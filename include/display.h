// This is public domain software.  Feel free to do whatever you want with it
// so long as you don't hold me liable for any damages - there is no warranty.
//
// If you want to pay me back for it, you can do so by taking ten minutes or
// more out of each day to remind yourself that you are valuable and your life
// is worth living, and treating yourself like someone worth taking care of.
// This software is already free; now free yourself.


#ifndef INCLUDE_DISPLAY_H
# define INCLUDE_DISPLAY_H


// This header file declares functions related to display code.


# include "snake.h"


// Enable this to move the terminal cursor over the apple after the screen is
// drawn.  This can hide the cursor on some terminals and creates less of an
// eyesore if successful.  It might also reveal the location of the apple even
// if it's hidden under the snake.
# define HILITE_APPLE


// Color data for the snake & the apple.
# define COLOR_SNAKE A_BOLD | A_REVERSE | COLOR_PAIR( 1 )

# ifdef HILITE_APPLE
#  define COLOR_APPLE A_BOLD | A_REVERSE | COLOR_PAIR( 2 )
#  define COLOR_GOLD  A_BOLD | COLOR_PAIR( 3 )
# else
#  define COLOR_APPLE A_BOLD | COLOR_PAIR( 2 )
#  define COLOR_GOLD  A_BOLD | A_REVERSE | COLOR_PAIR( 3 )
# endif


// Draws the snake.
void draw_snake( snake snek );


// Draws the snake but dead.
void draw_dead_snake( snake snek );


// Draws the apple.
void draw_apple( int y, int x );


// Draws the golden apple.
void draw_golden_apple( int y, int x );


// Prints the version number.
void print_version_number( int y, int x );


// Prints the license agreement in a separate window.
void display_license_agreement();


#endif
