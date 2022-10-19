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

#include "curses.h"

#include "globals.h"
#include "options.h"
#include "segment.h"
#include "snake.h"
#include "display.h"
#include "rank.h"
#include "hiscore.h"


int main()
{

    // Get options.
    init_options();

#ifdef DEBUG
    printf( "DEBUG: Reading options from %s\n", "options.txt" );
#endif

    int warnings = read_options_file( "options.txt" );

    if( warnings < 0 )
    {

        printf( "Couldn't read options file at %s\n", "options.txt" );
        perror( "Got error:" );

    }
    else if( warnings > 0 )
    {

        printf( "Got %d warnings while reading options from %s\n",
                warnings, "options.txt" );

    }

    if( warnings != 0 )
    {

        int cont = '\n';

        do
        {

            while( cont != '\n' )  cont = getchar();
            puts( "Continue? [y/n/q]" );
            cont = getchar();

        } while( cont != 'n' && cont != 'y' && cont != 'q'
              && cont != 'N' && cont != 'Y' && cont != 'Q' );

        if( cont != 'y' && cont != 'Y' )
        {

            return 0;

        }

    }

    initscr();
    raw();
    noecho();
    cbreak();
    nodelay( stdscr, TRUE );

    keypad( stdscr, 1 );


    if( display_flags & COLOR )
    {

        start_color();

        // Initialize the color pair for the snake.
        init_pair( 1, COLOR_GREEN, COLOR_BLACK );

        // Initialize the color pair for the apple.
        init_pair( 2, COLOR_GREEN, COLOR_RED );

        // Initialize the color pair for the golden apple.
        init_pair( 3, COLOR_YELLOW, COLOR_YELLOW );

    }


    // Initialize display data.
    init_symbols();


    // Initialize RNG.
    unsigned int seed = (unsigned int) time( NULL );

#ifdef DEBUG
    mvprintw( 2, 0, "Your lucky number is %u", seed );
#endif

    srand( seed );


    // Initialize the snake.
    snake player;


    // Get the outer boundaries of the terminal.
    getmaxyx( stdscr, max_y, max_x );
#ifdef DEBUG
    mvprintw( 0, 0, "Got screen size %03d, %03d", max_x, max_y );
#endif


    player.head = (segment*) malloc( sizeof( segment ) );
    player.head->x = max_x / 2;
    player.head->y = max_y / 2;
    player.tail = player.head;
    player.ghost_x = -1;
    player.ghost_y = -1;
    player.length = 1;


    // Print the version number.
    print_version_number( max_y - 1, 0 );


    // Assign coordinates for the apple.
    // The apple's initial Y coordinate is fudged to never be on the first
    // line or on the same line as the player, so that its "Eat these" message
    // doesn't interfere with the other helpful information.
    int apple_x, apple_y;
    do
    {
        apple_x = rand() % max_x;
        apple_y = 1 + (rand() % (max_y - 2));
    } while( apple_y == player.head->y );

#ifdef DEBUG
    mvprintw( 1, 0, "Apple spawned at coords %03d, %03d", apple_x, apple_y );
#endif


    // Display helpful information.
#ifndef DEBUG
    mvprintw( 0, 0, "Arrow keys, wasd, or hjkl to move.  " );
    printw( "Press p to pause or q to quit." );
#endif
    mvprintw( player.head->y, player.head->x + 2, "<- This is you" );
    if( apple_x < (max_x - 13) )
    {
        mvprintw( apple_y, apple_x + 2, "<- Eat these" );
    }
    else
    {
        mvprintw( apple_y, apple_x - 13, "Eat these ->" );
    }


    signed char direction = INVALID;
    int input = 0;
    flag_t status = 0;
    clock_t fps = 10;
    clock_t delay = CLOCKS_PER_SEC / fps;
    clock_t frame_time;


    // Display the player & apple and wait for user input.
    draw_snake( player );
    draw_apple( apple_y, apple_x, 1 );
    move( apple_y, apple_x );
    do{ input = getch(); } while( input == ERR );

    // Clear the unnecessary text.
    clear();


    // Start the timer.
    time_t start_time = time( NULL );


    do
    {

        frame_time = clock();

#ifdef DEBUG
        if( input != ERR )
        {
            mvprintw( max_y - 1, 0, "%-15s", keyname( input ) );
        }
#endif

        // Check input.
        if( input == move_left )
        {

            if( direction != RIGHT ) direction = LEFT;

        }

        else if( input == move_down )
        {

            if( direction != UP )    direction = DOWN;

        }

        else if( input == move_up )
        {

            if( direction != DOWN )  direction = UP;
        }

        else if( input == move_right )
        {

            if( direction != LEFT )  direction = RIGHT;
        }

        // Decrease the game speed.
        else if( input == slow_down )
        {

            if( fps > 1 )
            {

                fps--;
                delay = CLOCKS_PER_SEC / fps;
#ifdef DEBUG
                mvprintw( 0, 0, "Speed: %u", fps );
#endif

            }
            else
            {

                flash();
#ifdef DEBUG
                attron( A_REVERSE );
                mvprintw( 0, 0, "Speed: %u", fps );
                attroff( A_REVERSE );
#endif

            }

        } // else if( input == slow_down )

        // Increase the game speed.
        if( input == speed_up )
        {

            if( fps < CLOCKS_PER_SEC )
            {

                fps++;
                delay = CLOCKS_PER_SEC / fps;
#ifdef DEBUG
                mvprintw( 0, 0, "Speed: %u", fps );
#endif

            }
            else
            {

                flash();
#ifdef DEBUG
                attron( A_REVERSE );
                mvprintw( 0, 0, "Speed: %u", fps );
                attroff( A_REVERSE );
#endif
            }

        } // else if( input == speed_up )

#ifdef DEBUG

        // Grow the player.
        else if( input == debug_grow )
        {

            status = status | CHEATED;
            grow_snake( &player );
            mvprintw( 0, 0, "Length: %u", player.length );

        }

        // Shrink the player.
        else if( input == debug_shrink )
        {

            status = status | CHEATED;
            if( player.length > 1 )
            {
                segment *old_tail = player.tail;
                mvaddch( old_tail->y, old_tail->x, ' ' );
                player.tail = player.tail->previous;
                player.tail->next = NULL;
                destroy_segment( old_tail );
                player.length--;
                mvprintw( 0, 0, "Length: %u", player.length );
            }
            else
            {
                status = status | DEAD;
            }

        }

#endif

        // Pause the game.
        else if( input == pause_key )
        {

pause_screen:

            attron( A_REVERSE );
            mvprintw( max_y / 2, (max_x / 2) - 12,
                        "Press any key to unpause." );
            attroff( A_REVERSE );
            move( apple_y, apple_x );

            while( getch() == ERR );

            mvprintw( max_y / 2, (max_x / 2) - 12,
                        "                         " );
            draw_snake( player );
            draw_apple( apple_y, apple_x, player.length );

        }

        else if( input ==  show_version )
        {

            print_version_number( max_y - 1, 0 );

        }

        else if( input == show_license )
        {

            print_version_number( max_y - 1, 0 );
            move( apple_y, apple_x );
            display_license_agreement();

            // Redraw the screen.
            clear();
            draw_snake( player );
            draw_apple( apple_y, apple_x, player.length );

            // Pause the screen to give the player a chance to get their
            // bearings.
            goto pause_screen;

        }


        // Move the player.
        if( direction != INVALID )
        {
            move_snake( &player, direction );
        }

        // Check if the player ate an apple.
        if( player.head->x == apple_x && player.head->y == apple_y )
        {
            // Add a segment to the snake.
            grow_snake( &player );
#ifdef DEBUG
            mvprintw( 0, 0, "Length: %u, ratio: %.3f",
                    player.length, get_rank( player.length, (max_x * max_y) ) );
#endif

            // Move the apple.
            do
            {
                apple_x = rand() % max_x;
                apple_y = rand() % max_y;

#ifdef DEBUG
                mvprintw( 1, 0, "Apple spawned at coords %03d, %03d",
                        apple_x, apple_y );
#endif
            } while( apple_x == player.head->x && apple_y == player.head->y );
        }
        // If the player did NOT eat an apple, erase the spot where the new
        // segment would have been.
        else
        {
            mvaddch( player.ghost_y, player.ghost_x, ' ' );
        }

        // Check if the player bit themself.
        int head_x = player.head->x, head_y = player.head->y;
        segment *current = player.head->next;
        while( current != NULL )
        {
            if( head_x == current->x && head_y == current->y )
            {
                // Kill the player and terminate the mainloop.
                status = status | DEAD;
                break;
            }

            current = current->next;
        }

        if( status & DEAD )  break;

        // Draw the apple & the snake.
        draw_apple( apple_y, apple_x, player.length );
        
        attron( color_snake );
        mvaddch( player.head->y, player.head->x, sym_snake );
        attroff( color_snake );

        move( apple_y, apple_x );

        // Get input.
        input = getch();


        // Delay for a given amount of time before continuing.
        while( clock() < frame_time + delay );

    } while( !(status & DEAD) && input != 'q' );


    // Stop the timer.
    time_t end_time = time( NULL );

    // Flush user input.
    flushinp();


    // If the player has died, draw its corpse and wait for a quit.
    if( status & DEAD )
    {
        draw_dead_snake( player );

        // Make sure to refresh the screen so that these elements don't get
        // drawn over the high scores list.
        refresh();

    }

    unsigned int final_length = player.length;
    unsigned int points = final_length > 0 ? final_length - 1 : 0;

    destroy_snake( &player );

    // Check the high scores file.
    if( status & DEAD )
    {
        score game;
        game.points = points;
        game.ratio = get_rank( final_length, (unsigned int) (max_y * max_x) );
        game.time = end_time - start_time;
        game.date = end_time;

        // For now, give the player a placeholder name.
        game.name[0] = '\0';

        score *scores = (score*) malloc( 10 * sizeof( score ) );
        size_t num_scores = 0;
        int row = -1;

        // Open the hiscore file for reading.
        FILE *hiscore = fopen( hiscore_path, "r" );

        // If the hiscore file wasn't read, our job has been made very easy.
        if( hiscore == NULL )
        {
            scores[0] = game;
            num_scores = 1;
            row = 0;
        }
        else
        {
            // Read the hiscore file.
            int err = read_hiscore_file( hiscore, scores, &num_scores );

            // We can close the file immediately.
            fclose( hiscore );

            // Try to add the player's current score.
            // Unless they cheated.
            if( !(status & CHEATED) )
            {
                row = insert_score( scores, &num_scores, game );
            }
        }


        if( num_scores > 0 )
        {

            // Create a window to store the high scores in.
            // NOTE: for reasons which will forever baffle me, the game doesn't
            // place the window at the correct y coordinate unless you store it
            // in a variable first, resulting in the window being half-buried
            // beneath the boundaries of the displayable window.
            int height = 8 + (int) num_scores, width = 59;
            WINDOW *w = centered_window( height, width );
            box( w, 0, 0 );
            mvwprintw( w, 1, 2, "You died with %d points.", game.points );
            if( game.points <= 4 )
            {
                wprintw( w, "  Wow, how did you even do that?" );
            }

            // Display the high scores list.
            mvwprintw( w, 4, 2,  "No. Name                 Points   Time" );
            wprintw( w, "     Rank" );

            char *rank;

            for( size_t index = 0; index < num_scores; index++ )
            {
                score current = scores[index];
                get_rank_name( &rank, current.ratio );

                mvwprintw( w, 5 + (int) index, 2, "%2lu) %-20s %-8u %-8lu %s",
                        index + 1,
                        current.name, current.points, current.time, rank );
            }

            // If the player made the high scores list, get their name.
            if( row >= 0 )
            {

                char name[21];

                mvwprintw( w, 2, 2, "You made the top ten!  " );
                wprintw( w, "Please, enter your name!" );
                wrefresh( w );
                echo();
                mvwgetstr( w, 5 + row, 6, name );
                noecho();

                // If the player did not enter a name, give them a placeholder.
                size_t letter;
                if( name[0] == '\0' )
                {

                    for( letter = 0; letter < 4; letter++ )
                    {
                        scores[row].name[letter] = "anon"[letter];
                    }

                }
                else
                {

                    for( letter = 0; letter < 20 && name[letter] != '\0';
                            letter++ )
                    {
                        scores[row].name[letter] = name[letter];
                    }

                }

                scores[row].name[letter] = '\0';

#ifdef __WIN32
                // For Windows builds, re-output the high score data since
                // the Windows terminal likes to clear text data on the line
                // following the name input.
                get_rank_name( &rank, scores[row].ratio );
                mvwprintw( w, 5 + row, 27, "%-8u %-8lu %s",
                        scores[row].points, scores[row].time, rank );
                box( w, 0, 0 );
#endif

            }
            else
            {

                // If the player cheated, admonish them.
                if( status & CHEATED )
                {
                    mvwprintw( w, 2, 2, "Sorry, cheaters never prosper." );
                }
                else
                {
                    mvwprintw( w, 2, 2, "Sorry, looks like you didn't make " );
                    wprintw( w, "the top ten." );
                }

            }

            mvwprintw( w, 6 + (int) num_scores, 2, "Press q to quit." );
            wmove( w, 6 + (int) num_scores, 8 );
            wrefresh( w );

            while( getch() != 'q' );

            delwin( w );

        }

        // If the player made the high scores list, we have to write it anew.
        if( row >= 0 )
        {
            hiscore = fopen( hiscore_path, "w" );

            write_hiscore_file( hiscore, scores, num_scores );

            fclose( hiscore );
        }

        free( scores );

    } // if( status & DEAD )

    // Stop curses.
    echo();
    endwin();

    return 0;
}
