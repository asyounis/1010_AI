#ifndef GAME_H
#define GAME_H

#include "Global.h"
#include <cstring>


class Player;
class Window;

class Game
{
public:

    Game(Player *p, Window *w, bool isTraining = false);
    ~Game();
    // Game(Player *p);

    static void getGridForPiece(int piece, int &width, int &height, int pGrid[5][5])
    {

        // Clear the array
        memset(pGrid, 0, sizeof(pGrid[0][0]) * 5 * 5);

        // Allocate memory for the moves
        // int **pGrid = new int*[5];
        // pGrid[0] = new int[5];
        // pGrid[1] = new int[5];
        // pGrid[2] = new int[5];
        // pGrid[3] = new int[5];
        // pGrid[4] = new int[5];

        // Make sure the memory is cleared
        // // memset(pGrid[0], 0, sizeof(int) * 5);
        // memset(pGrid[1], 0, sizeof(int) * 5);
        // memset(pGrid[2], 0, sizeof(int) * 5);
        // memset(pGrid[3], 0, sizeof(int) * 5);
        // memset(pGrid[4], 0, sizeof(int) * 5);

        if (piece == 0)
        {
            width = 1;
            height = 3;
            pGrid[0][0] = 1;
            pGrid[1][0] = 1;
            pGrid[2][0] = 1;
        }
        else if (piece == 1)
        {
            width = 3;
            height = 1;
            pGrid[0][0] = 1;
            pGrid[0][1] = 1;
            pGrid[0][2] = 1;
        }
        else if (piece == 2)
        {
            width = 3;
            height = 3;
            pGrid[0][0] = 1;
            pGrid[0][1] = 1;
            pGrid[0][2] = 1;
            pGrid[1][2] = 1;
            pGrid[2][2] = 1;
        }
        else if (piece == 3)
        {
            width = 3;
            height = 3;
            pGrid[0][0] = 1;
            pGrid[0][1] = 1;
            pGrid[0][2] = 1;
            pGrid[1][0] = 1;
            pGrid[2][0] = 1;
        }
        else if (piece == 4)
        {
            width = 3;
            height = 3;
            pGrid[0][0] = 1;
            pGrid[1][0] = 1;
            pGrid[2][0] = 1;
            pGrid[2][1] = 1;
            pGrid[2][2] = 1;
        }
        else if (piece == 5)
        {
            width = 3;
            height = 3;
            pGrid[0][2] = 1;
            pGrid[1][2] = 1;
            pGrid[2][0] = 1;
            pGrid[2][1] = 1;
            pGrid[2][2] = 1;
        }
        else if (piece == 6)
        {
            width = 1;
            height = 2;
            pGrid[0][0] = 1;
            pGrid[1][0] = 1;
        }
        else if (piece == 7)
        {
            width = 2;
            height = 1;
            pGrid[0][0] = 1;
            pGrid[0][1] = 1;
        }
        else if (piece == 8)
        {
            width = 2;
            height = 2;
            pGrid[0][0] = 1;
            pGrid[0][1] = 1;
            pGrid[1][0] = 1;
        }
        else if (piece == 9)
        {
            width = 2;
            height = 2;
            pGrid[0][0] = 1;
            pGrid[0][1] = 1;
            pGrid[1][1] = 1;
        }
        else if (piece == 10)
        {
            width = 2;
            height = 2;
            pGrid[0][1] = 1;
            pGrid[1][1] = 1;
            pGrid[1][0] = 1;
        }
        else if (piece == 11)
        {
            width = 2;
            height = 2;
            pGrid[0][0] = 1;
            pGrid[1][1] = 1;
            pGrid[1][0] = 1;
        }
        else if (piece == 12)
        {
            width = 1;
            height = 5;
            pGrid[0][0] = 1;
            pGrid[1][0] = 1;
            pGrid[2][0] = 1;
            pGrid[3][0] = 1;
            pGrid[4][0] = 1;
        }
        else if (piece == 13)
        {
            width = 5;
            height = 1;
            pGrid[0][0] = 1;
            pGrid[0][1] = 1;
            pGrid[0][2] = 1;
            pGrid[0][3] = 1;
            pGrid[0][4] = 1;
        }
        else if (piece == 14)
        {
            width = 1;
            height = 4;
            pGrid[0][0] = 1;
            pGrid[1][0] = 1;
            pGrid[2][0] = 1;
            pGrid[3][0] = 1;
        }
        else if (piece == 15)
        {
            width = 4;
            height = 1;
            pGrid[0][0] = 1;
            pGrid[0][1] = 1;
            pGrid[0][2] = 1;
            pGrid[0][3] = 1;
        }
        else if (piece == 16)
        {
            width = 1;
            height = 1;
            pGrid[0][0] = 1;
        }
        else if (piece == 17)
        {
            width = 2;
            height = 2;
            pGrid[0][0] = 1;
            pGrid[0][1] = 1;
            pGrid[1][0] = 1;
            pGrid[1][1] = 1;
        }
        else if (piece == 18)
        {
            width = 3;
            height = 3;
            pGrid[0][0] = 1;
            pGrid[0][1] = 1;
            pGrid[0][2] = 1;
            pGrid[1][0] = 1;
            pGrid[1][1] = 1;
            pGrid[1][2] = 1;
            pGrid[2][0] = 1;
            pGrid[2][1] = 1;
            pGrid[2][2] = 1;
        }
        // return pGrid;
    }

    void play();
    int getNumberOfLinesCleared();

private:
    int grid[GAME_BOARD_GRID_SIZE][GAME_BOARD_GRID_SIZE];
    Player *player;
    Window *window;
    int score;
    int numberOfLinesCleared;
    bool isTraining;
    int numberOfPiecesPlayed;




    void clearGrid();
    void generatePieces(int *piece);
};

#endif // GAME_H