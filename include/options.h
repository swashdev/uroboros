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


#ifndef INCLUDE_OPTIONS_H
# define INCLUDE_OPTIONS_H


// This file declares functions used to read and interpret options.


// Initialize all options to their default values.
void init_options();

// Attempts to assign a key binding to `target` based on the input `value`.
// Returns a 1 on success or a 0 on failure.
int assign_keybind( int *target, const char *value );

// Reads in options from a file at the given path.  This function will print
// warning messages to stdio if it reads an invalid line from the file.
// Returns 1 if any such invalid lines were found, 0 otherwise.  Returns -1
// if the options file was not found.
int read_options_file( const char *path );


#endif
