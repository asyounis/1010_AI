#include "game.h"
#include "player.h"
#include "window.h"

#include <cstring>
#include <ctime>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

Game::Game(Player *p, Window *w, bool isTraining):
    player(p),
    window(w),
    score(0),
    numberOfLinesCleared(0),
    isTraining(isTraining),
    numberOfPiecesPlayed(0)
{
    // Make sure the grid is empty
    clearGrid();

    // Seed the random number generator
    srand(time(NULL));

    // Make sure we only display when we have a window to display on
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
        numberOfPiecesPlayed++;
    }
}

void Game::play()
{
    while (true)
    {
        // Check limits for training
        if (isTraining && (numberOfPiecesPlayed > NUMBER_OF_TRAINING_PIECES))
        {
            break;
        }

        // Data for this round
        int pieces[NUMBER_OF_PIECES_PER_ROUND];
        int pX[NUMBER_OF_PIECES_PER_ROUND];
        int pY[NUMBER_OF_PIECES_PER_ROUND];

        // generate pieces if we need to
        generatePieces(pieces);

        // Make sure we only display when we have a window to display on
        if (window != NULL)
        {
            // Draw the game pieces for this round
            window->renderPieces(pieces);
        }

        // Get the move from the player
        bool hasMove = player->playRound(grid, pieces, pX, pY);

        // If there is no move available then just end the game;
        if (!hasMove)
        {
            break;
        }

        for (int i = 0; i < NUMBER_OF_PIECES_PER_ROUND; i++)
        {
            // Piece Data
            int pWidth = 0;
            int pHeight = 0;
            int pGrid[5][5];

            // Get the piece data
            Game::getGridForPiece(pieces[i], pWidth, pHeight, pGrid);

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

            for (int t = pY[i]; t < pY[i] + pHeight; t++)
            {
                bool didFindHole = false;

                for (int j = 0; j < GAME_BOARD_GRID_SIZE; j++)
                {
                    if (grid[t][j] == 0)
                    {
                        didFindHole = true;
                        break;
                    }
                }

                rowsToClear[t] = !didFindHole;
            }

            for (int t = pX[i]; t < pX[i] + pWidth; t++)
            {
                bool didFindHole = false;

                for (int j = 0; j < GAME_BOARD_GRID_SIZE; j++)
                {
                    if (grid[j][t] == 0)
                    {
                        didFindHole = true;
                        break;
                    }
                }

                columnsToClear[t] = !didFindHole;
            }

            for (int t = pY[i]; t < pY[i] + pHeight; t++)
            {
                if (!rowsToClear[t])
                {
                    continue;
                }

                numberOfLinesCleared++;
                score += GAME_BOARD_GRID_SIZE;

                for (int j = 0; j < GAME_BOARD_GRID_SIZE; j++)
                {
                    grid[t][j] = 0;
                }
            }

            for (int t = pX[i]; t < pX[i] + pWidth; t++)
            {
                if (!columnsToClear[t])
                {
                    continue;
                }

                numberOfLinesCleared++;
                score += GAME_BOARD_GRID_SIZE;

                for (int j = 0; j < GAME_BOARD_GRID_SIZE; j++)
                {
                    grid[j][t] = 0;
                }
            }
        }

        // Make sure we only display when we have a window to display on
        if (window != NULL)
        {
            // Draw the game pieces for this round
            window->renderGrid(grid);
        }

        // std::cout << "Score: " << score << "\n";
        // usleep(1000000);
    }

    // std::cout << "Game Over" << "\n";
}

int Game::getNumberOfLinesCleared()
{
    return numberOfLinesCleared;
}
