// This is public domain software.  Feel free to do whatever you want with it
// so long as you don't hold me liable for any damages - there is no warranty.
//
// If you want to pay me back for it, you can do so by taking ten minutes or
// more out of each day to remind yourself that you are valuable and your life
// is worth living, and treating yourself like someone worth taking care of.
// This software is already free; now free yourself.


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "hiscore.h"


// Writes a score to the given high scores file.  Returns the error code from
// the write.
int write_score( FILE *file, score game )
{

    return fprintf( file, "%u %lu %lu %s\n", game.points, game.time, game.date,
            game.name );

}


// Reads a score from the given high scores file and copies it into `game`.
// Returns 1 on success, `EOF` on end-of-file failure, or 0 for an unknown
// error.
int read_score( FILE *file, score *game )
{

    unsigned int points = 0;

    time_t time = 0, date = 0;

    char *name = 0;

    int num = fscanf( file, "%u %lu %lu %s\n", &points, &time, &date, name );

    // We want to have successfully read in 4 input items, so that's the number
    // to check against.
    if( num == 4 )
    {
        // Assume that space for `game` has already been allocated.  I know
        // that's dangerous or whatever, but this function is used specifically
        // to fill arrays, so it should already be allocated anyway.

        game->points = points;
        game->time = time;
        game->date = date;
        game->name = name;

        // Return a 1 to mark success.
        return 1;
    }
    else
    {

        // Check for an EOF.
        if( feof( file ) )
        {
            return EOF;
        }
        // If there's no EOF, we don't know why the read failed, so return a
        // 0 for generic error.
        else
        {
            return 0;
        }
    }

}


// Compares two given game scores.  Returns -1 if `left` is smaller; +1 if
// `right` is smaller; or 0 if they are equal.
int compare_scores( score left, score right )
{

    // High scores are sorted by points first, then time, then date.
    if( left.points > right.points )
    {
        return -1;
    }
    else if( left.points < right.points )
    {
        return +1;
    }

    if( left.time < right.time )
    {
        return -1;
    }
    else if( left.time > right.time )
    {
        return +1;
    }

    if( left.date < right.date )
    {
        return -1;
    }
    else if( left.date > right.date )
    {
        return +1;
    }

    return 0;

}


// Inserts the given `new_score` into the `scores` list, updating `num_scores`.
void insert_score( score **scores, size_t *num_scores, score new_score )
{

    score new_list[10];

    // The `index` of the `scores` list we're on.
    size_t index = 0;

    // The total `count` of array items assigned so far.
    size_t count = 0;

    // Assign to 1 when the new score has been written so we can skip
    // future comparisons.
    unsigned char wrote = 0;

    for( ; index < *num_scores && count < 10; count++ )
    {

        // If we've already written the new score, we can skip comparisons.
        if( wrote )
        {
            new_list[count] = (*scores)[index];

            // Make sure to advance `index` before continuing.
            index++;
        }
        else
        {
            // For each index in the new array, decide whether to write the new
            // score or the old score.
            int first = compare_scores( new_score, (*scores)[index] );

            // Only write the new score first if it is SMALLER than the old
            // one.  Equal scores (which should be impossible but w/e) will
            // favor the old score.
            if( first < 0 )
            {
                new_list[count] = new_score;

                // Mark that we've written the new score so that we can skip
                // future comparisons.
                wrote = 1;
            }
            else
            {
                new_list[count] = (*scores)[index];

                // Advance `index` before continuing.
                index++;
            }
        }
    }

    // Overwrite the old `scores` list and update `num_scores`.
    *num_scores = count;

    for( index = 0; index < count; index++ )
    {
        (*scores)[index] = new_list[index];
    }

}
