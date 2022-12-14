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


// This file defines functions declared in options.h


#include <stdio.h>
#include <stdlib.h>
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

    color = 1;

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


// Reads in options from a file at the given path.  This function will print
// warning messages to stdio if it reads an invalid line from the file.
// Returns a positive error count if any such warnings were printed, 0
// otherwise.  Returns -1 if the options file was not found.
int read_options_file( const char *path )
{

    int err = 0;

    FILE *options = fopen( path, "r" );

    // Abort if the file is not found and return -1.
    if( options == NULL )
    {

        return -1;

    }

    // Read the file.
    char line[81];
    char key[13];
    char value[61];
    line[80]  = '\0';
    key[12]   = '\0';
    value[60] = '\0';
    size_t count = 0;
    int pair;
    size_t length;
    int keybind;
    char check_keybind;
    while( !feof( options ) )
    {

        line[0] = '\0';
        check_keybind = 0;
        count = count + 1;

        // Read up to 80 characters of the given line.
        fgets( line, 80, options );

        // If the line is blank or starts with a '#', skip it.
        length = strlen( line );
        if( length <= 1 || line[0] == '#' )
        {

            continue;

        }

        // Non-comment lines follow a predictable format, so we can use
        // `sscanf` to get key/value pairs for each option.
        pair = sscanf( line, "%s = %s", key, value );

        // `pair` should evaluate to 2 if we successfully got a key/value
        // pair.  If not, print a warning message and skip this line.
        if( pair != 2 )
        {

            printf( "WARNING: Could not read line %lu in %s:\n%s\n",
                    count, path, line );

            err = err + 1;

            continue;

        }

        // Now we check each of the possible name values that could have been
        // read into `key` and assign a value appropriately.
        
        // Key bindings 


        if( !strcmp( key, "move_up" ) )
        {

            keybind = assign_keybind( &move_up, value );
            check_keybind = 1;

        }
        else if( !strcmp( key, "move_down" ) )
        {

            keybind = assign_keybind( &move_down, value );
            check_keybind = 1;

        }
        else if( !strcmp( key, "move_left" ) )
        {

            keybind = assign_keybind( &move_left, value );
            check_keybind = 1;

        }
        else if( !strcmp( key, "move_right" ) )
        {

            keybind = assign_keybind( &move_right, value );
            check_keybind = 1;

        }
        else if( !strcmp( key, "speed_up" ) )
        {
            
            keybind = assign_keybind( &speed_up, value );
            check_keybind = 1;

        }
        else if( !strcmp( key, "slow_down" ) )
        {

            keybind = assign_keybind( &slow_down, value );
            check_keybind = 1;

        }
        else if( !strcmp( key, "pause_key" ) )
        {

            keybind = assign_keybind( &pause_key, value );
            check_keybind = 1;

        }
        else if( !strcmp( key, "quit_key" ) )
        {

            keybind = assign_keybind( &quit_key, value );
            check_keybind = 1;

        }
        else if( !strcmp( key, "show_version" ) )
        {

            keybind = assign_keybind( &show_version, value );
            check_keybind = 1;

        }
        else if( !strcmp( key, "show_license" )
              || !strcmp( key, "show_licence" ) )
        {

            keybind = assign_keybind( &show_license, value );
            check_keybind = 1;

        }
        // Debug key bindings don't trigger a warning on non-debug builds, but
        // also don't assign any values.
        else if( !strcmp( key, "debug_grow" ) )
        {

#ifndef DEBUG
            continue;
#else
            keybind = assign_keybind( &debug_grow, value );
            check_keybind = 1;
#endif

        }
        else if( !strcmp( key, "debug_shrink" ) )
        {

#ifndef DEBUG
            continue;
#else
            keybind = assign_keybind( &debug_shrink, value );
            check_keybind = 1;
#endif

        }

        // If a keybind option was read, check if it was successful.
        if( check_keybind )
        {

            // If the keybind was unsuccessful, print a warning.
            if( !keybind )
            {

                printf( "WARNING: Invalid keybind at line %lu in %s:\n%s\n",
                        count, path, line );
                err = err + 1;

            }

            // Either way, we are finished and can move on to the next line.
            continue;

        }
        else if( !strcmp( key, "color" ) || !strcmp( key, "colour" ) )
        {

            if( value[0] == 'y' || value[0] == 'Y' )
            {

                color = 1;

            }
            else if( value[0] == 'n' || value[0] == 'N' )
            {

                color = 0;

            }
            else
            {

                printf( "WARNING: Invalid boolean option at line %lu in %s:",
                        count, path );
                printf( "\n%s\n", line );
                err = err + 1;

            }

            continue;

        }

        // If none of the above option checks have passed, the line is invalid
        // and we need to nag the user.
        else
        {

            printf( "WARNNIG: Invalid or unknown key/value pair at line %lu",
                    count );
            printf( " in %s:\n%s\n", path, line );
            err = err + 1;

        }

    } // while( !eof( options ) )

    fclose( options );

#ifdef DEBUG
    puts( "DEBUG: Reading options file resulted in assigned options:" );

# define show_keybind( name, var ) printf( "%s:\t%d/%c\n", name, var, var )
# define show_boolean( name, val, mask ) printf( "%s:\t%c\n", name, \
        mask & val ? 'Y' : 'N' )

    show_keybind( "move_up", move_up );
    show_keybind( "move_down", move_down );
    show_keybind( "move_left", move_left );
    show_keybind( "move_right", move_right );
    show_keybind( "speed_up", speed_up );
    show_keybind( "slow_down", slow_down );
    show_keybind( "debug_grow", debug_grow );
    show_keybind( "debug_shrink", debug_shrink );
    show_keybind( "pause_key", pause_key );
    show_keybind( "quit_key", quit_key );
    show_keybind( "show_version", show_version );
    show_keybind( "show_license", show_license );
    show_boolean( "color", 1, color );

# undef show_keybind
# undef show_boolean

#endif

    return err;

} // int read_options_file( const char* )
