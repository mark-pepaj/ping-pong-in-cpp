#include <raylib.h>
#include <cmath>


const float PIXELS_PER_METER = 100.0f;

const int screenHeight = 600;
const int screenWidth = 800;


const int playerOneHeight = 100;
const int playerOneWidth = 20;
const int playerTwoHeight = 100;
const int playerTwoWidth = 20;

const int playerOneStartPos = 0;
const int playerTwoStartPos = screenWidth - playerTwoWidth;


const int pongSize = 25;
float pongX = (screenWidth / 2.0f) - (pongSize / 2.0f);
float pongY = (screenHeight / 2.0f) - (pongSize / 2.0f);

const int leftBoundary = 0;
const int rightBoundary = screenWidth - pongSize;

const int ceilY = 0;
const int playerFloorY = screenHeight - playerOneHeight;
const int pongFloorY = screenHeight - pongSize;

const float movingSpeed = 2.5f * PIXELS_PER_METER;

const int FPS = 60;


int main() {

    InitWindow(screenWidth, screenHeight, "Pong");
    SetTargetFPS(FPS);

    // start both players in the middle
    float playerOneY = screenHeight / 2.0f;
    float playerTwoY = screenHeight / 2.0f;

    float playerOneY_velocity = 0.0f;
    float playerTwoY_velocity = 0.0f;

    float pongX_velocity = GetRandomValue(0, 1) ? movingSpeed : -movingSpeed;
    float pongY_velocity = GetRandomValue(0, 1) ? movingSpeed : -movingSpeed;

    float dt = 0.0f;

    int playerOneScore = 0;
    int playerTwoScore = 0;
    
    bool gameStarted = false;
    bool paddleCollision = false;

    while(!WindowShouldClose()) {
        dt = GetFrameTime();

        if (!gameStarted) {
            const char* msg = "Press SPACE to Start";
            int msgWidth = MeasureText(msg, 30);
            DrawText(msg, (screenWidth - msgWidth) / 2, screenHeight / 2 - 60, 30, GRAY);
            if (IsKeyPressed(KEY_SPACE)) gameStarted = true;
        }
        else {
            if (IsKeyPressed(KEY_W)) playerOneY_velocity = -std::abs(movingSpeed);
            if (IsKeyPressed(KEY_S)) playerOneY_velocity = movingSpeed;

            if (IsKeyPressed(KEY_UP)) playerTwoY_velocity = -std::abs(movingSpeed);
            if (IsKeyPressed(KEY_DOWN)) playerTwoY_velocity = movingSpeed;
            
            playerOneY += playerOneY_velocity * dt;
            playerTwoY += playerTwoY_velocity * dt;

            pongX += pongX_velocity * dt;
            pongY += pongY_velocity * dt;

            if (playerOneY > playerFloorY) {
                playerOneY = playerFloorY;
                playerOneY_velocity = -std::abs(movingSpeed);
            }
            else if (playerOneY < ceilY) {
                playerOneY = 0;
                playerOneY_velocity = movingSpeed;
            }

            if (playerTwoY > playerFloorY) {
                playerTwoY = playerFloorY;
                playerTwoY_velocity = -std::abs(movingSpeed);
            }
            else if (playerTwoY < ceilY) {
                playerTwoY = 0;
                playerTwoY_velocity = movingSpeed;
            }


            if ((pongY + pongSize > playerOneY) && (pongY < playerOneY + playerOneHeight)) {
                if (pongX < leftBoundary + playerOneWidth) { 
                    pongX = leftBoundary + playerOneWidth;
                    pongX_velocity = std::abs(movingSpeed);
                    pongY_velocity = playerOneY_velocity;
                    paddleCollision = true;                
                }
            }

            if ((pongY + pongSize > playerTwoY) && (pongY < playerTwoY + playerTwoHeight)) {
                if (pongX > rightBoundary - playerTwoWidth) { 
                    pongX = rightBoundary - playerTwoWidth;
                    pongX_velocity = -std::abs(movingSpeed);
                    pongY_velocity = playerTwoY_velocity;
                    paddleCollision = true;                
                }
            }
            
            if (paddleCollision == false) {
                if (pongX > rightBoundary) {
                    pongX = screenWidth / 2.0f;
                    pongY = screenHeight / 2.0f;
                    pongX_velocity = -std::abs(movingSpeed);
                    playerOneScore++;
                    gameStarted = false;
                }
                else if (pongX < leftBoundary) {
                    pongX = screenWidth / 2.0f;
                    pongY = screenHeight / 2.0f;
                    pongX_velocity = std::abs(movingSpeed);
                    playerTwoScore++;
                    gameStarted = false;
                }

                if (pongY > pongFloorY) {
                    pongY = pongFloorY;
                    pongY_velocity = -std::abs(movingSpeed);
                }
                else if (pongY < ceilY) {
                    pongY = ceilY;
                    pongY_velocity = std::abs(movingSpeed);
                }
            }            
            
            paddleCollision = false;
        }
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawRectangle(playerOneStartPos, (int)playerOneY, playerOneWidth, playerOneHeight, MAROON);
        DrawRectangle(playerTwoStartPos, (int)playerTwoY, playerTwoWidth, playerTwoHeight, MAROON);
        DrawRectangle((int)pongX, (int)pongY, pongSize, pongSize, BLACK);
        DrawText(TextFormat("%d", playerOneScore), screenWidth / 4, 20, 40, DARKGRAY);
        DrawText(TextFormat("%d", playerTwoScore), 3 * screenWidth / 4, 20, 40, DARKGRAY);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
