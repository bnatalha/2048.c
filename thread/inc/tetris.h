#ifndef TETRIS_HEADER
#define TETRIS_HEADER

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define ESC 27

#define DELAY 1
#define DELAY_FACTOR 0.8

#define RED 1
#define GREEN 2
#define YELLOW 3
#define BLUE 4
#define FUCHSIA 5
#define CYAN 6
#define WHITE 7

#define PLAYFIELD_W 10
#define PLAYFIELD_H 20
#define PLAYFIELD_X 30
#define PLAYFIELD_Y 1
#define BORDER_COLOR YELLOW

#define SCORE_X 1
#define SCORE_Y 2
#define SCORE_COLOR GREEN

#define HELP_X 58
#define HELP_Y 1
#define HELP_COLOR CYAN

#define NEXT_X 14
#define NEXT_Y 11

#define GAMEOVER_X 1
#define GAMEOVER_Y (PLAYFIELD_H + 3)

#define LEVEL_UP 20

#define FILLED_CELL "[]"
#define NEXT_EMPTY_CELL "  "
#define PLAYFIELD_EMPTY_CELL " ."

struct termios terminal_conf;
int use_color = 1;
long tetris_delay = DELAY * 1000000;

typedef struct {
    int origin_x;
    int origin_y;
    int x;
    int y;
    int color;
    int symmetry;
    int orientation;
    int *data;
    char empty_cell[3];
} tetris_piece_s;

// ============================================================================
// FUNCTIONS ==================================================================
// ============================================================================

void clear_screen();

void xyprint(int x, int y, char *s);

void show_cursor();

void hide_cursor();

void set_fg(int color);

void set_bg(int color);

void reset_colors();

void set_bold();

void cmd_quit();

int *get_cells(tetris_piece_s piece, int *position);

void draw_piece(tetris_piece_s piece, int visible);

int position_ok(tetris_piece_s piece, int *playfield, int *position);

int move(tetris_piece_s *piece, int *playfield, int dx, int dy, int dz);

void flatten_piece(tetris_piece_s *piece, int *playfield);

void draw_playfield(int *playfield);

int line_complete(int line);

int process_complete_lines(int *playfield);

void update_score(int complete_lines);

void process_fallen_piece(tetris_piece_s *piece, int *playfield);

void cmd_right(tetris_piece_s *piece, int *playfield);

void cmd_left(tetris_piece_s *piece, int *playfield);

void cmd_rotate(tetris_piece_s *piece, int *playfield);

int cmd_down(tetris_piece_s *piece, int *playfield);

void cmd_drop(tetris_piece_s *piece, int *playfield);

void draw_help(int visible);

void draw_border();

tetris_piece_s get_next_piece(int visible);

void redraw_screen(int help_visible, tetris_piece_s next_piece, int next_visible, tetris_piece_s current_piece, int *playfield);

tetris_piece_s get_current_piece(tetris_piece_s next_piece, int *playfield);

char get_key(long delay);

long get_current_micros();

int game();

#endif