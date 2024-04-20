#include "raylib.h"

// STATIC
int BORDER_SIZE = 10;

int main(void) {
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "window");
  SetTargetFPS(60);

  bool eatten = false;
  Vector2 food = {GetRandomValue(BORDER_SIZE, screenWidth - BORDER_SIZE),
                  GetRandomValue(BORDER_SIZE, screenHeight - BORDER_SIZE)};

  while (!WindowShouldClose()) {
    if (eatten) {
      food = (Vector2){GetRandomValue(BORDER_SIZE, screenWidth - BORDER_SIZE),
                       GetRandomValue(BORDER_SIZE, screenHeight - BORDER_SIZE)};
      eatten = false;
    }
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // Draw a gray border
    DrawLineEx((Vector2){0, 0}, (Vector2){screenWidth, 0}, BORDER_SIZE, GRAY);
    DrawLineEx((Vector2){0, 0}, (Vector2){0, screenHeight}, BORDER_SIZE, GRAY);
    DrawLineEx((Vector2){screenWidth, 0}, (Vector2){screenWidth, screenHeight},
               BORDER_SIZE, GRAY);
    DrawLineEx((Vector2){0, screenHeight}, (Vector2){screenWidth, screenHeight},
               BORDER_SIZE, GRAY);

    DrawRectangleRec((Rectangle){food.x, food.y, 10, 10}, RED);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
