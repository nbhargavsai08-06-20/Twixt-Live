# ♟️ Twixt — Terminal Connection Game in C

---

## 📋 Table of Contents

- [About the Game](#about-the-game)
- [Board Layout](#board-layout)
- [Gameplay Rules](#gameplay-rules)
- [Win Conditions](#win-conditions)
- [Commands](#commands)
- [Board Display](#board-display)
- [Project Structure](#project-structure)
- [Build & Run](#build--run)

---

## 🎯 About the Game

Twixt is a two-player strategic connection game played on a 26×26 grid (24×24 playable area with borders).

- 🔴 **Red** tries to connect the **top border → bottom border**
- 🔵 **Blue** tries to connect the **left border → right border**

Players alternate placing pegs. The program automatically creates **knight-move links** between pegs of the same player, provided the link does not cross any existing link. The first player to form a complete connected path between their two opposite borders wins.

---

## 🗺️ Board Layout

```
         Col 0    Col 1–24     Col 25
Row 0   [ Red border (top)              ]
Row 1   [          Playable Area        ]
 ...    [           24 × 24            ]
Row 24  [          Playable Area        ]
Row 25  [ Red border (bottom)           ]

Col 0  → Left blue border
Col 25 → Right blue border
```

| Zone | Rows | Columns | Description |
|------|------|---------|-------------|
| Top border | 0 | 1–24 | Red only |
| Bottom border | 25 | 1–24 | Red only |
| Left border | 1–24 | 0 | Blue only |
| Right border | 1–24 | 25 | Blue only |
| Playable area | 1–24 | 1–24 | Both players |

---

## 📜 Gameplay Rules

### Peg Placement

**Red** may place pegs on:
- Top border: `(0, 1–24)`
- Bottom border: `(25, 1–24)`
- Playable board area: `(1–24, 1–24)`

**Blue** may place pegs on:
- Left border: `(1–24, 0)`
- Right border: `(1–24, 25)`
- Playable board area: `(1–24, 1–24)`

### Automatic Link Creation

After every valid peg placement, the program scans for knight-move neighbors and automatically creates a link if **all** of the following conditions are met:

1. Both pegs belong to the **same player**
2. The pegs are exactly a **knight's move** apart — `(±1, ±2)` or `(±2, ±1)`
3. The link does **not already exist**
4. The link does **not cross** any existing link

---

## 🏆 Win Conditions

| Player | Win Condition |
|--------|---------------|
| 🔴 Red | DFS finds a connected path from **Row 0 → Row 25** |
| 🔵 Blue | DFS finds a connected path from **Col 0 → Col 25** |

Win detection runs automatically after every move using a depth-first search on the link graph.

---

## 💻 Commands

| Command | Description |
|---------|-------------|
| `place r c` | Place a peg at row `r`, column `c` |
| `show` | Display the current board |
| `show_links` | Display all active links |
| `help` | Print available commands |
| `exit` | Quit the game |

> **Invalid placements** print `mat kar lala` or `invalid` depending on the violation type.  
> All inputs are validated against placement rules before being accepted.

---

## 🎨 Board Display

The board uses **ANSI color codes** for clear visual distinction:

| Symbol | Color | Meaning |
|--------|-------|---------|
| `R` | 🔴 Red | Red player's peg |
| `B` | 🔵 Blue | Blue player's peg |
| Top & bottom borders | Red | Red's goal edges |
| Left & right borders | Blue | Blue's goal edges |

---

## 🗂️ Project Structure

```
twixt/
│
├── main.c          → Main game loop & input handling
├── arrays.c        → Global arrays (board state, borders)
├── board.c         → show_board() and display logic
├── pinplacing.c    → place_peg() and occ() (occupancy checks)
├── links.c         → Link logic, crossing detection, neighbor graph
├── wincheck.c      → dfs(), red_win(), blue_win()
└── twixt.h         → All shared declarations and prototypes
```

---

## 🚀 Build & Run

### Compile

```bash
gcc # ♟️ Twixt — Terminal Connection Game in C

---

## 📋 Table of Contents

- [About the Game](#about-the-game)
- [Board Layout](#board-layout)
- [Gameplay Rules](#gameplay-rules)
- [Win Conditions](#win-conditions)
- [Commands](#commands)
- [Board Display](#board-display)
- [Project Structure](#project-structure)
- [Build & Run](#build--run)

---

## 🎯 About the Game

Twixt is a two-player strategic connection game played on a 26×26 grid (24×24 playable area with borders).

- 🔴 **Red** tries to connect the **top border → bottom border**
- 🔵 **Blue** tries to connect the **left border → right border**

Players alternate placing pegs. The program automatically creates **knight-move links** between pegs of the same player, provided the link does not cross any existing link. The first player to form a complete connected path between their two opposite borders wins.

---

## 🗺️ Board Layout

```
         Col 0    Col 1–24     Col 25
Row 0   [ Red border (top)              ]
Row 1   [          Playable Area        ]
 ...    [           24 × 24            ]
Row 24  [          Playable Area        ]
Row 25  [ Red border (bottom)           ]

Col 0  → Left blue border
Col 25 → Right blue border
```

| Zone | Rows | Columns | Description |
|------|------|---------|-------------|
| Top border | 0 | 1–24 | Red only |
| Bottom border | 25 | 1–24 | Red only |
| Left border | 1–24 | 0 | Blue only |
| Right border | 1–24 | 25 | Blue only |
| Playable area | 1–24 | 1–24 | Both players |

---

## 📜 Gameplay Rules

### Peg Placement

**Red** may place pegs on:
- Top border: `(0, 1–24)`
- Bottom border: `(25, 1–24)`
- Playable board area: `(1–24, 1–24)`

**Blue** may place pegs on:
- Left border: `(1–24, 0)`
- Right border: `(1–24, 25)`
- Playable board area: `(1–24, 1–24)`

### Automatic Link Creation

After every valid peg placement, the program scans for knight-move neighbors and automatically creates a link if **all** of the following conditions are met:

1. Both pegs belong to the **same player**
2. The pegs are exactly a **knight's move** apart — `(±1, ±2)` or `(±2, ±1)`
3. The link does **not already exist**
4. The link does **not cross** any existing link

---

## 🏆 Win Conditions

| Player | Win Condition |
|--------|---------------|
| 🔴 Red | DFS finds a connected path from **Row 0 → Row 25** |
| 🔵 Blue | DFS finds a connected path from **Col 0 → Col 25** |

Win detection runs automatically after every move using a depth-first search on the link graph.

---

## 💻 Commands

| Command | Description |
|---------|-------------|
| `place r c` | Place a peg at row `r`, column `c` |
| `show` | Display the current board |
| `show_links` | Display all active links |
| `help` | Print available commands |
| `exit` | Quit the game |

> **Invalid placements** print `mat kar lala` or `invalid` depending on the violation type.  
> All inputs are validated against placement rules before being accepted.

---

## 🎨 Board Display

The board uses **ANSI color codes** for clear visual distinction:

| Symbol | Color | Meaning |
|--------|-------|---------|
| `R` | 🔴 Red | Red player's peg |
| `B` | 🔵 Blue | Blue player's peg |
| Top & bottom borders | Red | Red's goal edges |
| Left & right borders | Blue | Blue's goal edges |

---

## 🗂️ Project Structure

```
twixt/
│
├── main.c          → Main game loop & input handling
├── arrays.c        → Global arrays (board state, borders)
├── board.c         → show_board() and display logic
├── pinplacing.c    → place_peg() and occ() (occupancy checks)
├── links.c         → Link logic, crossing detection, neighbor graph
├── wincheck.c      → dfs(), red_win(), blue_win()
└── twixt.h         → All shared declarations and prototypes
```

---

## 🚀 Build & Run

### Compile

```bash
gcc # ♟️ Twixt — Terminal Connection Game in C

---

## 📋 Table of Contents

- [About the Game](#about-the-game)
- [Board Layout](#board-layout)
- [Gameplay Rules](#gameplay-rules)
- [Win Conditions](#win-conditions)
- [Commands](#commands)
- [Board Display](#board-display)
- [Project Structure](#project-structure)
- [Build & Run](#build--run)

---

## 🎯 About the Game

Twixt is a two-player strategic connection game played on a 26×26 grid (24×24 playable area with borders).

- 🔴 **Red** tries to connect the **top border → bottom border**
- 🔵 **Blue** tries to connect the **left border → right border**

Players alternate placing pegs. The program automatically creates **knight-move links** between pegs of the same player, provided the link does not cross any existing link. The first player to form a complete connected path between their two opposite borders wins.

---

## 🗺️ Board Layout

```
         Col 0    Col 1–24     Col 25
Row 0   [ Red border (top)              ]
Row 1   [          Playable Area        ]
 ...    [           24 × 24            ]
Row 24  [          Playable Area        ]
Row 25  [ Red border (bottom)           ]

Col 0  → Left blue border
Col 25 → Right blue border
```

| Zone | Rows | Columns | Description |
|------|------|---------|-------------|
| Top border | 0 | 1–24 | Red only |
| Bottom border | 25 | 1–24 | Red only |
| Left border | 1–24 | 0 | Blue only |
| Right border | 1–24 | 25 | Blue only |
| Playable area | 1–24 | 1–24 | Both players |

---

## 📜 Gameplay Rules

### Peg Placement

**Red** may place pegs on:
- Top border: `(0, 1–24)`
- Bottom border: `(25, 1–24)`
- Playable board area: `(1–24, 1–24)`

**Blue** may place pegs on:
- Left border: `(1–24, 0)`
- Right border: `(1–24, 25)`
- Playable board area: `(1–24, 1–24)`

### Automatic Link Creation

After every valid peg placement, the program scans for knight-move neighbors and automatically creates a link if **all** of the following conditions are met:

1. Both pegs belong to the **same player**
2. The pegs are exactly a **knight's move** apart — `(±1, ±2)` or `(±2, ±1)`
3. The link does **not already exist**
4. The link does **not cross** any existing link

---

## 🏆 Win Conditions

| Player | Win Condition |
|--------|---------------|
| 🔴 Red | DFS finds a connected path from **Row 0 → Row 25** |
| 🔵 Blue | DFS finds a connected path from **Col 0 → Col 25** |

Win detection runs automatically after every move using a depth-first search on the link graph.

---

## 💻 Commands

| Command | Description |
|---------|-------------|
| `place r c` | Place a peg at row `r`, column `c` |
| `show` | Display the current board |
| `show_links` | Display all active links |
| `help` | Print available commands |
| `exit` | Quit the game |

> **Invalid placements** print `mat kar lala` or `invalid` depending on the violation type.  
> All inputs are validated against placement rules before being accepted.

---

## 🎨 Board Display

The board uses **ANSI color codes** for clear visual distinction:

| Symbol | Color | Meaning |
|--------|-------|---------|
| `R` | 🔴 Red | Red player's peg |
| `B` | 🔵 Blue | Blue player's peg |
| Top & bottom borders | Red | Red's goal edges |
| Left & right borders | Blue | Blue's goal edges |

---

## 🗂️ Project Structure

```
twixt/
│
├── main.c          → Main game loop & input handling
├── arrays.c        → Global arrays (board state, borders)
├── board.c         → show_board() and display logic
├── pinplacing.c    → place_peg() and occ() (occupancy checks)
├── links.c         → Link logic, crossing detection, neighbor graph
├── wincheck.c      → dfs(), red_win(), blue_win()
└── twixt.h         → All shared declarations and prototypes
```

---

## 🚀 Build & Run

### Compile

```bash
gcc main.c game.c -o twixt
```

### Run

```bash
./twixt
```

### Example Session

```
> place 0 5       # Red places on top border
> place 12 25     # Blue places on right border
> show            # Display current board
> show_links      # Display all active links
> help            # List all commands
> exit            # Quit the game
``` -o twixt
```

### Run

```bash
./twixt
```

### Example Session

```
> place 0 5       # Red places on top border
> place 12 25     # Blue places on right border
> show            # Display current board
> show_links      # Display all active links
> help            # List all commands
> exit            # Quit the game
``` -o twixt
```

### Run

```bash
./twixt
```

### Example Session

```
> place 0 5       # Red places on top border
> place 12 25     # Blue places on right border
> show            # Display current board
> show_links      # Display all active links
> help            # List all commands
> exit            # Quit the game
```
