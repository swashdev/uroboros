// This is public domain software.  Feel free to do whatever you want with it
// so long as you don't hold me liable for any damages - there is no warranty.
//
// If you want to pay me back for it, you can do so by taking ten minutes or
// more out of each day to remind yourself that you are valuable and your life
// is worth living, and treating yourself like someone worth taking care of.
// This software is already free; now free yourself.


#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "ncurses.h"

#include "globals.h"
#include "segment.h"
#include "snake.h"
#include "display.h"


int main()
{
    printf( "Uroboros, version %d.%d.%d-prerelease\n",
            VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH );

    time_t t;

    unsigned int seed = (unsigned int) time( &t );

    printf( "Your lucky number is %u.\n", seed );

    srand( seed );

    initscr();
    raw();
    noecho();
    cbreak();
    nodelay( stdscr, TRUE );

    keypad( stdscr, 1 );

    start_color();

    // Initialize the color pair for the snake.
    init_pair( 1, COLOR_RED, COLOR_BLACK );

    // Initialize the color pair for the apple.
    init_pair( 2, COLOR_GREEN, COLOR_RED );

    // Initialize the color pair for the golden apple.
    init_pair( 3, COLOR_YELLOW, COLOR_YELLOW );


    // Initialize the snake.
    snake player;

    player.head = (segment*) malloc( sizeof( segment ) );
    player.head->x = 0;
    player.head->y = 0;
    player.tail = player.head;
    player.ghost_x = -1;
    player.ghost_y = -1;
    player.length = 1;


    // Assign coordinates for the apple.
    int apple_x, apple_y;
    do
    {
        apple_x = rand() % 80;
        apple_y = rand() % 24;
    } while( apple_x == 0 && apple_y == 0 );


    signed char direction = INVALID;
    char input = 0;
    char dead = 0;


    do
    {

        // Move the player.
        if( direction != INVALID )
        {
            // Erase the player's tail before moving them.
            mvaddch( player.tail->y, player.tail->x, ' ' );

            move_snake( &player, direction );
        }

        // Check if the player ate an apple.
        if( player.head->x == apple_x && player.head->y == apple_y )
        {
            // Add a segment to the snake.
            grow_snake( &player );
            mvprintw( 0, 0, "Length: %u", player.length );

            // Move the apple.
            do
            {
                apple_x = rand() % 80;
                apple_y = rand() % 24;
            } while( apple_x == player.head->x && apple_y == player.head->y );
        }

        // Check if the player bit themself.
        int head_x = player.head->x, head_y = player.head->y;
        segment *current = player.head->next;
        while( current != NULL )
        {
            if( head_x == current->x && head_y == current->y )
            {
                // Kill the player and terminate the mainloop.
                dead = true;
                break;
            }

            current = current->next;
        }

        if( dead )  break;

        // Draw the apple & the snake.
        draw_apple( apple_y, apple_x );
        draw_snake( player );

#ifdef HILITE_APPLE
        move( apple_y, apple_x );
#endif

        // Get input.
        input = getch();

        switch( input )
        {

            case 'p':
                mvprintw( 0, 0, "Press any key to unpause." );
                getch();
                break;

            case 'h':
                if( direction != RIGHT ) direction = LEFT;
                break;

            case 'j':
                if( direction != UP )    direction = DOWN;
                break;

            case 'k':
                if( direction != DOWN )  direction = UP;
                break;

            case 'l':
                if( direction != LEFT )  direction = RIGHT;
                break;

        } // switch( input )


        // Delay for a given amount of time before continuing.
        clock_t start_time = clock();

        while( clock() < start_time + 100000 );

    } while( !dead && input != 'q' );


    // If the player has died, draw its corpse and wait for a quit.
    if( dead )
    {
        draw_dead_snake( player );

        mvprintw( 0, 0, "Whoops!  You died with %d points.",
                player.length - 1 );

        if( player.length <= 4 )  printw( "  Wow, how did you even do that?" );

        printw( "  Press q to quit." );

        do input = getch(); while( input != 'q' );
    }

    destroy_snake( &player );

    endwin();

    return 0;
}
