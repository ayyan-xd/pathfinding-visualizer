#include "raylib.h"
#include <vector>
#include <queue>

const int ROWS = 25;
const int COLS = 40;
const int CELL = 30;

enum CellType
{
    EMPTY,
    WALL,
    START,
    END,
    VISITED,
    PATH
};

struct Point
{
    int r, c;
};

int main()
{
    InitWindow(COLS * CELL, ROWS * CELL, "Pathfinding Visualizer");
    SetTargetFPS(60);

    std::vector<std::vector<CellType>> grid(ROWS, std::vector<CellType>(COLS, EMPTY));
    int startR = 12, startC = 5;
    grid[startR][startC] = START;
    grid[12][34] = END;

    std::queue<Point> q;
    std::vector<std::vector<bool>> seen(ROWS, std::vector<bool>(COLS, false));
    std::vector<std::vector<Point>> parent(ROWS, std::vector<Point>(COLS, Point{-1, -1}));
    bool searching = false;

    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    while (!WindowShouldClose())
    {
        // draw and erase walls
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

        // press SPACE to start BFS
        if (IsKeyPressed(KEY_SPACE) && !searching)
        {
            searching = true;
            q.push({startR, startC});
            seen[startR][startC] = true;
        }

        // BFS: a few squares per frame
        for (int s = 0; s < 4 && searching && !q.empty(); s++)
        {
            Point cur = q.front();
            q.pop();

            for (int i = 0; i < 4; i++)
            {
                int nr = cur.r + dr[i];
                int nc = cur.c + dc[i];

                if (nr < 0 || nr >= ROWS || nc < 0 || nc >= COLS)
                    continue;
                if (seen[nr][nc] || grid[nr][nc] == WALL)
                    continue;

                seen[nr][nc] = true;
                parent[nr][nc] = cur;

                if (grid[nr][nc] == END)
                {
                    searching = false;

                    // walk back from the end to the start
                    Point p = parent[nr][nc];
                    while (!(p.r == startR && p.c == startC))
                    {
                        grid[p.r][p.c] = PATH;
                        p = parent[p.r][p.c];
                    }
                    break;
                }

                grid[nr][nc] = VISITED;
                q.push({nr, nc});
            }
        }

        BeginDrawing();
        ClearBackground(Color{20, 20, 20, 255});

        for (int r = 0; r < ROWS; r++)
        {
            for (int c = 0; c < COLS; c++)
            {
                Color color = Color{45, 45, 45, 255};
                if (grid[r][c] == WALL)
                    color = Color{140, 140, 140, 255};
                if (grid[r][c] == VISITED)
                    color = Color{60, 100, 150, 255};
                if (grid[r][c] == PATH)
                    color = WHITE;
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