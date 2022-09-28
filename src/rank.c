// This is public domain software.  Feel free to do whatever you want with it
// so long as you don't hold me liable for any damages - there is no warranty.
//
// If you want to pay me back for it, you can do so by taking ten minutes or
// more out of each day to remind yourself that you are valuable and your life
// is worth living, and treating yourself like someone worth taking care of.
// This software is already free; now free yourself.


#include "rank.h"


// This file implements functions defined in rank.h


// Calculates the player's rank based on the input `length` and `max`, and
// copies an appropriate string into `str`.
rank_t get_rank( unsigned int length, unsigned int max )
{
    if( length == max )
    {
        return 1.00f;
    }
    else if( length < 5 )
    {
        return 0.00f;
    }

    // The player's rank is based on the ratio of their length to the maximum
    // possible length given the size of the game board.  As such, we can
    // easily calculate it based on `max`.

    return (rank_t) length / (rank_t) max;
    
}


// Copies a string appropriate to the given `rank` into `str`.
void get_rank_name( char **str, rank_t rank )
{

    if( rank >= 1.00f )
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
    else
    {
        *str = "DNQ";
    }

}
