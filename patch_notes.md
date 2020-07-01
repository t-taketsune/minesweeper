Alpha:
  v1.0:
    Created structures for cell and field.
    Set initialization for the game.
    Created cell-opening module.

  v1.1:
    Added constraint for bomb placing: never start bombs on starting cell to avoid insta-losses.

  v1.2:
    Updated game interface.
    Added command constants for open, mark and unmk.
    Added simple command handler.

Beta:
  v1.0:
    Updated size and number of bombs (decrease).
    Added structure for coordinate.
    Added send command to check for the winning condition.
    Refactored code into functions for each command, main loop only calls those functions now.

  v1.0.1:
    Added README file explaining the project.

  v1.0.2:
    Updated size and number of bombs (increase).

  v1.0.3:
    Removed debugging printf.
    Updated number of bombs (increase).

  v1.0.4:
    Added makefile.

  v1.2:
    Created structure for the field.
    Modified handling of positions outside the game grid via assigning an invalid value.
    Refactored code into smaller functions.
    Organized code in sequential bits of functions.
    Added the ability to choose field size and number of bombs.

  v1.3:
    Added commands help and quit.
    Reversed order of game arguments.
    Minor code refactoring.

  v1.3.1:
    Moved help and quit to own functions.

  v1.3.2:
    Minor edit to README.

Final:
  v1.0:
    Split code into various files.
    Moving interface to ncurses lib.

  v1.0.1:
    Makefile update.
