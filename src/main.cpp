#include "raylib.h"
#include <vector>

const int ROWS = 25;
const int COLS = 40;
const int CELL = 30;

enum CellType
{
    EMPTY,
    WALL,
    START,
    END
};

int main()
{
    InitWindow(COLS * CELL, ROWS * CELL, "Pathfinding Visualizer");
    SetTargetFPS(60);

    std::vector<std::vector<CellType>> grid(ROWS, std::vector<CellType>(COLS, EMPTY));
    grid[12][5] = START;
    grid[12][34] = END;

    while (!WindowShouldClose())
    {
        int col = GetMouseX() / CELL;
        int row = GetMouseY() / CELL;
        bool inside = row >= 0 && row < ROWS && col >= 0 && col < COLS;

        if (inside)
        {
            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && grid[row][col] == EMPTY)
                grid[row][col] = WALL;
            if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON) && grid[row][col] == WALL)
                grid[row][col] = EMPTY;
        }

        BeginDrawing();
        ClearBackground(Color{20, 20, 20, 255});

        for (int r = 0; r < ROWS; r++)
        {
            for (int c = 0; c < COLS; c++)
            {
                Color color = Color{45, 45, 45, 255}; // Default color for EMPTY cells
                if (grid[r][c] == WALL)
                    color = Color{140, 140, 140, 255}; // Color for WALL cells
                if (grid[r][c] == START)
                    color = GREEN;
                if (grid[r][c] == END)
                    color = RED;
                DrawRectangle(c * CELL, r * CELL, CELL - 1, CELL - 1, color);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}