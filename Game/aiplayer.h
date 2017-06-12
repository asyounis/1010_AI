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
        float moveScore;
        int numberOfLinesCleared;
        int grid[GAME_BOARD_GRID_SIZE][GAME_BOARD_GRID_SIZE];
    };

public:
    AIPlayer();
    AIPlayer(float heuristicCoeff[NUMBER_OF_HEURISTICS]);

    ~AIPlayer();

    bool playRound(int grid[GAME_BOARD_GRID_SIZE][GAME_BOARD_GRID_SIZE], int piece[NUMBER_OF_PIECES_PER_ROUND], int x[NUMBER_OF_PIECES_PER_ROUND], int y[NUMBER_OF_PIECES_PER_ROUND]);


private:
    int calculateNumberOfOrderPermutations(int c);
    int** calculateOrderPermutations(int *p, int count);

    std::vector<AIPlayer::Move*>* calculateMoves(int pieces[NUMBER_OF_PIECES_PER_ROUND], int grid[GAME_BOARD_GRID_SIZE][GAME_BOARD_GRID_SIZE]);
    int processGrid(int grid[GAME_BOARD_GRID_SIZE][GAME_BOARD_GRID_SIZE], int x, int y, int pWidth, int pHeight);
    void evaluateMove(Move *m);


    int maxRectangle(int A[GAME_BOARD_GRID_SIZE][GAME_BOARD_GRID_SIZE]);
    int maxHist(int row[GAME_BOARD_GRID_SIZE]);

    float heuristicCoeff[NUMBER_OF_HEURISTICS];

};

#endif // AIPLAYER_H