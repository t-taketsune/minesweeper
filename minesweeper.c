#include "init.h"
#include "commands.h"

int main() {
    field game;
    init_game(&game);
    int end = 0, n_marks = 0, i, j;
    char cmd[5];
    wclear(stdscr);
    refresh();
    print_field(&game);
    while (!end) {
        scanw("%s %d %d", cmd, &i, &j, game.input_win);
        if (strcmp(cmd, open_cmd) == 0) {
            open(&game, i, j, &end);
        } else if (strcmp(cmd, mark_cmd) == 0) {
            mark(&game, i, j, &n_marks);
        } else if (strcmp(cmd, unmk_cmd) == 0) {
            unmark(&game, i, j, &n_marks);
        } else if (strcmp(cmd, send_cmd) == 0) {
            send(&game, n_marks, &end);
        } else if (strcmp(cmd, quit_cmd) == 0) {
            quit(&game);
        } else {
            printf("Unknown command. 0 0 help for a list of commands.\n");
        }
    }
    return 0;
}
