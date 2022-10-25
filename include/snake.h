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


#ifndef INCLUDE_SNAKE_H
# define INCLUDE_SNAKE_H


# include "segment.h"


// The `snake` struct is used to store the snake in a format convenient for
// manipulating it.

typedef struct snake snake;
struct snake
{
    // The number of segments on the snake.
    unsigned int length;

    // The coordinates of the "ghost" segment used when the snake grows.
    int ghost_x, ghost_y;

    // The `head` and `tail` of the snake.
    segment *head, *tail;
};


// Adds a segment to the snake.
void grow_snake( snake *snek );


// Deallocates all memory allocated for the snake.
void destroy_snake( snake *snek );


// Moves the snake in the given direction.
void move_snake( snake *snek, signed char direction );


#endif
