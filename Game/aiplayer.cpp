#include "aiplayer.h"
#include "game.h"

#include <iostream>
#include <stack>
#include <cstring>




AIPlayer::AIPlayer(float heuristicCoeff[NUMBER_OF_HEURISTICS])
{
    memcpy(this->heuristicCoeff, heuristicCoeff, sizeof(float) * NUMBER_OF_HEURISTICS);
}

AIPlayer::AIPlayer()
{
    for (int i = 0; i < NUMBER_OF_HEURISTICS; i++)
    {
        heuristicCoeff[i] = 1.0 / (float)NUMBER_OF_HEURISTICS;
    }
}

AIPlayer::~AIPlayer() {}

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


    int totalNumberOfMoves = 0;
    std::vector<std::vector<Move*>*> vectOfMoves = std::vector<std::vector<Move*>*>();

    for (size_t i = 0; i < permutationsVector.size(); i++)
    {
        vectOfMoves.push_back(calculateMoves(permutationsVector.at(i), grid));
        delete [] permutationsVector.at(i);
        totalNumberOfMoves += vectOfMoves.at(i)->size();
    }

    if (totalNumberOfMoves == 0)
    {
        for (size_t i = 0; i < vectOfMoves.size(); i++)
        {
            delete vectOfMoves.at(i);
        }

        return false;
    }


    int bestMoveScore = 0;
    int bestMoveIndex[2];
    bestMoveIndex[0] = 0;
    bestMoveIndex[1] = 0;

    for (size_t i = 0; i < vectOfMoves.size(); i++)
    {
        for (size_t m = 0; m < vectOfMoves.at(i)->size(); m++)
        {
            evaluateMove(vectOfMoves.at(i)->at(m));

            if (vectOfMoves.at(i)->at(m)->moveScore > bestMoveScore)
            {
                bestMoveIndex[0] = i;
                bestMoveIndex[1] = m;
            }
        }
    }

    for (int i = 0; i < NUMBER_OF_PIECES_PER_ROUND; i++)
    {
        piece[i] = vectOfMoves.at(bestMoveIndex[0])->at(bestMoveIndex[1])->piece[i];
        x[i] = vectOfMoves.at(bestMoveIndex[0])->at(bestMoveIndex[1])->x[i];
        y[i] = vectOfMoves.at(bestMoveIndex[0])->at(bestMoveIndex[1])->y[i];
    }


    for (size_t i = 0; i < vectOfMoves.size(); i++)
    {
        for (size_t m = 0; m < vectOfMoves.at(i)->size(); m++)
        {
            delete vectOfMoves.at(i)->at(m);
        }

        delete vectOfMoves.at(i);
    }

    return true;
}

int AIPlayer::processGrid(int grid[GAME_BOARD_GRID_SIZE][GAME_BOARD_GRID_SIZE], int x, int y, int pWidth, int pHeight)
{
    int linesCleared = 0;

    bool rowsToClear[GAME_BOARD_GRID_SIZE];
    bool columnsToClear[GAME_BOARD_GRID_SIZE];

    for (int i = y; i < y + pHeight; i++)
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

    for (int i = x; i < x + pWidth; i++)
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

    for (int i = y; i < y + pHeight; i++)
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

    for (int i = x; i < x + pWidth; i++)
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

std::vector<AIPlayer::Move*>* AIPlayer::calculateMoves(int pieces[NUMBER_OF_PIECES_PER_ROUND], int origGrid[GAME_BOARD_GRID_SIZE][GAME_BOARD_GRID_SIZE])//,  std::vector<Move*> **moves)
{

    // Make an initial empty move
    Move  *initMove = new Move();

    // Clear everything
    initMove->moveScore = 0;
    initMove->numberOfLinesCleared = 0;

    // Copy the data into the init piece
    memcpy(initMove->piece, pieces, sizeof(int) * NUMBER_OF_PIECES_PER_ROUND);
    memcpy(initMove->grid, origGrid, sizeof(int) * GAME_BOARD_GRID_SIZE * GAME_BOARD_GRID_SIZE);

    // Create a vector of moves
    std::vector<Move*> *moveTmp = new std::vector<Move*>();

    // Insert the init piece
    moveTmp->push_back(initMove);

    // Do all additional pieces
    for (int i = 0; i < NUMBER_OF_PIECES_PER_ROUND; i++)
    {
        // Create a vector of new moves to use
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
                            if ((pGrid[pY][pX] == 1) && (currentMove->grid[piecePlacementY + pY][piecePlacementX + pX] == 1))
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

                    // Move on if it is not a valid move
                    if (!isValidMove)
                    {
                        continue;
                    }

                    // Create a new move
                    Move  *newMove = new Move(*currentMove);

                    // Copy the data over
                    newMove->numberOfLinesCleared = currentMove->numberOfLinesCleared;
                    memcpy(newMove->piece, currentMove->piece, sizeof(int) * NUMBER_OF_PIECES_PER_ROUND);
                    memcpy(newMove->grid, currentMove->grid, sizeof(int) * GAME_BOARD_GRID_SIZE * GAME_BOARD_GRID_SIZE);

                    // Set the piece position for this piece
                    newMove->x[i] = piecePlacementX;
                    newMove->y[i] = piecePlacementY;

                    // Place the piece since valid
                    for (int pX = 0; pX < pWidth; pX++)
                    {
                        for (int pY = 0; pY < pHeight; pY++)
                        {
                            newMove->grid[piecePlacementY + pY][piecePlacementX + pX] += pGrid[pY][pX];
                        }
                    }

                    // Get the number of cleared lines and process the grid
                    newMove->numberOfLinesCleared += processGrid(newMove->grid, piecePlacementX , piecePlacementY, pWidth, pHeight);

                    // Add the piece into the move temp for the next round
                    moveTmp->push_back(newMove);
                }
            }

            delete movetmpOrig->at(m);
        }

        delete movetmpOrig;
    }


    // moves->insert(moves->end(), moveTmp->begin(), moveTmp->end());

    // *moves = moveTmp;
    return moveTmp;

    // moveTmp->clear();
    // delete moveTmp;
}

void AIPlayer::evaluateMove(Move *m)
{
    int numberOfHoles = 0;
    int numberOfFreeLines = 0;
    int largestRectangleArea = 0;
    int totalNumberOfLineClusters = 0;

    bool freeRows[GAME_BOARD_GRID_SIZE];
    bool freeColumns[GAME_BOARD_GRID_SIZE];

    // Check Lines
    for (int x = 0; x < GAME_BOARD_GRID_SIZE; x++)
    {
        bool isFreeLine = true;
        for (int y = 0; y < GAME_BOARD_GRID_SIZE; y++)
        {
            if (m->grid[y][x] != 0)
            {
                isFreeLine = false;
                break;
            }
        }

        if (isFreeLine)
        {
            numberOfFreeLines++;
            freeColumns[x] = false;
        }
        else
        {
            freeColumns[x] = true;
        }
    }

    // Check Lines
    for (int y = 0; y < GAME_BOARD_GRID_SIZE; y++)
    {
        bool isFreeLine = true;
        for (int x = 0; x < GAME_BOARD_GRID_SIZE; x++)
        {
            if (m->grid[y][x] != 0)
            {
                isFreeLine = false;
                break;
            }
        }

        if (isFreeLine)
        {
            numberOfFreeLines++;
            freeRows[y] = true;
        }
        else
        {
            freeRows[y] = false;
        }
    }

    bool isOnCluster = false;
    for (int i = 0; i < GAME_BOARD_GRID_SIZE; i++)
    {
        if (freeRows[i] == false)
        {
            if (!isOnCluster)
            {
                isOnCluster = true;
                totalNumberOfLineClusters++;
            }
        }
        else
        {
            isOnCluster = false;
        }
    }

    isOnCluster = false;
    for (int i = 0; i < GAME_BOARD_GRID_SIZE; i++)
    {
        if (freeColumns[i] == false)
        {
            if (!isOnCluster)
            {
                isOnCluster = true;
                totalNumberOfLineClusters++;
            }
        }
        else
        {
            isOnCluster = false;
        }
    }

    // Number of Holes
    for (int x = 0; x < GAME_BOARD_GRID_SIZE; x++)
    {
        for (int y = 0; y < GAME_BOARD_GRID_SIZE; y++)
        {
            if (((x - 1) >= 0) && (m->grid[y][x - 1] == 0))
            {
                // Do nothing
            }
            else if (((y - 1) >= 0) && (m->grid[y - 1][x] == 0))
            {
                // Do nothing
            }
            else if (((y + 1) < GAME_BOARD_GRID_SIZE) && (m->grid[y + 1][x] == 0))
            {
                // Do nothing
            }
            else if (((x + 1) < GAME_BOARD_GRID_SIZE) && (m->grid[y][x + 1] == 0))
            {
                // Do nothing
            }
            else
            {
                // Non of the tests passed so its a hall
                numberOfHoles++;
            }

        }
    }

    // Get the largest rectangle
    largestRectangleArea = maxRectangle(m->grid);

    m->moveScore =  (heuristicCoeff[0] * (float)m->numberOfLinesCleared);
    m->moveScore += (heuristicCoeff[1] * (float)numberOfFreeLines);
    m->moveScore += (heuristicCoeff[2] * (float)numberOfHoles);
    m->moveScore += (heuristicCoeff[3] * (float)largestRectangleArea);
    m->moveScore += (heuristicCoeff[4] * (float)totalNumberOfLineClusters);
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


// Finds the maximum area under the histogram represented
// by histogram.  See below article for details.
// http://www.geeksforgeeks.org/largest-rectangle-under-histogram/
int AIPlayer::maxHist(int row[GAME_BOARD_GRID_SIZE])
{
    // Create an empty stack. The stack holds indexes of
    // hist[] array/ The bars stored in stack are always
    // in increasing order of their heights.
    std::stack<int> result;

    int top_val;     // Top of stack

    int max_area = 0; // Initialize max area in current
    // row (or histogram)

    int area = 0;    // Initialize area with current top

    // Run through all bars of given histogram (or row)
    int i = 0;
    while (i < GAME_BOARD_GRID_SIZE)
    {
        // If this bar is higher than the bar on top stack,
        // push it to stack
        if (result.empty() || row[result.top()] <= row[i])
            result.push(i++);

        else
        {
            // If this bar is lower than top of stack, then
            // calculate area of rectangle with stack top as
            // the smallest (or minimum height) bar. 'i' is
            // 'right index' for the top and element before
            // top in stack is 'left index'
            top_val = row[result.top()];
            result.pop();
            area = top_val * i;

            if (!result.empty())
                area = top_val * (i - result.top() - 1 );
            max_area = std::max(area, max_area);
        }
    }

    // Now pop the remaining bars from stack and calculate area
    // with every popped bar as the smallest bar
    while (!result.empty())
    {
        top_val = row[result.top()];
        result.pop();
        area = top_val * i;
        if (!result.empty())
            area = top_val * (i - result.top() - 1 );

        max_area = std::max(area, max_area);
    }
    return max_area;
}

// Returns area of the largest rectangle with all 1s in A[][]
int AIPlayer::maxRectangle(int A[GAME_BOARD_GRID_SIZE][GAME_BOARD_GRID_SIZE])
{
    // Calculate area for first row and initialize it as
    // result
    int result = maxHist(A[0]);

    // iterate over row to find maximum rectangular area
    // considering each row as histogram
    for (int i = 1; i < GAME_BOARD_GRID_SIZE; i++)
    {

        for (int j = 0; j < GAME_BOARD_GRID_SIZE; j++)

            // if A[i][j] is 1 then add A[i -1][j]
            if (A[i][j]) A[i][j] += A[i - 1][j];


        // Update result if area with current row (as last row)
        // of rectangle) is more
        result = std::max(result, maxHist(A[i]));
    }

    return result;
}