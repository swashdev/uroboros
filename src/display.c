// This is public domain software.  Feel free to do whatever you want with it
// so long as you don't hold me liable for any damages - there is no warranty.
//
// If you want to pay me back for it, you can do so by taking ten minutes or
// more out of each day to remind yourself that you are valuable and your life
// is worth living, and treating yourself like someone worth taking care of.
// This software is already free; now free yourself.


#include "curses.h"

#include "globals.h"
#include "segment.h"
#include "snake.h"
#include "display.h"


// Draws the apple.
void draw_apple( int y, int x )
{
    attron( COLOR_APPLE );

    mvaddch( y, x, '\'' );

    attroff( COLOR_APPLE );
}


// Draws the golden apple.
void draw_golden_apple( int y, int x )
{
    attron( COLOR_GOLD );

    mvaddch( y, x, '\'' );

    attroff( COLOR_GOLD );
}


// Draws the snake.
void draw_snake( struct snake snek )
{
    struct segment *node = snek.head;

    int x, y;

    attron( COLOR_SNAKE );

    // Iterate through the whole list until we reach the tail.
    while( node != NULL )
    {
        x = node->x;
        y = node->y;

        mvaddch( y, x, ' ' );

        node = node->next;
    }

    attroff( COLOR_SNAKE );
}


// Draws the snake but dead.
void draw_dead_snake( struct snake snek )
{
    struct segment *node = snek.head;

    int x, y;

    // Iterate through the whole list until we reach the tail.
    while( node != NULL )
    {
        x = node->x;
        y = node->y;

        mvaddch( y, x, '%' );

        node = node->next;
    }
}


// Prints the version number.
void print_version_number( int y, int x )
{
    mvprintw( y, x, "Uroboros v%d.%d.%d-prerelease",
            VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH );

#ifdef DEBUG
    // Debug builds are indicated by a build metadata tag.
    printw( "+debug" );
#endif
}
