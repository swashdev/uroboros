Uroboros
========

Uroboros is a pretty simple Snake clone that runs in your computer's terminal.
It is confirmed to run on Linux.  However, previous builds have also been
tested on macOS.

Uroboros is a project I started as part of an effort to build more games by
challenging myself to see what I could build in only a week.  The bulk of the
game's logic was written in only two days (actually one and a half, with the
other half dedicated to troubleshooting my compilers) and much of the rest of
the time so far has been spent smoothing things out.


Play of the Game
----------------

You are a snake.  Your objective is to eat many apples.  Unfortunately, eating
apples makes your tail longer, and if you bite your tail by accident you'll
lose the game, largely because biting your tail is against the rules, but also
because you died.

In this version of Snake, moving off the edge of the screen causes you to wrap
around to the other side, rather than dying.


### Controls

 - Move: Arrow keys
 - Pause: p
 - Quit: q
 - Increase Speed: = (plus key)
 - Decrease Speed: - (minus key)
 - Version: v
 - View License: c


### Customizing

You can personalize your game by editing [options.txt][options].  Instructions
on how to do so are included in that file.

[options]: options.txt


Compiling
---------

Uroboros is a very simple game, structurally, and as such there aren't any
fancy bells or whistles you need to compile it, and you don't have to learn how
to use makefiles.


### Dependencies

The one thing that Uroboros needs is a curses implementation.  On Linux and
macOS, ncurses has been used successfully, and ncurses is readily available for
POSIX systems in general via package managers.

On Windows, PDCurses has been used, which requires a bit more futzing with
because Windows doesn't like to make things easy for you, but you should be
able to figure it out with some simple Internet searches.


### Compiling with GCC

Uroboros can be compiled via a single gcc command like so:
```
gcc -I include src/options.c src/segment.c src/snake.c src/display.c src/rank.c src/hiscore.c src/main.c -o uroboros -lncurses
```

For Windows I've been able to successfully use MinGW, although I've found that
cross-compiling from Linux is slightly easier if you know how to do it, because
third-party 32-bit compliers are becoming increasingly difficult to find and
I'm not sure PDCurses even supports 64-bit systems.  Your mileage may vary.


###  Debug Builds

To make a debug build, go into `include/globals.h` and enable the `DEBUG` flag
by un-commenting the line it's defined on.


License
-------

Uroboros has been voluntarily [released into the public domain](UNLICENSE) and
I retain no copyright, patents, or other interests in the software.  You can
compile it, modify it, share it with your friends, sell it for profit, launch
it into space, tattoo it on your forearm, or even release it under the GPL for
all I care.  Go bananas.  Just bear in mind that Uroboros is released with
**absolutely no warranty** and that I will not be held liable for any damages
under any circumstances.
