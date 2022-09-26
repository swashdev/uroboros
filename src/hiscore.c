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

#include "globals.h"
#include "hiscore.h"


// Writes a score to the given high scores file.  Returns the error code from
// the write.
int write_score( FILE *file, score game )
{

    return fprintf( file, "%u %f %lu %lu %s\n", game.points, game.ratio,
            game.time, game.date, game.name );

}


// Reads a score from the given high scores file and copies it into `game`.
// Returns 1 on success, `EOF` on end-of-file failure, or 0 for an unknown
// error.
int read_score( FILE *file, score *game )
{

    unsigned int points = 0;

    rank_t ratio = 0.000f;

    time_t time = 0, date = 0;

    int num = fscanf( file, "%u %f %lu %lu ", &points, &ratio, &time,
            &date );

    // We want to have successfully read in 4 input items, so that's the number
    // to check against.
    if( num == 4 )
    {
        // Assume that space for `game` has already been allocated.  I know
        // that's dangerous or whatever, but this function is used specifically
        // to fill arrays, so it should already be allocated anyway.

        game->points = points;
        game->ratio = ratio;
        game->time = time;
        game->date = date;

        // Now we need to read in the player's name  We'll read in up to 20
        // characters, terminating either on newline or when that limit is
        // reached.  Either way, the read head will be advanced until either a
        // newline or EOF is reached.
        int letter;
        size_t index = 0;
        do
        {

            letter = fgetc( file );

            if( index < 20 && letter != '\n' && letter != EOF )
            {
                game->name[index] = (char) letter;
                index += 1;
            }

        } while( letter != '\n' && letter != EOF );

        // Terminate the player's name with a null character.
        game->name[index] = '\0';

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

    // High scores are sorted by points first, then ratio, then time, then
    // date.
    if( left.points > right.points )
    {
        return -1;
    }
    else if( left.points < right.points )
    {
        return +1;
    }

    if( left.ratio > right.ratio )
    {
        return -1;
    }
    else if( left.ratio < right.ratio )
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
// Returns -1 on failure or the index of the inserted score on success.
int insert_score( score *scores, size_t *num_scores, score new_score )
{

    score new_list[10];

    // The `index` of the `scores` list we're on.
    size_t index = 0;

    // The total `count` of array items assigned so far.
    size_t count = 0;

    // Assign to 1 when the new score has been written so we can skip
    // future comparisons.
    unsigned char wrote = 0;

    // This value will be assigned to the index of the inserted score, if
    // insertion is successful.
    int new_index = -1;

    for( ; index < *num_scores && count < 10; count++ )
    {

        // If we've already written the new score, we can skip comparisons.
        if( wrote )
        {
            new_list[count] = scores[index];

            // Make sure to advance `index` before continuing.
            index++;
        }
        else
        {
            // For each index in the new array, decide whether to write the new
            // score or the old score.
            int first = compare_scores( new_score, scores[index] );

            // Only write the new score first if it is SMALLER than the old
            // one.  Equal scores (which should be impossible but w/e) will
            // favor the old score.
            if( first < 0 )
            {
                new_list[count] = new_score;

                new_index = (int) count;

                // Mark that we've written the new score so that we can skip
                // future comparisons.
                wrote = 1;
            }
            else
            {
                new_list[count] = scores[index];

                // Advance `index` before continuing.
                index++;
            }
        }
    }

    // If the player's score wasn't written, but the list is short enough to
    // accomodate one more score, insert it now.
    if( !wrote && *num_scores < 10 )
    {
        new_list[count] = new_score;
        new_index = (int) count;
        count += 1;
    }

    // Overwrite the old `scores` list and update `num_scores`.
    *num_scores = count;

    for( index = 0; index < count; index++ )
    {
        scores[index] = new_list[index];
    }

    return new_index;

}


// Writes the high `scores` to the high scores `file`.  Returns a negative
// error code on failure or 1 on success.
int write_hiscore_file( FILE *file, score *scores, size_t num_scores )
{

    // Begin by writing the file format ID number.
    fprintf( file, "%06x\n", HI_SCORE_FILE_FORMAT );

    // Error codes from writes are stored here.
    int err;

    // Write each score one at a time.
    for( size_t index = 0; index < num_scores && index < 10; index++ )
    {
        err = write_score( file, scores[index] );

        if( err < 0 )
        {
            return err;
        }
    }

    return 1;

}


// Reads the high scores `file` and updates the `scores` array and `num_scores`
// counter according to the scores that were found.  Returns a negative error
// value if the file was not in a compatible format or a 0 for an unknown
// error; otherwise, returns 1.
int read_hiscore_file( FILE *file, score *scores, size_t *num_scores )
{

    int err;

    // Begin by reading the file format ID number so it can be checked.
    unsigned int format;
    err = fscanf( file, "%06x\n", &format );

    if( err < 1 )  return 0;

    // Check the file format ID.
#if VERSION_MAJOR > 1
    if( VERSION_MAJOR != ((format & 0xff0000) >> 16) )
#else
    if( VERSION_MAJOR < ((format & 0xff0000) >> 16) )
#endif
    {
        // If the ID indicates an incompatible format, return an error code.
        return -1;
    }

    *num_scores = 0;
    err = 1;
    // Read each of the high scores in one at a time, checking the error code
    // each time.
    while( err >= 1 && *num_scores < 10 )
    {
        err = read_score( file, &scores[*num_scores] );

        // On success, increment the counter.
        if( err == 1 )
        {
            *num_scores += 1;
        }
    }

    // If we got an EOF, that's an acceptable error and we can consider that a
    // success.  Otherwise, return an error code.
    if( err > 0 || err == EOF )
    {
        return 1;
    }
    else
    {
        return 0;
    }

}
