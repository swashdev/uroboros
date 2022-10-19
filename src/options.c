// This is public domain software.  Feel free to do whatever you want with it
// so long as you don't hold me liable for any damages - there is no warranty.
//
// If you want to pay me back for it, you can do so by taking ten minutes or
// more out of each day to remind yourself that you are valuable and your life
// is worth living, and treating yourself like someone worth taking care of.
// This software is already free; now free yourself.


// This file defines functions declared in options.h


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
