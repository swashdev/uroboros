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


// Initializes color & symbol data.
void init_symbols()
{

    sym_bone = '%';

    if( display_flags & COLOR )
    {

        sym_snake = ' ';
        sym_apple = '\'';

        color_snake = A_REVERSE | COLOR_PAIR( 1 );

        if( display_flags & HILITE_APPLE )
        {

            color_apple = A_BOLD | A_REVERSE | COLOR_PAIR ( 2 );
            color_gold  = A_BOLD | COLOR_PAIR( 3 );

        }
        else
        {

            color_apple = A_BOLD | COLOR_PAIR( 2 );
            color_gold  = A_BOLD | A_REVERSE | COLOR_PAIR( 3 );

        }

    } // if( display_flags & COLOR )
    else
    {

        sym_snake = '#';
        sym_apple = '%';

        color_snake = A_BOLD | A_REVERSE;
        color_apple = 0;
        color_gold  = A_BOLD;

    }

} // void init_symbols()


// Draws the apple.
void draw_apple( int y, int x, unsigned int count )
{

    // Decide whether to draw a regular apple or a golden apple.
    attr_t color = (count % 10) ? color_apple : color_gold;

    attron( color );

    mvaddch( y, x, sym_apple );

    attroff( color );

}


// Draws the snake.
void draw_snake( struct snake snek )
{

    struct segment *node = snek.head;

    int x, y;

    attron( color_snake );

    // Iterate through the whole list until we reach the tail.
    while( node != NULL )
    {

        x = node->x;
        y = node->y;

        mvaddch( y, x, sym_snake );

        node = node->next;

    }

    attroff( color_snake );

} // void draw_snake( struct snake )


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

        mvaddch( y, x, sym_bone );

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

    first_metadata = 0;
#endif

}


// Prints the license agreement in a separate window.
void display_license_agreement()
{

    WINDOW *w = centered_window( 12, 80 );

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
