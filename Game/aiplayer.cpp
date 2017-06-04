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

bool AIPlayer::playRound(int grid[GAME_BOARD_GRID_SIZE][GAME_BOARD_GRID_SIZE],
                         int piece[NUMBER_OF_PIECES_PER_ROUND],
                         int x[NUMBER_OF_PIECES_PER_ROUND],
                         int y[NUMBER_OF_PIECES_PER_ROUND])
{

    int numberOfPermutations = calculateNumberOfOrderPermutations(NUMBER_OF_PIECES_PER_ROUND);
    int **permutations = calculateOrderPermutations(piece, NUMBER_OF_PIECES_PER_ROUND);

    std::vector<int*> permutationsVector = std::vector<int*>();

    for (int i = 0; i < numberOfPermutations; i++)
    {
        bool inAlready = false;
        for (size_t j = 0; j < permutationsVector.size(); j++)
        {
            if (permutationsVector.at(j) == permutations[i])
            {
                inAlready = true;
                break;
            }

            inAlready = true;
            for (int k = 0; k < NUMBER_OF_PIECES_PER_ROUND; k++)
            {
                if (permutations[i][k] != permutationsVector.at(j)[k])
                {
                    inAlready = false;
                    break;
                }
            }

            if (inAlready)
            {
                break;
            }
        }

        if (!inAlready)
        {
            permutationsVector.push_back(permutations[i]);
        }
    }

    delete [] permutations;

    std::vector<Move*> *moves = new std::vector<Move*>();

    for (size_t i = 0; i < permutationsVector.size(); i++)
    {
        calculateMoves(permutationsVector.at(i), grid, moves);
        delete [] permutationsVector.at(i);
    }

    if (moves->size() == 0)
    {
        delete moves;
        std::cout << "No Moves \n";
        return false;
    }

    std::cout << "Number of Moves: " << moves->size() << "\n";

    int bestMoveScore = 0;
    int bestMoveIndex = 0;
    for (size_t m = 0; m < moves->size(); m++)
    {
        evaluateMove(moves->at(m));

        if (moves->at(m)->moveScore > bestMoveScore)
        {
            bestMoveIndex = m;
        }
    }

    for (int i = 0; i < NUMBER_OF_PIECES_PER_ROUND; i++)
    {
        piece[i] = moves->at(bestMoveIndex)->piece[i];
        x[i] = moves->at(bestMoveIndex)->x[i];
        y[i] = moves->at(bestMoveIndex)->y[i];
    }




    for (size_t m = 0; m < moves->size(); m++)
    {
        for (int i = 0; i < GAME_BOARD_GRID_SIZE; i++)
        {
            delete [] moves->at(m)->grid[i];
        }
        delete [] moves->at(m)->grid;
        delete moves->at(m);
    }

    delete moves;
    return true;
}


int AIPlayer::processGrid(int **grid)
{

    int linesCleared = 0;

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

        linesCleared++;

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
        linesCleared++;

        for (int j = 0; j < GAME_BOARD_GRID_SIZE; j++)
        {
            grid[j][i] = 0;
        }
    }

    return linesCleared;
}

void AIPlayer::calculateMoves(int pieces[NUMBER_OF_PIECES_PER_ROUND], int origGrid[GAME_BOARD_GRID_SIZE][GAME_BOARD_GRID_SIZE],  std::vector<Move*> *moves)
{

    // Make an initial empty move
    Move  *initMove = new Move();

    // Clear everything
    initMove->moveScore = 0;
    initMove->numberOfLinesCleared = 0;
    initMove->grid = new int*[GAME_BOARD_GRID_SIZE];

    for (int i = 0; i < NUMBER_OF_PIECES_PER_ROUND; i++)
    {
        initMove->piece[i] = pieces[i];
    }


    for (int j = 0; j < GAME_BOARD_GRID_SIZE; j++)
    {
        // Allocate memory
        initMove->grid[j] = new int[GAME_BOARD_GRID_SIZE];

        // Copy into the new array;
        for (int t = 0; t < GAME_BOARD_GRID_SIZE; t++)
        {
            initMove->grid[j][t] = origGrid[j][t];
        }
    }


    std::vector<Move*> *moveTmp = new std::vector<Move*>();
    moveTmp->push_back(initMove);


    // Do all additional pieces
    for (int i = 0; i < NUMBER_OF_PIECES_PER_ROUND; i++)
    {
        std::vector<Move*> *movetmpOrig = moveTmp;
        moveTmp = new std::vector<Move*>();

        // Get the piece data
        int pWidth = 0;
        int pHeight = 0;
        int pGrid[5][5];

        // Get the piece data
        Game::getGridForPiece(pieces[i], pWidth, pHeight, pGrid);

        for (size_t m = 0; m < movetmpOrig->size(); m++)
        {
            Move  *currentMove = movetmpOrig->at(m);
            for (int piecePlacementX = 0; piecePlacementX < (GAME_BOARD_GRID_SIZE - pWidth + 1); piecePlacementX++)
            {
                for (int piecePlacementY = 0; piecePlacementY < (GAME_BOARD_GRID_SIZE - pHeight + 1); piecePlacementY++)
                {
                    bool isValidMove = true;

                    // Check if it is a valid move
                    for (int pX = 0; pX < pWidth; pX++)
                    {
                        for (int pY = 0; pY < pHeight; pY++)
                        {
                            if (currentMove->grid[piecePlacementY + pY][piecePlacementX + pX] == 1)
                            {
                                isValidMove = false;
                                break;
                            }
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

                    Move  *newMove = new Move(*currentMove);

                    for (int pI = 0;  pI < NUMBER_OF_PIECES_PER_ROUND; pI++)
                    {
                        newMove->piece[pI] = currentMove->piece[pI];
                    }

                    newMove->numberOfLinesCleared = currentMove->numberOfLinesCleared;
                    newMove->x[i] = piecePlacementX;
                    newMove->y[i] = piecePlacementY;

                    newMove->grid = new int*[GAME_BOARD_GRID_SIZE];

                    for (int j = 0; j < GAME_BOARD_GRID_SIZE; j++)
                    {
                        // Allocate memory
                        newMove->grid[j] = new int[GAME_BOARD_GRID_SIZE];

                        // Copy into the new array;
                        for (int t = 0; t < GAME_BOARD_GRID_SIZE; t++)
                        {
                            newMove->grid[j][t] = currentMove->grid[j][t];
                        }
                    }

                    // Place the piece since valid
                    for (int pX = 0; pX < pWidth; pX++)
                    {
                        for (int pY = 0; pY < pHeight; pY++)
                        {
                            newMove->grid[piecePlacementY + pY][piecePlacementX + pX] += pGrid[pY][pX];
                        }
                    }

                    newMove->numberOfLinesCleared += processGrid(newMove->grid);

                    moveTmp->push_back(newMove);
                }
            }

            for (int g = 0; g < GAME_BOARD_GRID_SIZE; g++)
            {
                delete [] currentMove->grid[g];
            }
            delete [] currentMove->grid;
            delete movetmpOrig.at(m);
        }

        delete movetmpOrig;
    }



    for (size_t m = 0; m < moveTmp->size(); m++)
    {
        moves->push_back(moveTmp->at(m));
    }

    delete moveTmp;
    moveTmp->clear();

}

void AIPlayer::evaluateMove(Move *m)
{

    m->moveScore = m->numberOfLinesCleared;

    // int numberOfHoles = 0;
    // int numberOfFreeLines = 0;


    // for (int x = 0; x < GAME_BOARD_GRID_SIZE; x++)
    // {
    //     for (int y = 0; y < GAME_BOARD_GRID_SIZE; y++)
    //     {

    //     }
    // }
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