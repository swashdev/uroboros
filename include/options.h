// This is public domain software.  Feel free to do whatever you want with it
// so long as you don't hold me liable for any damages - there is no warranty.
//
// If you want to pay me back for it, you can do so by taking ten minutes or
// more out of each day to remind yourself that you are valuable and your life
// is worth living, and treating yourself like someone worth taking care of.
// This software is already free; now free yourself.


#ifndef INCLUDE_OPTIONS_H
# define INCLUDE_OPTIONS_H


// This file declares functions used to read and interpret options.


// Initialize all options to their default values.
void init_options();

// Attempts to assign a key binding to `target` based on the input `value`.
// Returns a 1 on success or a 0 on failure.
int assign_keybind( int *target, const char *value );


#endif
