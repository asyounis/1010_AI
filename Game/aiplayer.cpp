#include "aiplayer.h"
#include "game.h"

#include <iostream>





AIPlayer::AIPlayer()
{
    // int *tmp = new int[4];
    // tmp[0] = 1;
    // tmp[1] = 2;
    // tmp[2] = 3;
    // tmp[3] = 4;

    // int **out = calculateOrderPermutations(tmp, 4);

    // for (int i = 0; i < calculateNumberOfOrderPermutations(4); i++)
    // {
    //     for (int j = 0; j < 4; j++)
    //     {
    //         std::cout << out[i][j] << "   ";
    //     }
    //     std::cout << "\n";
    // }
}

void AIPlayer::playRound(int grid[GAME_BOARD_GRID_SIZE][GAME_BOARD_GRID_SIZE],
                         int piece[NUMBER_OF_PIECES_PER_ROUND],
                         int x[NUMBER_OF_PIECES_PER_ROUND],
                         int y[NUMBER_OF_PIECES_PER_ROUND])
{

    int numberOfPermutations = calculateNumberOfOrderPermutations(NUMBER_OF_PIECES_PER_ROUND);
    int **permutations = calculateOrderPermutations(piece, NUMBER_OF_PIECES_PER_ROUND);

    std::vector<move> moves = std::vector<move>();

    for (int i = 0; i < numberOfPermutations; i++)
    {
        calculateMoves(permutations[i], grid, moves);
    }
}



void AIPlayer::calculateMoves(int pieces[NUMBER_OF_PIECES_PER_ROUND], int origGrid[GAME_BOARD_GRID_SIZE][GAME_BOARD_GRID_SIZE],  std::vector<move> moves)
{
    std::vector<move> moveTmp = std::vector<move>();
    for (int i = 0; i < NUMBER_OF_PIECES_PER_ROUND; i++)
    {


        int pWidth = 0;
        int pHeight = 0;
        int pGrid[5][5];

        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                pGrid[i][j] = 0;
            }
        }

        // Get the piece data
        Game::getGridForPiece(pieces[i], pWidth, pHeight, pGrid);


        for (int x = 0; x < (GAME_BOARD_GRID_SIZE - pWidth); x++)
        {
            for (int y = 0; y < (GAME_BOARD_GRID_SIZE - pHeight); y++)
            {

                int grid[GAME_BOARD_GRID_SIZE][GAME_BOARD_GRID_SIZE]
                for (int j = 0; j < GAME_BOARD_GRID_SIZE; j++)
                {
                    for (int t = 0; t < GAME_BOARD_GRID_SIZE; t++)
                    {
                        grid[j][t] = origGrid[j][t]
                    }
                }



                bool isValidMove = true;

                // Check if it is a valid move
                for (int x1 = 0; x1 < pWidth; x1++)
                {
                    for (int y1 = 0; y1 < pHeight; y1++)
                    {
                        if (grid[y + y1][x + x1] == 1)
                        {
                            isValidMove == false;
                            break;
                        }

                        grid[y + y1][x + x1] += pGrid[y1][x1];

                    }

                    if (!isValidMove)
                    {
                        break;
                    }
                }

                if (!isValidMove)
                {
                    continue;
                }

                // Place the piece since valid
                for (int x1 = 0; x1 < pWidth; x1++)
                {
                    for (int y1 = 0; y1 < pHeight; y1++)
                    {
                        grid[y + y1][x + x1] += pGrid[y1][x1];
                    }

                    if (!isValidMove)
                    {
                        break;
                    }
                }


            }
        }

        for (int x1 = 0; x1 < pWidth; x1++)
        {
            for (int y1 = 0; y1 < pHeight; y1++)
            {
                grid[pY1[i] + y1][pX1[i] + x1] += pGrid[y1][x1];

                if (pGrid[y][x1] == 1)
                {
                    // score += 1;
                }
            }
        }
    }
}


void evaluateMove(move m)
{
    int numberOfHoles = 0;
    int numberOfFreeLines = 0;


    for (int x = 0; x < GAME_BOARD_GRID_SIZE; x++)
    {
        for (int y = 0; y < GAME_BOARD_GRID_SIZE; y++)
        {
            
        }
    }
}




int AIPlayer::calculateNumberOfOrderPermutations(int c)
{
    int fact = 1;
    for (int i = c; i > 0; i--)
    {
        fact *= i;
    }

    return fact;
}


int** AIPlayer::calculateOrderPermutations(int *p, int count)
{
    if (count == 1)
    {
        int **ret = new int*[1];
        ret[0] = new int[1];
        ret[0][0] = p[0];
        return ret;
    }

    int lowerPermNum = calculateNumberOfOrderPermutations(count - 1);

    int **ret = new int*[lowerPermNum * count];

    int permPos = 0;
    for (int i = 0; i < count; i++)
    {
        int *par = new int[count - 1];
        int c = 0;
        for (int j = 0; j < count; j++)
        {
            if (j == i)
            {
                continue;
            }
            par[c] = p[j];
            c++;
        }

        int **lowerPerms = calculateOrderPermutations(par, count - 1);
        delete [] par;


        for (int j = 0; j < lowerPermNum; j++)
        {
            ret[permPos] = new int[count];

            for (int t = 0; t < count - 1; t++)
            {
                ret[permPos][t] = lowerPerms[j][t];
            }

            ret[permPos][count - 1] = p[i];
            permPos++;

            delete [] lowerPerms[j];
        }

        delete [] lowerPerms;
    }

    return ret;
}