/*
 * =====================================================================================
 *
 *       Filename:  Tetris.c
 *
 *    Description:  Tetris in raylib
 *
 *        Version:  1.0
 *        Created:  01/17/2025 09:58:53
 *       Revision:  1.0
 *       Compiler:  gcc
 *
 *         Author:  nsrddyn,
 *   Organization:
 *
 * =====================================================================================
 */

#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// GAME SETTINGS
#define FPS 60
#define FONT_SIZE 10

#define TETROMINO_SIZE_HEIGHT 2
#define TETROMINO_SIZE_WIDTH 4

#define CYAN_I (Color){0, 255, 255, 255}
#define YELLOW_O (Color){255, 255, 102, 255}
#define PURPLE_T (Color){138, 43, 226, 255}
#define GREEN_S (Color){34, 139, 34, 255}
#define RED_Z (Color){255, 69, 0, 255}
#define BLUE_J (Color){70, 130, 180, 255}
#define ORANGE_L (Color){255, 140, 0, 255}

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 600
#define COLUMNS 10
#define ROWS 20
#define CELL_WIDTH SCREEN_WIDTH / COLUMNS
#define CELL_HEIGHT SCREEN_HEIGHT / ROWS

static int SCORE = 0;

typedef struct {
  int blocks[TETROMINO_SIZE_HEIGHT][TETROMINO_SIZE_WIDTH];
  Color color;
  int x;
  int y;

} TETROMINO;

TETROMINO TETROMINOES[7] = {
    // Making the tetrominoes in an array design
    {{
         {0, 0, 0, 0},
         {1, 1, 1, 1},
     },
     CYAN_I,
     COLUMNS / 2,
     0},
    // supposed to have 2 forms of rotations
    // default spawn location is: center

    {{
         {0, 1, 1, 0},
         {0, 1, 1, 0},
     },
     YELLOW_O,
     COLUMNS / 2,
     0},
    // supposed to have no rotation forms
    // default spawn location is: center
    {{
         {0, 1, 0, 0},
         {1, 1, 1, 0},
     },
     PURPLE_T,
     0,
     0},
    // flat side left center
    // 4 rotational forms
    {{
         {0, 1, 1, 0},
         {1, 1, 0, 0},
     },
     GREEN_S,
     0,
     0},
    // left center
    // 4 rotational forms
    {{
         {1, 1, 0, 0},
         {0, 1, 1, 0},
     },
     RED_Z,
     0,
     0},
    // left center
    // 4 rotational forms
    {{
         {1, 0, 0, 0},
         {1, 1, 1, 0},
     },
     BLUE_J,
     0,
     0},
    // flat side first and left center
    // 4 rotational forms
    {{
         {0, 0, 1, 0},
         {1, 1, 1, 0},
     },
     ORANGE_L,
     0,
     0},
    // flat side first and left center
    // 4 rotational forms
};

void DRAW_BACKGROUND_GRID() {
  for (int i = 0; i <= COLUMNS; i++) {
    DrawLine(i * CELL_WIDTH, 0, i * CELL_WIDTH, SCREEN_HEIGHT, GRAY);
  }
  for (int j = 0; j <= ROWS; j++) {
    DrawLine(0, j * CELL_HEIGHT, SCREEN_WIDTH, j * CELL_HEIGHT, GRAY);
  }
}

int **CREATE_TETROMINOS_GRID(int rows, int columns) {
  int **array = malloc(rows * sizeof(int *));
  if (!array)
    return NULL;

  for (int i = 0; i < rows; i++)

  {
    array[i] = calloc(columns, sizeof(int));
    if (!array[i]) {
      for (int j = 0; j < i; j++)
        free(array[j]);
      free(array);
      return NULL;
    }
  }
  return array;
}

void CHECK_FULL_LINE(int **GRID) {
  for (int y = 0; y < ROWS; y++) {
    bool FULL_LINE = true;

    for (int x = 0; x < COLUMNS; x++) {
      if (GRID[y][x] == 0) {
        FULL_LINE = false;
        break;
      }
    }

    if (FULL_LINE) {
      for (int i = y; i > 0; i--) {
        for (int x = 0; x < COLUMNS; x++)
          GRID[i][x] = GRID[i - 1][x];
      }

      for (int x = 0; x < COLUMNS; x++)
        GRID[ROWS - 2][x] = 0;

      SCORE += 10;
    }
  }
}

// Detect if the active tetromino is hitting another tetromino
// Detect if the active tetromino is hitting another tetromino
int COLLISION_DETECTION(TETROMINO *tetromino, int **GRID) {
  int TETROMINO_WIDTH = 0;
  int TETROMINO_HEIGHT = 0;

  // Determine the bounding width and height of the tetromino
  for (int y = 0; y < TETROMINO_SIZE_HEIGHT; y++) {
    for (int x = 0; x < TETROMINO_SIZE_WIDTH; x++) {
      if (tetromino->blocks[y][x] == 1) {
        // Update width and height based on the furthest active blocks
        if (x + 1 > TETROMINO_WIDTH)
          TETROMINO_WIDTH = x + 1;
        if (y + 1 > TETROMINO_HEIGHT)
          TETROMINO_HEIGHT = y + 1;
      }
    }
  }

  // Check for collision with the grid
  for (int i = 0; i < TETROMINO_HEIGHT; i++) {
    for (int j = 0; j < TETROMINO_WIDTH; j++) {
      if (tetromino->blocks[i][j] == 1) {
        int GRID_X = tetromino->x + j;
        int GRID_Y = tetromino->y + i;

        // Check if we are within the grid boundaries and if there is a block
        if (GRID_Y >= 0 && GRID_X >= 0 && GRID[GRID_Y][GRID_X] != 0) {
          return 1; // Collision detected
        }
      }
    }
  }

  // No collision
  return 0;
}
int *ROTATE_ACTIVE_TETROMINO(TETROMINO *tetromino, int **GRID) {
  int *ROTATED_TETROMINO;

  for (int x = 0; x < COLUMNS; x++) {
    for (int y = 0; y < ROWS; y++) {
      ROTATED_TETROMINO = 0;
    }
  }
  return ROTATED_TETROMINO;
}

void FREE_GRID(int **array, int rows) {
  for (int i = 0; i < rows; i++)
    free(array[i]);
  free(array);
}

void DRAW_TETROMINO(TETROMINO *tetromino) {
  for (int y = 0; y < TETROMINO_SIZE_HEIGHT; y++) {
    for (int x = 0; x < TETROMINO_SIZE_WIDTH; x++) {
      if (tetromino->blocks[y][x] == 1) {
        DrawRectangle((tetromino->x + x) * CELL_WIDTH,
                      (tetromino->y + y) * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT,
                      tetromino->color);
      }
    }
  }
}

TETROMINO SPAWN_TETROMINO() {
  int RANDOM_INDEX = GetRandomValue(0, 6);
  TETROMINO tetromino = TETROMINOES[RANDOM_INDEX];

  if (tetromino.x == 0) {
    tetromino.x = COLUMNS / 2 - 2;
    tetromino.y = 0;
  }
  return tetromino;
}

void MOVE_TETROMINO(TETROMINO *tetromino, int **GRID) {
  // RIGHT WALL COLLISION DETECTION BY STOPPING MOVEMENT
  if (IsKeyDown(KEY_RIGHT) && COLLISION_DETECTION(tetromino, GRID) == 0 &&
      tetromino->x < COLUMNS - 2)
    tetromino->x++;
  // LEFT WALL COLLISION DETECTION BY STOPPING MOVEMENT
  if (IsKeyDown(KEY_LEFT) && COLLISION_DETECTION(tetromino, GRID) == 0 &&
      tetromino->x > 0)
    tetromino->x--;
  // BOTTOM ROW COLLISION DETECTION BY STOPPING MOVEMENT
  if (IsKeyDown(KEY_DOWN) && COLLISION_DETECTION(tetromino, GRID) == 0 &&
      tetromino->y < ROWS - 2)
    tetromino->y++;
}

void SAVE_TETROMINO(TETROMINO *tetromino, int **GRID) {
  for (int y = 0; y < TETROMINO_SIZE_HEIGHT; y++) {
    for (int x = 0; x < TETROMINO_SIZE_WIDTH; x++) {
      if (tetromino->blocks[y][x] == 1) {
        int GRIDX = tetromino->x + x;
        int GRIDY = tetromino->y + y;
        if (GRIDX < COLUMNS && GRIDY >= 0 && GRIDY < ROWS)
          GRID[GRIDY][GRIDX] = 1;
      }
    }
  }
}

void DRAW_SAVED_TETROMINO(int **GRID, TETROMINO *tetromino) {
  for (int y = 0; y < ROWS; y++) {
    for (int x = 0; x < COLUMNS; x++) {
      if (GRID[y][x] == 1)
        DrawRectangle((x * CELL_WIDTH), (y * CELL_HEIGHT), CELL_WIDTH,
                      CELL_HEIGHT, tetromino->color);
    }
  }
}

void DRAW_STATS(TETROMINO *tetromino) {
  char SCORE_TEXT[16];
  sprintf(SCORE_TEXT, "SCORE: %d", SCORE);
  DrawText(SCORE_TEXT, 10, 10, FONT_SIZE, BLUE);

  char CURRENT_Y_POSITION[32], CURRENT_X_POSITION[32];
  sprintf(CURRENT_Y_POSITION, "Y COÖRDINATE: %d", tetromino->y);
  sprintf(CURRENT_X_POSITION, "X COÖRDINATE: %d", tetromino->x);
  DrawText(CURRENT_Y_POSITION, 10, 50, FONT_SIZE, BLUE);
  DrawText(CURRENT_X_POSITION, 10, 80, FONT_SIZE, BLUE);

  int POS_X = SCREEN_WIDTH / 2;
  int POS_Y = SCREEN_HEIGHT / 2;

  const char ERROR_TEXT[] = "LOW FPS";
  if (GetFPS() < 40)
    DrawText(ERROR_TEXT, POS_X, POS_Y, FONT_SIZE, RED);
}

int main() {
  // Initialize the window and set the wanted FPS
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tetris");
  SetTargetFPS(FPS);

  // Spawn a new tetromino
  TETROMINO ACTIVE_TETROMINO = SPAWN_TETROMINO();

  int **GRID = CREATE_TETROMINOS_GRID(ROWS, COLUMNS);
  if (!GRID) {
    printf("Failed to allocate memory for the grid.");
    CloseWindow();
    return 1;
  }

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);

    DRAW_BACKGROUND_GRID();
    DRAW_SAVED_TETROMINO(GRID, &ACTIVE_TETROMINO);
    DRAW_TETROMINO(&ACTIVE_TETROMINO);
    DRAW_STATS(&ACTIVE_TETROMINO);

    MOVE_TETROMINO(&ACTIVE_TETROMINO, GRID);

    if (ACTIVE_TETROMINO.y == ROWS - 2 ||
        COLLISION_DETECTION(&ACTIVE_TETROMINO, GRID) != 0) {
      SCORE++;
      SAVE_TETROMINO(&ACTIVE_TETROMINO, GRID);
      ACTIVE_TETROMINO = SPAWN_TETROMINO();
      printf("DEBUGGING INFORMATION - XOR %p: ", &ACTIVE_TETROMINO.x);
      printf("DEBUGGING INFORMATION - YOR %p: ", &ACTIVE_TETROMINO.y);
    }

    EndDrawing();
  }

  FREE_GRID(GRID, ROWS);
  CloseWindow();
  return 0;
}
