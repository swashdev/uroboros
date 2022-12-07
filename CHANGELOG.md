# Changelog

This file records the concise(-ish) history of the Uroboros project.

The format of this file is based on the
[Keep a Changelog 1.0.0](https://keepachangelog.com/en/1.0.0/) convention.

An effort has been made for this project to follow the
[Semantic Versioning 2.0.0](https://semver.org/spec/v2.0.0) version numbering
standard.  Prerelease versions of Uroboros are referred to as "dev builds" and
indicated by a "-dev" suffix followed by a number.  Dev builds are generally
not documented in this file unless special circumstances require it.


## [Unreleased]

### Fixed

- Lines read in from the options file are now reset after each line read, to
  prevent assigning options twice under certain circumstances.

### Code Changes

- Strings used when reading in the options file are now statically allocated
  rather than being dynamically allocated at runtime.  They should also use
  less memory this way.


## [0.3.0-dev.2] - 2022-12-03

### Notes

- In order to protect users who are subject to tyrannical governments, the
  license agreement has been changed from the previous informal license to the
  Unlicense.

### Added

- Certain program settings, such as key bindings and display settings, can now
  be set by the user in an options file, included with Uroboros.  The game no
  longer needs to be recompiled in order to be reconfigured.

- If the player's terminal is shorter than the height of the license agreement
  disclosure window, the window can now be scrolled up and down.

### Fixed

- The message mocking people who die with low scores now appropriately displays
  whenever the player's score is impossibly low, not just when it's under 4
  points.

### Code Changes

- A new variable type `flag_t` will now be used for bitmask flags.

- Player status is now stored in a `flag_t` named `status` (originally named
  `dead`) and now uses the named constants `DEAD` and `CHEATED` to determine
  the respective player statuses.


## [0.2.2] - 2022-10-18

### Added

- The game now displays a message on the high scores table if it detects
  cheating.

- Debug builds now have a small message informing you of the identity of a key
  that has been pressed.

### Changed

- The version number is now always displayed when the game is started, rather
  than only being displayed on debug or prerelease versions.

- The player's score is now displayed with the high scores list, rather than
  separately from it.

### Fixed

- On Windows, the player's score data is output a second time after entering
  their name, to fix a problem introduced by the Windows terminal clearing all
  text data after the name input.

- The high scores list is now output even if the player cheated.

- User input is now flushed before trying to enter a player name.


## [0.2.1] - 2022-10-13

### Added

- An in-game high scores window will now be displayed, rather than outputting
  the high scores to the terminal after the game closes.

### Changed

- Player names are no longer stored with a bunch of dots in the high scores
  file.

- The helpful text is now cleared off of the screen when the game begins.

### Fixed

- The terminal will no longer refuse to echo input after quitting the game.
  I still don't know why that happened, but it's fixed now.

- The first apple will no longer spawn on the same line as the version number,
  to prevent the "Eat these" message from interfering with the version number
  and vice-versa.

- The timer now doesn't start until the player presses a key, so they can wait
  for as long as they want to start playing without their high score being
  affected.


## [0.2.0] - 2022-10-13

### Added

- High scores!  Qualifying players can now add their name to a "top 10" list
  that they can use to gloat to other players!

- Debug output will now include the player's ratio along with their length.

### Changed

- The license disclosure window is now centered.


## [0.1.0] - 2022-09-19

### Added

- The game can now be compiled without color if desired.

- The player can now increase or decrease the game's speed on-the-fly with the
  \- and + keys.

- On debug builds, the player can now increase or decrease the size of the
  snake by holding shift while pressing the - or + keys.

### Changed

- The cursor now always moves over apples.  The `HILITE_APPLE` flag now only
  determines if the apple's colors are reversed to help hide the cursor.

- The snake is now green.

- Version numbers are now only displayed on debug builds or prerelease
  versions.

### Removed

- Several unused functions previously intended to be used to handle the linked
  lists used to represent the snake have been removed.

### Fixed

- Uses of the `true` keyword, which is not standard across C compilers, have
  been removed.

- "curses.h" has been used instead of "ncurses.h" to allow for the use of
  standards other than ncurses.

- Game speed is now appropriately determined according to the `CLOCKS_PER_SEC`
  constant, allowing for cross-compatibility between systems.  This has been
  used to allow a fairly consistent default speed of 10 frames per second.
