// This is public domain software.  Feel free to do whatever you want with it
// so long as you don't hold me liable for any damages - there is no warranty.
//
// If you want to pay me back for it, you can do so by taking ten minutes or
// more out of each day to remind yourself that you are valuable and your life
// is worth living, and treating yourself like someone worth taking care of.
// This software is already free; now free yourself.


// This file defines functions declared in options.h


#include <stdio.h>
#include <string.h>

#include "curses.h"

#include "globals.h"
#include "options.h"


// Initialize all options to their default values.
void init_options()
{

    move_up      = KEY_UP;
    move_down    = KEY_DOWN;
    move_left    = KEY_LEFT;
    move_right   = KEY_RIGHT;
    speed_up     = '=';
    slow_down    = '-';
#ifdef DEBUG
    debug_grow   = '+';
    debug_shrink = '_';
#endif
    quit_key     = 'q';
    pause_key    = 'p';
    show_version = 'v';
    show_license = 'c';

    display_flags = COLOR;

    hiscore_path = "hiscore";

}


// Attempts to assign a key binding to `target` based on the input `value`.
// Returns a 1 on success or a 0 on failure.
int assign_keybind( int *target, const char *value )
{

    int succ = 0;

    // Generally, we only care about the first character of `value`.  However,
    // as a special case, Uroboros allows arrow key inputs or "SPACE" to
    // indicate the space bar, so it behooves us to check.
    
    // If the input `value` is only one character long, that's a freebie for
    // us.
    if( strlen( value ) == 1 )
    {
        *target = value[0];
        succ = 1;

    }
    // If `value` starts with 'S', it might be the "SPACE" keyword used by
    // Uroboros to indicate the user wants to assign the keybind to the
    // spacebar.
    else if( value[0] == 'S' )
    {

        if( !strcmp( value, "SPACE" ) )
        {

            *target = ' ';
            succ = 1;

        }

    }
    // If `value` starts with 'K', that means that it may be one of the `KEY_*`
    // constants defined by curses, which in our case means it may be one of
    // the arrow keys which Uroboros accepts.
    else if( value[0] == 'K' )
    {

        // Check each of the names in order from shortest to longest.
        if( !strcmp( value, "KEY_UP" ) )
        {

            *target = KEY_UP;
            succ = 1;

        }
        else if( !strcmp( value, "KEY_DOWN" ) )
        {

            *target = KEY_DOWN;
            succ = 1;

        }
        else if( !strcmp( value, "KEY_LEFT" ) )
        {

            *target = KEY_LEFT;
            succ = 1;

        }
        else if( !strcmp( value, "KEY_RIGHT" ) )
        {

            *target = KEY_RIGHT;
            succ = 1;

        }

    } // else if( value[0] == 'K' )

    return succ;

} // int assign_keybind( int*, const char* )
