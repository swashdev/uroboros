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


#ifndef INCLUDE_RANK_H
# define INCLUDE_RANK_H


// This file defines the various "ranks" and how to calculate them.


typedef float rank_t;


// Calculates the player's rank based on the input `length` and `max`.
rank_t get_rank( unsigned int length, unsigned int max );


// Copies a string appropriate to the given `rank` into `str`.
void get_rank_name( char **str, rank_t rank );


// Each rank is a floating-point value.  Scores >= that value qualify for the
// rank.  Uroboros is reserved only for perfect scores.  Negative values are
// special-cased.
# define DIRT         0.000f
# define WORM         0.010f
# define SNAKE        0.025f
# define RATTLER      0.050f
# define PYTHON       0.075f
# define KING         0.100f
# define SNALLYGASTER 0.250f
# define WYRM         0.500f
# define QUETZALCOATL 0.750f
# define NIDHOGG      0.900f
# define ATUM         0.950f
# define UROBOROS     1.000f


#endif
