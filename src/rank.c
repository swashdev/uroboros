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


#include "rank.h"


// This file implements functions defined in rank.h


// Calculates the player's rank based on the input `length` and `max`, and
// copies an appropriate string into `str`.
rank_t get_rank( unsigned int length, unsigned int max )
{
    // Return 1.000f (Uroboros) for a perfect score.
    if( length == max )
    {
        return 1.00f;
    }
    // Return -1.000f (Glycon) for an impossible score.
    else if( length < 5 || length > max )
    {
        return -1.00f;
    }

    // The player's rank is based on the ratio of their length to the maximum
    // possible length given the size of the game board.  As such, we can
    // easily calculate it based on `max`.

    return (rank_t) length / (rank_t) max;
    
}


// Copies a string appropriate to the given `rank` into `str`.
void get_rank_name( char **str, rank_t rank )
{

    if( rank > UROBOROS || rank < DIRT )
    {
        *str = "Glycon";
    }
    else if( rank == UROBOROS )
    {
        *str = "Uroboros";
    }
    else if( rank >= ATUM )
    {
        *str = "Atum";
    }
    else if( rank >= NIDHOGG )
    {
        *str = "Nidhogg";
    }
    else if( rank >= QUETZALCOATL )
    {
        *str = "Quetzalcoatl";
    }
    else if( rank >= WYRM )
    {
        *str = "Wyrm";
    }
    else if( rank >= SNALLYGASTER )
    {
        *str = "Snallygaster";
    }
    else if( rank >= KING )
    {
        *str = "King Cobra";
    }
    else if( rank >= PYTHON )
    {
        *str = "Python";
    }
    else if( rank >= RATTLER )
    {
        *str = "Rattlesnake";
    }
    else if( rank >= SNAKE )
    {
        *str = "Snake";
    }
    else if( rank >= WORM )
    {
        *str = "Worm";
    }
    else if( rank >= DIRT )
    {
        *str = "Dirt";
    }

}
