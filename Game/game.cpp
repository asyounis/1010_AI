#include "game.h"
#include "player.h"
#include "window.h"

#include <cstring>
#include <ctime>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

Game::Game(Player *p, Window *w):
    player(p),
    window(w),
    score(0),
    numberOfLinesCleared(0)
{
    // Make sure the grid is empty
    clearGrid();

    // Seed the random number generator
    srand(time(NULL));

    if (window != NULL)
    {
        // Draw the game pieces for this round
        window->renderGrid(grid);
    }
}

Game::~Game()
{
    delete player;
}


// Game::Game(Player *p)
// {
// Game(p, NULL);
// }


void Game::clearGrid()
{
    // Set all the cells to 0
    for (int x = 0; x < GAME_BOARD_GRID_SIZE; x++)
    {
        for (int y = 0; y < GAME_BOARD_GRID_SIZE; y++)
        {
            grid[x][y] = 0;
        }
    }
}

void Game::generatePieces(int *piece)
{
    for (int i = 0; i < NUMBER_OF_PIECES_PER_ROUND; i++)
    {
        // piece[i] = 16;//rand() % NUMBER_OF_PIECE_TYPES;
        piece[i] = rand() % NUMBER_OF_PIECE_TYPES;
    }
}

void Game::play()
{
    while (true)
    {
        // std::cout << "Step\n";


        // Data for this round
        int pieces[NUMBER_OF_PIECES_PER_ROUND];
        int pX[NUMBER_OF_PIECES_PER_ROUND];
        int pY[NUMBER_OF_PIECES_PER_ROUND];

        // generate pieces if we need to
        generatePieces(pieces);


        if (window != NULL)
        {
            // Draw the game pieces for this round
            window->renderPieces(pieces);
        }

        // Get the move from the player
        bool hasMove = player->playRound(grid, pieces, pX, pY);

        // for (int i = 0; i < NUMBER_OF_PIECES_PER_ROUND; i++)
        // {
        //     std::cout << "(" << pieces[i] << "      " << pX[i] << ", " << pY[i] << "), ";
        // }
        // std::cout << "\n";


        if (!hasMove)
        {
            break;
        }

        for (int i = 0; i < NUMBER_OF_PIECES_PER_ROUND; i++)
        {
            int pWidth = 0;
            int pHeight = 0;
            int pGrid[5][5];

            // for (int i = 0; i < 5; i++)
            // {
            //     for (int j = 0; j < 5; j++)
            //     {
            //         pGrid[i][j] = 0;
            //     }
            // }

            // Get the piece data
            Game::getGridForPiece(pieces[i], pWidth, pHeight, pGrid);


            // std::cout << pieces[i] << "\n";
            // std::cout << pWidth << ", " << pHeight << "\n";


            for (int x = 0; x < pWidth; x++)
            {
                for (int y = 0; y < pHeight; y++)
                {
                    grid[pY[i] + y][pX[i] + x] += pGrid[y][x];

                    if (pGrid[y][x] == 1)
                    {
                        score += 1;
                    }
                }
            }

            bool rowsToClear[GAME_BOARD_GRID_SIZE];
            bool columnsToClear[GAME_BOARD_GRID_SIZE];

            for (int i = 0; i < GAME_BOARD_GRID_SIZE; i++)
            {
                bool didFindHole = false;

                for (int j = 0; j < GAME_BOARD_GRID_SIZE; j++)
                {
                    if (grid[i][j] == 0)
                    {
                        didFindHole = true;
                        break;
                    }
                }

                rowsToClear[i] = !didFindHole;
            }

            for (int i = 0; i < GAME_BOARD_GRID_SIZE; i++)
            {
                bool didFindHole = false;

                for (int j = 0; j < GAME_BOARD_GRID_SIZE; j++)
                {
                    if (grid[j][i] == 0)
                    {
                        didFindHole = true;
                        break;
                    }
                }

                columnsToClear[i] = !didFindHole;
            }

            for (int i = 0; i < GAME_BOARD_GRID_SIZE; i++)
            {
                if (!rowsToClear[i])
                {
                    continue;
                }

                numberOfLinesCleared++;
                score += GAME_BOARD_GRID_SIZE;

                for (int j = 0; j < GAME_BOARD_GRID_SIZE; j++)
                {
                    grid[i][j] = 0;
                }
            }

            for (int i = 0; i < GAME_BOARD_GRID_SIZE; i++)
            {
                if (!columnsToClear[i])
                {
                    continue;
                }

                numberOfLinesCleared++;
                score += GAME_BOARD_GRID_SIZE;

                for (int j = 0; j < GAME_BOARD_GRID_SIZE; j++)
                {
                    grid[j][i] = 0;
                }
            }
        }

        if (window != NULL)
        {
            // Draw the game pieces for this round
            window->renderGrid(grid);
        }



        // std::cout << "Score: " << score << "\n";

        // std::cout << "\n\n\n\n\n\n\n";
        // usleep(100000);
        // sleep(4);
        // break;
    }

    // std::cout << "Game Over" << "\n";
}

int Game::getNumberOfLinesCleared()
{
    return numberOfLinesCleared;
}
