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

### Added

- An in-game high scores window will now be displayed, rather than outputting
  the high scores to the terminal after the game closes.

### Changed

- Player names are no longer stored with a bunch of dots in the high scores
  file.

### Fixed

- The terminal will no longer refuse to echo input after quitting the game.
  I still don't know why that happened, but it's fixed now.

- The first apple will no longer spawn on the same line as the version number,
  to prevent the "Eat these" message from interfering with the version number
  and vice-versa.


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
