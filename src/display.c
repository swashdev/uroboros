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
void draw_apple( int y, int x, unsigned int count )
{
    // Decide whether to draw a regular apple or a golden apple.
    attr_t color = (count % 10) ? COLOR_APPLE : COLOR_GOLD;

    attron( color );

    mvaddch( y, x, '\'' );

    attroff( color );
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
    mvprintw( y, x, "Uroboros v%d.%d.%d",
            VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH );

#if VERSION_BUILD > 0
    // Dev builds are indicated by a prerelease tag.
    printw( "-dev.%d", VERSION_BUILD );
#endif


    // Build metadata starts with a + and is separated by . in the semantic
    // versioning standard, so use a + for the first metadata tag and a . for
    // the rest.
    char first_metadata = 1;
#ifdef DEBUG
    // Debug builds are indicated by a build metadata tag.
    printw( "%cdebug", first_metadata ? '+' : '.'  );
#endif

#if defined( __APPLE__ ) || defined( __MACH__ )
    printw( "  (Thanks, Frenchy!)" );
#endif

}


// Prints the license agreement in a separate window.
void display_license_agreement()
{

    WINDOW *w = newwin( 12, 80, 0, 0 );

    box( w, 0, 0 );

    mvwprintw( w, 1, 2, "This is public domain software.  Feel free to do " );
    wprintw( w, "whatever you want with it" );
    mvwprintw( w, 2, 2, "so long as you don't hold me liable for any " );
    wprintw( w, "damages - there is no warranty." );

    mvwprintw( w, 4, 2, "If you want to pay me back for it, you can do so " );
    wprintw( w, "by taking ten minutes or" );
    mvwprintw( w, 5, 2, "more out of each day to remind yourself that you " );
    wprintw( w, "are valuable and your life" );
    mvwprintw( w, 6, 2, "is worth living, and treating yourself like " );
    wprintw( w, "someone worth taking care of." );
    mvwprintw( w, 7, 2, "This software is already free; now free yourself." );

    mvwprintw( w, 10, 2, "Press SPACE to close this window." );

    wrefresh( w );

    while( getch() != ' ' );

    delwin( w );

    clear();

}
