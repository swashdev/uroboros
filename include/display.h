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


#ifndef INCLUDE_DISPLAY_H
# define INCLUDE_DISPLAY_H


// This header file declares functions related to display code.


# include "curses.h"

# include "globals.h"
# include "snake.h"


// Creates a curses window that's centered on the screen.
#define centered_window( height, width ) \
    newwin( height, width, (max_y - height) / 2, (max_x - width) / 2 )


// Initializes color & symbol data.
void init_symbols();


// Draws the snake.
void draw_snake( snake snek );


// Draws the snake but dead.
void draw_dead_snake( snake snek );


// Draws the apple.
void draw_apple( int y, int x, unsigned int count );


// Prints the version number.
void print_version_number( int y, int x );


// Prints the license agreement in a separate window.
void display_license_agreement();


#endif
