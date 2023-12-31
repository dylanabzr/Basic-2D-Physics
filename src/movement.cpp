#include <raylib.h>
#include <iostream>
#include <unistd.h>
#include <cstdint>
#define WINDOW_HEIGHT 1000
#define WINDOW_WIDTH 1000

struct Object{
  int posX, posY, height, width;
};



class Game_Objects{
  protected:
    Object human {WINDOW_WIDTH/2, 3 * WINDOW_HEIGHT / 5, 50, 30};
    Object ground {0, human.posY + human.height, 5, WINDOW_WIDTH};
    bool isColliding(const Object obj1, const Object obj2) { // for now that function is useless, but i'll use it in the future :)
      bool xOverlap = (obj1.posX < obj2.posX + obj2.width) && (obj2.posX < obj1.posX + obj1.width);
      bool yOverlap =  (obj1.posY < obj2.posY + obj2.height) && (obj2.posY < obj1.posY + obj1.height);
      return (xOverlap && yOverlap);
    }
    
};

class Movement : public Game_Objects{
  protected:
    int8_t X_Movement_Status = 0, Y_Movement_Status = 0;
    uint16_t Xcount = 0, Ycount = 0;
    void walk() {
      X_Movement_Status = IsKeyDown(KEY_D) - IsKeyDown(KEY_A);
      human.posX += 5 * X_Movement_Status;
      if (X_Movement_Status) Xcount++;
      if (Xcount >= 10) {
        X_Movement_Status = 0;
        Xcount = 0;
      } 
    }
    void jump() {
      if (!Y_Movement_Status) {
        Y_Movement_Status = IsKeyDown(KEY_SPACE);
        return;
      }  
      human.posY -= 7 * Y_Movement_Status;
      Ycount++;
      if (Y_Movement_Status == 1) {
        if (Ycount >= 15) {
          Y_Movement_Status = -1;
          Ycount=0;
        }
      }
      if (Y_Movement_Status == -1) {
          if (Ycount >= 15) {
            Y_Movement_Status = 0;
            Ycount = 0;
          }
      }
    }
    void basicMovement() {
      walk();
      jump();
    }
    
};

class Graphics : Movement{
  protected:
    void gameUI() {
      BeginDrawing();
      ClearBackground(RAYWHITE);
      DrawRectangle(human.posX, human.posY, human.width, human.height, GRAY);
      DrawRectangle(ground.posX, ground.posY, ground.width, ground.height, BLACK);
      basicMovement();
      EndDrawing();
    }
};

class Window : Graphics{
  public:
    void windowLoop() {
      InitWindow(WINDOW_HEIGHT, WINDOW_WIDTH, "Physics");
      SetTargetFPS(60);
      while(!WindowShouldClose()){
        if (IsKeyDown(KEY_ESCAPE)) WindowShouldClose();
        gameUI();
      }
      CloseWindow();
    }
};

void startGame() {
  Window window;
  window.windowLoop();
}

int main() {
  startGame();
  return 0; 
}
