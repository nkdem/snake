#include "raylib.h"

#define BOX_SIZE 10
#define MAX_SNAKE_SIZE 25

Vector2 LEFT = {-BOX_SIZE, 0};
Vector2 RIGHT = {BOX_SIZE, 0};
Vector2 UP = {0, -BOX_SIZE};
Vector2 DOWN = {0, BOX_SIZE};

bool equalVector2(Vector2 v1, Vector2 v2) {
  return v1.x == v2.x && v1.y == v2.y;
}

// Snake struct
typedef struct Snake {
  int size;
  Vector2 speed;
  Color color;
  Vector2 body[10];
} Snake;

void upgradeSnake(Snake *snake) {
  int i = snake->size;
  float nbX = snake->body[i - 1].x;
  float nbY = snake->body[i - 1].y;
  if (equalVector2(snake->speed, LEFT)) {
    snake->body[i] = (Vector2){
        nbX + BOX_SIZE, nbY}; // plcae the new box on the right of the last box
  } else if (equalVector2(snake->speed, RIGHT)) {
    snake->body[i] = (Vector2){nbX - BOX_SIZE, nbY};
  } else if (equalVector2(snake->speed, UP)) {
    snake->body[i] = (Vector2){nbX, nbY - BOX_SIZE};
  } else if (equalVector2(snake->speed, DOWN)) {
    snake->body[i] = (Vector2){nbX, nbY + BOX_SIZE};
  }
}

void randomiseFood(Vector2 *food, int screenWidth, int screenHeight) {
  food->x = GetRandomValue(BOX_SIZE, screenWidth - BOX_SIZE);
  food->y = GetRandomValue(BOX_SIZE, screenHeight - BOX_SIZE);
}

int main(void) {
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "window");
  SetTargetFPS(25);

  bool eatten = false;
  Vector2 food;
  randomiseFood(&food, screenWidth, screenHeight);

  Snake snake = {
      2,
      (Vector2){0, 0},
      GREEN,
  };
  snake.body[0] = (Vector2){screenWidth / 2, screenHeight / 2};

  // pick random speed
  int random = GetRandomValue(0, 3);
  if (random == 0) {
    snake.speed = LEFT;
  } else if (random == 1) {
    snake.speed = RIGHT;
  } else if (random == 2) {
    snake.speed = UP;
  } else if (random == 3) {
    snake.speed = DOWN;
  }
  while (!WindowShouldClose()) {
    if (eatten) {
      randomiseFood(&food, screenWidth, screenHeight);
      eatten = false;
    }

    if (snake.size == MAX_SNAKE_SIZE) {
      // end game
      break;
    }

    if (IsKeyPressed(KEY_LEFT)) {
      if (!equalVector2(snake.speed, RIGHT)) {
        snake.speed = LEFT;
      }
    } else if (IsKeyPressed(KEY_RIGHT)) {
      if (!equalVector2(snake.speed, LEFT)) {
        snake.speed = RIGHT;
      }
    } else if (IsKeyPressed(KEY_UP)) {
      if (!equalVector2(snake.speed, DOWN)) {
        snake.speed = UP;
      }
    } else if (IsKeyPressed(KEY_DOWN)) {
      if (!equalVector2(snake.speed, UP)) {
        snake.speed = DOWN;
      }
    }

    // Update Snake Position
    snake.body[0].x += snake.speed.x;
    snake.body[0].y += snake.speed.y;

    if (snake.body[0].x < 0 || snake.body[0].x > screenWidth ||
        snake.body[0].y < 0 || snake.body[0].y > screenHeight) { // hit the wall
      break;
    }

    for (int i = snake.size; i > 0; i--) {
      snake.body[i] = snake.body[i - 1];
    }

    // Check if snake eats food
    if (CheckCollisionRecs(
            (Rectangle){snake.body[0].x, snake.body[0].y, BOX_SIZE, BOX_SIZE},
            (Rectangle){food.x, food.y, 10, 10})) {
      eatten = true;
      snake.size++;
      upgradeSnake(&snake);
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    // Draw a gray border
    DrawLineEx((Vector2){0, 0}, (Vector2){screenWidth, 0}, BOX_SIZE, GRAY);
    DrawLineEx((Vector2){0, 0}, (Vector2){0, screenHeight}, BOX_SIZE, GRAY);
    DrawLineEx((Vector2){screenWidth, 0}, (Vector2){screenWidth, screenHeight},
               BOX_SIZE, GRAY);
    DrawLineEx((Vector2){0, screenHeight}, (Vector2){screenWidth, screenHeight},
               BOX_SIZE, GRAY);

    // Draw the food
    DrawRectangleRec((Rectangle){food.x, food.y, 10, 10}, RED);

    // Draw the snake
    for (int i = 0; i < snake.size + 1; i++) { // for the length of the snake
      DrawRectangleRec(
          (Rectangle){snake.body[i].x, snake.body[i].y, BOX_SIZE, BOX_SIZE},
          snake.color);
    }
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
