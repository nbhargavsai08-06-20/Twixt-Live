#include "twixt.h"
#include <stdio.h>
#include <string.h>

void clear_screen(void) {
    for (int i = 0; i < 40; i++) putchar('\n');
}

const char* player_name(Player p) {
    if (p == PLAYER_RED) return "RED (R)";
    if (p == PLAYER_BLACK) return "BLACK (B)";
    return "NONE";
}

Player next_player(Player p) {
    return (p == PLAYER_RED) ? PLAYER_BLACK : PLAYER_RED;
}

void print_board(const Game *g) {
    printf(C_GREY "\n    ");
    for (int c = 0; c < BOARD_SIZE; c++)
        printf("%2d ", c + 1);
    printf("\n");

    for (int r = 0; r < BOARD_SIZE; r++) {
        printf("%2d |", r + 1);
        for (int c = 0; c < BOARD_SIZE; c++) {
            CellState cell = g->board[r][c];
            if (cell == CELL_RED_PIN)
                printf(" " C_RED "R" C_RESET C_GREY " ");
            else if (cell == CELL_BLACK_PIN)
                printf(" " C_BLUE "B" C_RESET C_GREY " ");
            else
                printf(" . ");
        }
        printf("|\n");
    }
    printf(C_RESET "\n");

    printf("Links:\n");
    if (g->edgeCount == 0) {
        printf("  (none)\n");
    } else {
        for (int i = 0; i < g->edgeCount; i++) {
            const Edge *e = &g->edges[i];
            printf("  %s: (%d,%d) <-> (%d,%d)\n",
                   e->owner == PLAYER_RED ? "Red" : "Black",
                   e->r1 + 1, e->c1 + 1, e->r2 + 1, e->c2 + 1);
        }
    }
}

void print_help_turn(void) {
    printf("Commands:\n");
    printf("  help\n");
    printf("  place r c\n");
    printf("  done\n");
    printf("  quit\n");
}

bool turn_loop(Game *g, Player p) {
    bool placed = false;
    char cmd[32];

    while (1) {
        printf("[%s] Enter command: ", player_name(p));
        if (scanf("%31s", cmd) != 1) return false;

        if (!strcmp(cmd, "help")) {
            print_help_turn();
        }
        else if (!strcmp(cmd, "place")) {
            if (placed) continue;
            int r, c;
            if (scanf("%d %d", &r, &c) != 2) continue;
            r--; c--;
            if (place_pin(g, r, c, p)) {
                placed = true;
                clear_screen();
                print_board(g);
            }
        }
        else if (!strcmp(cmd, "done")) {
            if (!placed) continue;
            return true;
        }
        else if (!strcmp(cmd, "quit")) {
            return false;
        }
    }
}

int main() {
    Game g;
    init_game(&g);
    Player p = PLAYER_RED;
    int turn = 1;

    clear_screen();
    printf("** Twixt CLI **\n");

    while (1) {
        clear_screen();
        printf("-- Turn %d: %s --\n", turn, player_name(p));
        print_board(&g);

        if (!turn_loop(&g, p)) break;
        if (check_win(&g, p)) {
            clear_screen();
            print_board(&g);
            printf("%s WINS!\n", player_name(p));
            break;
        }

        p = next_player(p);
        turn++;
    }

    return 0;
}
