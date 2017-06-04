#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "Global.h"
#include "player.h"

#include <vector>


class AIPlayer : public Player
{
    struct Move {
        int piece[NUMBER_OF_PIECES_PER_ROUND];
        int x[NUMBER_OF_PIECES_PER_ROUND];
        int y[NUMBER_OF_PIECES_PER_ROUND];
        int moveScore;
        int numberOfLinesCleared;
        int **grid;
    };

public:
    AIPlayer();


    bool playRound(int grid[GAME_BOARD_GRID_SIZE][GAME_BOARD_GRID_SIZE], int piece[NUMBER_OF_PIECES_PER_ROUND], int x[NUMBER_OF_PIECES_PER_ROUND], int y[NUMBER_OF_PIECES_PER_ROUND]);


private:
    int calculateNumberOfOrderPermutations(int c);
    int** calculateOrderPermutations(int *p, int count);

    void calculateMoves(int pieces[NUMBER_OF_PIECES_PER_ROUND], int grid[GAME_BOARD_GRID_SIZE][GAME_BOARD_GRID_SIZE], std::vector<Move*> *moves);
    int processGrid(int **grid);
    void evaluateMove(Move *m);

};

#endif // AIPLAYER_H