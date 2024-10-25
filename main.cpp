#include <raylib.h>

int player_score = 0;
int Computer_score = 0;

class Ball {
    public:
    float x, y;
    int x_movement, y_movement, radius;

    void draw() {
        DrawCircle(x, y, radius, PURPLE);
    }

    void update() {
        x += x_movement;
        y += y_movement;

        if(x + 20 >= GetScreenWidth()){
            Computer_score ++;
            x_movement *= -1;
        } else if(x - 20 <= 0){
            x_movement *= -1;
            player_score ++;
        }

        if((y + 20 >= GetScreenHeight()) || y - 20 <= 0){
            y_movement *= -1;
        }
    }
};

class Paddle {
    public:
    float x, y, width, height;
    int y_movement;

    void draw() {
        DrawRectangle(x, y, width, height, BLUE);
    }

    void update() {
            if(IsKeyDown(KEY_UP) && y > 10) {
                y -= y_movement;
            } else if(IsKeyDown(KEY_DOWN) && y + height < GetScreenHeight() - 10) {
                y += y_movement;
            }
        
    }
};

class Computer: public Paddle  {
    public:
    void update(int ball_y) {
        if(y + height / 2 < ball_y){
            y += y_movement;
        } else {
            y -= y_movement;
        }
    }
};

Ball ball;
Paddle Player;
Computer computer;

int main() {
    
    const int screen_width = 1200;
    const int screen_height = 800;
    InitWindow(screen_width, screen_height, "Ping Pong");
    SetTargetFPS(60);

    //ball
    ball.x = screen_width / 2;
    ball.y = screen_height / 2;
    ball.radius = 20;
    ball.x_movement = 7;
    ball.y_movement = 7;

    //Player
    Player.height = 140;
    Player.width = 30;
    Player.x = screen_width - 30;
    Player.y = screen_height / 2 - Player.height / 2;
    Player.y_movement = 6;

    //computer
    computer.height = 140;
    computer.width = 30;
    computer.x = 0;
    computer.y = screen_height / 2 - Player.height / 2;
    computer.y_movement = 6;

    while(WindowShouldClose() == false){
        BeginDrawing();
    
        //drawing
        ClearBackground(BLACK);       
        DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, VIOLET);
        ball.draw();
        Player.draw();
        computer.draw();
        DrawText(TextFormat("%i", Computer_score), 300, 20, 70, PURPLE);
        DrawText(TextFormat("%i", player_score), 900, 20, 70, PURPLE);

        //moving
        ball.update();
        Player.update();
        computer.update(ball.y);

        //colisions
        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{Player.x, Player.y, Player.width, Player.height}))
        {
            ball.x_movement *= -1;
        };

        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{computer.x, computer.y, computer.width, computer.height}))
        {
            ball.x_movement *= -1;
        };        

        EndDrawing();
  };

    CloseWindow();
};