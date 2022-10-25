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


// The segments of the snake are stored in a linked list.  Each segment stores
// its own coordinates to make it easier to move them independently.


#ifndef INCLUDE_SEGMENT_H
# define INCLUDE_SEGMENT_H


typedef struct segment segment;
struct segment
{
    int x, y;

    segment *next, *previous;
};


// Adds a new segment with the given `x` and `y` values to the `current`
// segment.
void add_segment( segment *current, int x, int y );


// Recursively frees up memory allocated for all of the segments in the list,
// starting with the `current` one.
void destroy_segment( segment *current );


#endif
