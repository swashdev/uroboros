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


// Enable this to move the terminal cursor over the apple after the screen is
// drawn.  This can hide the cursor on some terminals and creates less of an
// eyesore if successful.  It might also reveal the location of the apple even
// if it's hidden under the snake.
# define HILITE_APPLE


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
#  define COLOR_SNAKE A_BOLD | A_REVERSE | COLOR_PAIR( 1 )
# else
#  define COLOR_SNAKE A_BOLD | A_REVERSE
# endif


// If `HILITE_APPLE` is enabled, the color schemes for the apples will be
// reversed, unless we're compiling for Windows, because the Windows terminal
// doesn't work that way.
# ifndef COLOR
#  define COLOR_APPLE 0
#  define COLOR_GOLD  A_BOLD
# else
#  if defined( HILITE_APPLE ) && !defined( _WIN32 )
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
