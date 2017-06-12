#ifndef PLAYER_H
#define PLAYER_H

#include "Global.h"

class Player
{
public:
    Player() {};
    virtual ~Player() {};


    virtual bool playRound(int grid[GAME_BOARD_GRID_SIZE][GAME_BOARD_GRID_SIZE], int piece[NUMBER_OF_PIECES_PER_ROUND], int x[NUMBER_OF_PIECES_PER_ROUND], int y[NUMBER_OF_PIECES_PER_ROUND]) = 0;
};

#endif // PLAYER_H