#include "Snake.hpp"
#include "Fruit.hpp"

#include <print>

#include <raylib.h>

constexpr int CELL_SIZE = 25;
constexpr int CELL_COUNT = 30;
constexpr const char* WINDOW_TITLE = "Raylib Snake";

double last_update_time{0.};


bool should_move_snake(double interval) {
    double current_time = GetTime();
    if (current_time - last_update_time >= interval) {
        last_update_time = current_time;
        return true;
    }
    return false;
}

int main(int argc, char** argv) {

    InitWindow(CELL_SIZE * CELL_COUNT, CELL_SIZE * CELL_COUNT, WINDOW_TITLE);
    SetTargetFPS(60);

    Snake snake{CELL_SIZE, CELL_COUNT, CELL_COUNT};
    Fruit fruit{CELL_SIZE, CELL_COUNT, CELL_COUNT, snake.get_occupied_positions()};

    unsigned score{0};
    while (!WindowShouldClose()) {
        BeginDrawing();

        if (should_move_snake(0.2)) {
            snake.update();
            if (snake.is_collision()) {
                snake.reset();
                fruit.next(snake.get_occupied_positions());
                score = 0;
            }
            if (snake.can_eat_food(fruit.get_pos())) {
                snake.eat_food();
                fruit.next(snake.get_occupied_positions());
                score++;
            }
        }

        ClearBackground(BLACK);
        if (IsKeyPressed(KEY_A)) {
            snake.move_left();
        }
        if (IsKeyPressed(KEY_D)) {
            snake.move_right();
        }
        if (IsKeyPressed(KEY_S)) {
            snake.move_down();
        }
        if (IsKeyPressed(KEY_W)) {
            snake.move_up();
        }

        fruit.draw();
        snake.draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
