#include "game.h"
#include "player.h"
#include "window.h"

#include <cstring>
#include <ctime>
#include <stdlib.h>

Game::Game(Player *p, Window *w):
    player(p),
    window(w)
{
    // Make sure the grid is empty
    clearGrid();

    // Seed the random number generator
    srand(time(NULL));
}


Game::Game(Player *p)
{
    Game(p, NULL);
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
        piece[i] = rand() % NUMBER_OF_PIECE_TYPES;
    }
}

void Game::play()
{
    while (true)
    {
        // Data for this round
        int pieces[NUMBER_OF_PIECES_PER_ROUND];
        int x[NUMBER_OF_PIECES_PER_ROUND];
        int y[NUMBER_OF_PIECES_PER_ROUND];

        // generate pieces if we need to
        generatePieces(pieces);

        // Draw the game pieces for this round
        window->renderPieces(pieces);

        // Get the move from the player
        player->playRound(grid, pieces, x, y);
    }
}
