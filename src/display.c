// This is free and unencumbered software released into the public domain.
//
// For more information, please refer to the Unlicense, which should be
// included with the original source distribution or at <https://unlicense.org>
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
// AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
// ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


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

    int height = 26 > max_y ? max_y : 26, width = 73, x = (max_x - width) / 2,
        y = height > max_y ? 0 : (max_y - height) / 2;
    WINDOW *w = newwin( height, width, y, x );

    keypad( w, 1 );

    int input;
    int scroll = 0;
    char *str;

    do
    {

        wclear( w );
        box( w, 0, 0 );

        if( height < 26 )
        {

            mvwaddch( w, 1, width - 1, '^' );
            mvwaddch( w, height - 2, width - 1, 'v' );

        }

        y = 0;
        for( int line = scroll; line < 24 && y < height - 2; line++ )
        {

            y += 1;

            switch( line )
            {

                default:
                    continue;

                case 0:
                    str = "This is free and unencumbered software released into the public domain.";
                    break;

                case 2:
                    str = "Anyone is free to copy, modify, publish, use, compile, sell, or";
                    break;

                case 3:
                    str = "distribute this software, either in source code form or as a compiled";
                    break;

                case 4:
                    str = "binary, for any purpose, commercial or non-commercial, and by any";
                    break;

                case 5:
                    str = "means";
                    break;

                case 7:
                    str = "In jurisdictions that recognize copyright laws, the author or authors";
                    break;

                case 8:
                    str = "of this software dedicate any and all copyright interest in the";
                    break;

                case 9:
                    str = "software to the public domain. We make this dedication for the benefit";
                    break;

                case 10:
                    str = "of the public at large and to the detriment of our heirs and";
                    break;

                case 11:
                    str = "successors. We intend this dedication to be an overt act of";
                    break;

                case 12:
                    str = "relinquishment in perpetuity of all present and future rights to this";
                    break;

                case 13:
                    str = "software under copyright law.";
                    break;

                case 15:
                    str = "THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND,";
                    break;

                case 16:
                    str = "EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF";
                    break;

                case 17:
                    str = "MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.";
                    break;

                case 18:
                    str = "IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR";
                    break;

                case 19:
                    str = "OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,";
                    break;

                case 20:
                    str = "ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR";
                    break;

                case 21:
                    str = "OTHER DEALINGS IN THE SOFTWARE.";
                    break;

                case 23:
                    str = "For more information, please refer to <https://unlicense.org/>";
                    break;

            }

            mvwprintw( w, y, 1, str );

        }

        mvwprintw( w, height - 1, 1, " Press SPACE to close this window. " );

#ifdef DEBUG
        wprintw( w, "scroll: %02d ", scroll );
#endif

        wrefresh( w );

        input = wgetch( w );
        if( input == move_down && scroll < (26 - height) )
        {
            scroll += 1;
        }
        else if( input == move_up && scroll > 0 )
        {
            scroll -= 1;
        }

    } while( input != ' ' );

    delwin( w );

    clear();

}
