#ifndef TWIXT_H
#define TWIXT_H

#include <stdbool.h>

#define BOARD_SIZE 24
#define MAX_EDGES 1722

#define C_RESET        "\033[0m"
#define C_RED          "\033[31m"
#define C_BLUE         "\033[34m"
#define C_GREY         "\033[90m"
#define C_CYAN         "\033[36m"
#define C_BRIGHT_RED   "\033[91m"
#define C_BRIGHT_GREEN "\033[92m"

typedef enum {
    PLAYER_NONE = 0,
    PLAYER_RED,
    PLAYER_BLACK
} Player;

typedef enum {
    CELL_EMPTY = 0,
    CELL_RED_PIN,
    CELL_BLACK_PIN
} CellState;

typedef struct {
    int r1, c1;
    int r2, c2;
    Player owner;
} Edge;

typedef struct {
    CellState board[BOARD_SIZE][BOARD_SIZE];
    Edge edges[MAX_EDGES];
    int edgeCount;
} Game;

void init_game(Game *g);
bool can_place_pin(const Game *g, int r, int c, Player p);
bool place_pin(Game *g, int r, int c, Player p);

bool can_add_edge(const Game *g, int r1, int c1, int r2, int c2, Player p);
bool add_edge_internal(Game *g, int r1, int c1, int r2, int c2, Player p, bool verbose);

bool check_win(const Game *g, Player p);

void print_board(const Game *g);
void print_help_turn(void);
bool turn_loop(Game *g, Player p);

const char* player_name(Player p);
Player next_player(Player p);
void clear_screen(void);

#endif
