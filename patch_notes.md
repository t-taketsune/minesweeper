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
  v1.0.0:
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
