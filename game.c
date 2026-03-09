#include "twixt.h"
#include <stdio.h>

static bool in_bounds(int r, int c) {
    return (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE);
}

void init_game(Game *g) {
    g->edgeCount = 0;
    for (int r = 0; r < BOARD_SIZE; r++)
        for (int c = 0; c < BOARD_SIZE; c++)
            g->board[r][c] = CELL_EMPTY;
}

bool can_place_pin(const Game *g, int r, int c, Player p) {
    if (!in_bounds(r, c)) return false;
    if (g->board[r][c] != CELL_EMPTY) return false;
    if (p == PLAYER_RED && (c == 0 || c == BOARD_SIZE - 1)) return false;
    if (p == PLAYER_BLACK && (r == 0 || r == BOARD_SIZE - 1)) return false;
    return true;
}

bool place_pin(Game *g, int r, int c, Player p) {
    if (!can_place_pin(g, r, c, p)) return false;

    g->board[r][c] = (p == PLAYER_RED) ? CELL_RED_PIN : CELL_BLACK_PIN;

    static const int OFF[8][2] = {
        {-2,-1},{-2,1},{-1,-2},{-1,2},
        { 1,-2},{ 1,2},{ 2,-1},{ 2,1}
    };

    for (int i = 0; i < 8; i++) {
        int nr = r + OFF[i][0], nc = c + OFF[i][1];
        if (!in_bounds(nr, nc)) continue;
        if (p == PLAYER_RED) {
            if (g->board[nr][nc] != CELL_RED_PIN) continue;
        } else {
            if (g->board[nr][nc] != CELL_BLACK_PIN) continue;
        }
        add_edge_internal(g, r, c, nr, nc, p, false);
    }

    return true;
}

static bool is_knight_move(int r1, int c1, int r2, int c2) {
    int dr = r1 - r2; if (dr < 0) dr = -dr;
    int dc = c1 - c2; if (dc < 0) dc = -dc;
    return (dr == 1 && dc == 2) || (dr == 2 && dc == 1);
}

static bool edge_equals(const Edge *e, int r1, int c1, int r2, int c2) {
    return ((e->r1 == r1 && e->c1 == c1 && e->r2 == r2 && e->c2 == c2) ||
            (e->r1 == r2 && e->c1 == c2 && e->r2 == r1 && e->c2 == c1));
}

static bool edge_exists(const Game *g, int r1, int c1, int r2, int c2, Player p) {
    for (int i = 0; i < g->edgeCount; i++) {
        const Edge *e = &g->edges[i];
        if (e->owner == p && edge_equals(e, r1, c1, r2, c2)) return true;
    }
    return false;
}

typedef struct { int x, y; } Point;

static int crosschecking(Point a, Point b, Point c) {
    long long v = (long long)(b.x - a.x) * (c.y - a.y)
                - (long long)(b.y - a.y) * (c.x - a.x);
    if (v == 0) return 0;
    return (v > 0) ? 1 : 2;
}

static bool segments_intersect(Point p1, Point q1, Point p2, Point q2) {
    int o1 = crosschecking(p1, q1, p2);
    int o2 = crosschecking(p1, q1, q2);
    int o3 = crosschecking(p2, q2, p1);
    int o4 = crosschecking(p2, q2, q1);
    return (o1 != o2 && o3 != o4);
}

bool link_crosses_any(const Game *g, int r1, int c1, int r2, int c2) {
    Point p = {c1, r1}, q = {c2, r2};

    for (int i = 0; i < g->edgeCount; i++) {
        const Edge *e = &g->edges[i];

        if ((e->r1 == r1 && e->c1 == c1) ||
            (e->r2 == r1 && e->c2 == c1) ||
            (e->r1 == r2 && e->c1 == c2) ||
            (e->r2 == r2 && e->c2 == c2))
            continue;

        Point p2 = {e->c1, e->r1};
        Point q2 = {e->c2, e->r2};

        if (segments_intersect(p, q, p2, q2)) return true;
    }
    return false;
}

bool can_add_edge(const Game *g, int r1, int c1, int r2, int c2, Player p) {
    if (!in_bounds(r1, c1) || !in_bounds(r2, c2)) return false;
    if (r1 == r2 && c1 == c2) return false;
    if (!is_knight_move(r1, c1, r2, c2)) return false;

    CellState s1 = g->board[r1][c1];
    CellState s2 = g->board[r2][c2];

    if (p == PLAYER_RED) {
        if (s1 != CELL_RED_PIN || s2 != CELL_RED_PIN) return false;
    } else {
        if (s1 != CELL_BLACK_PIN || s2 != CELL_BLACK_PIN) return false;
    }

    if (edge_exists(g, r1, c1, r2, c2, p)) return false;
    if (link_crosses_any(g, r1, c1, r2, c2)) return false;
    if (g->edgeCount >= MAX_EDGES) return false;

    return true;
}

bool add_edge_internal(Game *g, int r1, int c1, int r2, int c2, Player p, bool verbose) {
    if (!can_add_edge(g, r1, c1, r2, c2, p)) return false;

    Edge *e = &g->edges[g->edgeCount++];
    e->r1 = r1; e->c1 = c1;
    e->r2 = r2; e->c2 = c2;
    e->owner = p;

    if (verbose) {
        printf(C_BRIGHT_GREEN "Link added between (%d,%d) and (%d,%d)." C_RESET "\n",
               r1 + 1, c1 + 1, r2 + 1, c2 + 1);
    }
    return true;
}

static bool dfs_red(const Game *g, bool vis[BOARD_SIZE][BOARD_SIZE], int r, int c) {
    if (vis[r][c]) return false;
    vis[r][c] = true;

    if (r == BOARD_SIZE - 1) return true;

    for (int i = 0; i < g->edgeCount; i++) {
        const Edge *e = &g->edges[i];
        if (e->owner != PLAYER_RED) continue;

        int nr = -1, nc = -1;
        if (e->r1 == r && e->c1 == c) { nr = e->r2; nc = e->c2; }
        else if (e->r2 == r && e->c2 == c) { nr = e->r1; nc = e->c1; }
        else continue;

        if (!vis[nr][nc] && dfs_red(g, vis, nr, nc))
            return true;
    }
    return false;
}

static bool dfs_black(const Game *g, bool vis[BOARD_SIZE][BOARD_SIZE], int r, int c) {
    if (vis[r][c]) return false;
    vis[r][c] = true;

    if (c == BOARD_SIZE - 1) return true;

    for (int i = 0; i < g->edgeCount; i++) {
        const Edge *e = &g->edges[i];
        if (e->owner != PLAYER_BLACK) continue;

        int nr = -1, nc = -1;
        if (e->r1 == r && e->c1 == c) { nr = e->r2; nc = e->c2; }
        else if (e->r2 == r && e->c2 == c) { nr = e->r1; nc = e->c1; }
        else continue;

        if (!vis[nr][nc] && dfs_black(g, vis, nr, nc))
            return true;
    }
    return false;
}

bool check_win(const Game *g, Player p) {
    bool vis[BOARD_SIZE][BOARD_SIZE] = {0};

    if (p == PLAYER_RED) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            if (g->board[0][c] == CELL_RED_PIN)
                if (dfs_red(g, vis, 0, c))
                    return true;
        }
    } else {
        for (int r = 0; r < BOARD_SIZE; r++) {
            if (g->board[r][0] == CELL_BLACK_PIN)
                if (dfs_black(g, vis, r, 0))
                    return true;
        }
    }

    return false;
}
