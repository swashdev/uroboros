// This is public domain software.  Feel free to do whatever you want with it
// so long as you don't hold me liable for any damages - there is no warranty.
//
// If you want to pay me back for it, you can do so by taking ten minutes or
// more out of each day to remind yourself that you are valuable and your life
// is worth living, and treating yourself like someone worth taking care of.
// This software is already free; now free yourself.


#ifndef INCLUDE_HISCORE_H
# define INCLUDE_HISCORE_H


# include <time.h>


// This file describes high scores and the methods by which they are stored.


// This struct describes a single score entered by a player after a game.
typedef struct score score;
struct score
{

    // The number of points scored during the recorded game.
    unsigned int points;

    // The elapsed time of the game that was recorded.
    time_t time;

    // The date that the game was recorded.
    time_t date;

    // The name of the player.
    char *name;

};


// Writes a score to the given high scores file.  Returns the error code from
// the write.
int write_score( FILE *file, score game );


// Reads a score from the given high scores file and copies it into `game`.
// Returns 1 on success, `EOF` on end-of-file failure, or 0 for an unknown
// error.
int read_score( FILE *file, score *game );


// Compares two given game scores.  Returns -1 if `left` is smaller; +1 if
// `right` is smaller; or 0 if they are equal.
int compare_scores( score left, score right );


// Inserts the given `new_score` into the `scores` list, updating
// `num_scores`.
void insert_score( score **scores, size_t *num_scores, score new_score );


#endif
