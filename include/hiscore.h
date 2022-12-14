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


#ifndef INCLUDE_HISCORE_H
# define INCLUDE_HISCORE_H


# include <time.h>

# include "rank.h"


// This file describes high scores and the methods by which they are stored.


// The high score format ID, used to verify that high scores have been saved
// in a compatible format.  The ID number should be set to the version number
// that defined the format so that the number is meaningful.
# define HI_SCORE_FILE_FORMAT 0x000200


// This struct describes a single score entered by a player after a game.
typedef struct score score;
struct score
{

    // The number of points scored during the recorded game.
    unsigned int points;

    // The ratio of player snake length to max board size.
    rank_t ratio;

    // The elapsed time of the game that was recorded.
    time_t time;

    // The date that the game was recorded.
    time_t date;

    // The name of the player.
    char name[21];

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


// Inserts the given `new_score` into the `scores` list, updating `num_scores`.
// Returns -1 on failure or the index of the inserted score on success.
int insert_score( score *scores, size_t *num_scores, score new_score );


// Writes the high `scores` to the high scores `file`.  Returns a negative
// error code on failure or 1 on success.
int write_hiscore_file( FILE *file, score *scores, size_t num_scores );


// Reads the high scores `file` and updates the `scores` array and `num_scores`
// counter according to the scores that were found.  Returns a negative error
// value if the file was not in a compatible format or a 0 for an unknown
// error; otherwise, returns 1.
int read_hiscore_file( FILE *file, score *scores, size_t *num_scores );


#endif
