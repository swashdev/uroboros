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


// Enable this to enable color.  Makes the game generally look better.
// Disabling this will cause the game to use alternate characters that should
// be more visible on displays which don't support color.
# define COLOR


// Enable this to reverse the apple's colors.  If your terminal's colors
// reverse the apple's colors, this will correct that.  Has no effect if
// `COLOR` is not enabled.
//# define HILITE_APPLE


// Character data for the snake & the apple.
# ifdef COLOR
#  define CHAR_SNAKE ' '
#  define CHAR_APPLE '\''
# else
#  define CHAR_SNAKE '#'
#  define CHAR_APPLE '%'
# endif


// Color data for the snake & the apple.
# ifdef COLOR
#  define COLOR_SNAKE A_REVERSE | COLOR_PAIR( 1 )
# else
#  define COLOR_SNAKE A_BOLD | A_REVERSE
# endif


# ifndef COLOR
#  define COLOR_APPLE 0
#  define COLOR_GOLD  A_BOLD
# else
// If `HILITE_APPLE` is enabled, the color schemes for the apples will be
// reversed, so that the terminal cursor doesn't screw them up.
#  ifdef HILITE_APPLE
#   define COLOR_APPLE A_BOLD | A_REVERSE | COLOR_PAIR( 2 )
#   define COLOR_GOLD  A_BOLD | COLOR_PAIR( 3 )
#  else
#   define COLOR_APPLE A_BOLD | COLOR_PAIR( 2 )
#   define COLOR_GOLD  A_BOLD | A_REVERSE | COLOR_PAIR( 3 )
#  endif
# endif


// Draws the snake.
void draw_snake( snake snek );


// Draws the snake but dead.
void draw_dead_snake( snake snek );


// Draws the apple.
void draw_apple( int y, int x, unsigned int count );


// Prints the version number.
void print_version_number( int y, int x );


// Prints the license agreement in a separate window.
void display_license_agreement();


#endif
