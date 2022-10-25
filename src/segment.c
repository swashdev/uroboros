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


#include <stdlib.h>

#include "segment.h"


// Adds a new segment with the given `x` and `y` values to the `current`
// segment.
void add_segment( segment *current, int x, int y )
{
    // Allocate memory for the new segment.
    if( current->next == NULL )
    {
        current->next = (segment*) malloc( sizeof( segment ) );
    }

    current->next->previous = current;

    current = current->next;

    current->x = x;
    current->y = y;
    current->next = NULL;
}


// Recursively frees up memory allocated for all of the segments in the list,
// starting with the `current` one.
void destroy_segment( segment *current )
{
    if( current->next != NULL )
    {
        destroy_segment( current->next );
    }

    free( current );
}
