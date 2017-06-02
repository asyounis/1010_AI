#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "Global.h"
#include "player.h"

// class Player;

class AIPlayer : public Player
{
public:
    AIPlayer();


    void playRound(int grid[GAME_BOARD_GRID_SIZE][GAME_BOARD_GRID_SIZE], int piece[NUMBER_OF_PIECES_PER_ROUND], int x[NUMBER_OF_PIECES_PER_ROUND], int y[NUMBER_OF_PIECES_PER_ROUND]);
};

#endif // AIPLAYER_H