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


#ifndef INCLUDE_GLOBALS_H
# define INCLUDE_GLOBALS_H


// This header file is used for global variables and constants.


# include "curses.h"


// The version number for the program.  An effort is made to follow the
// semantic versioning standard 2.0.0 <https://semver.org/spec/v2.0.0.html>
// Dev builds, indicated by a version number ending with "-dev.%d", represent
// prerelease versions, akin to alphas or betas in programs that have actual
// development teams and production quality.
# define VERSION_MAJOR 0
# define VERSION_MINOR 3
# define VERSION_PATCH 0
# define VERSION_BUILD 3


// The version number expressed as a hexadecimal number, with each of MAJOR,
// MINOR, and PATCH being given two hexadecimal digits.  This is useful for
// concisely outputting the version number to a file or quickly comparing two
// version numbers, but has very little use in user-facing contexts.  Dev build
// numbers are not considered when factoring in this number.
# define VERSION_SQUISHED (VERSION_MAJOR << 16) + (VERSION_MINOR << 8) + \
        VERSION_PATCH


// Enable this flag to build a debug version of the program.  Debug versions
// will give you debug output.
//# define DEBUG


// A standard type for bitmask flags.
typedef unsigned char flag_t;


// Constants used to represent directions.
# define INVALID  0
# define UP      -1
# define DOWN     1
# define LEFT    -2
# define RIGHT    2


// Constants used to represent player status.
# define DEAD    0x1
# define CHEATED 0x2


// The outer boundaries of the terminal.
int max_x;
int max_y;


// Color data.
attr_t color_snake, color_apple, color_gold;

// What symbols are used to represent in-game objects.
char sym_snake, sym_apple, sym_bone;


// Player Options /////////////////////////////////////////////////////////////


// Key bindings.
int move_up, move_down, move_left, move_right,
    speed_up, slow_down,
#ifdef DEBUG
    debug_grow, debug_shrink,
#endif
    quit_key, pause_key,
    show_version, show_license;


// Options relating to the display.
char color;


// Path to the hiscore file.
char *hiscore_path;


#endif
