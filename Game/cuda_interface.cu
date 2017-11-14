#include <thrust/device_vector.h>
#include "Global.h"
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>    // For max()
#include <cuda.h>
#include <cuda_runtime.h>




// __global__
__device__
void getGridForPiece(int piece, int &width, int &height, int pGrid[5][5])
{
    // Clear the array
    memset(pGrid, 0, sizeof(pGrid[0][0]) * 5 * 5);

    if (piece == 0)
    {
        width = 1;
        height = 3;
        pGrid[0][0] = 1;
        pGrid[1][0] = 1;
        pGrid[2][0] = 1;
    }
    else if (piece == 1)
    {
        width = 3;
        height = 1;
        pGrid[0][0] = 1;
        pGrid[0][1] = 1;
        pGrid[0][2] = 1;
    }
    else if (piece == 2)
    {
        width = 3;
        height = 3;
        pGrid[0][0] = 1;
        pGrid[0][1] = 1;
        pGrid[0][2] = 1;
        pGrid[1][2] = 1;
        pGrid[2][2] = 1;
    }
    else if (piece == 3)
    {
        width = 3;
        height = 3;
        pGrid[0][0] = 1;
        pGrid[0][1] = 1;
        pGrid[0][2] = 1;
        pGrid[1][0] = 1;
        pGrid[2][0] = 1;
    }
    else if (piece == 4)
    {
        width = 3;
        height = 3;
        pGrid[0][0] = 1;
        pGrid[1][0] = 1;
        pGrid[2][0] = 1;
        pGrid[2][1] = 1;
        pGrid[2][2] = 1;
    }
    else if (piece == 5)
    {
        width = 3;
        height = 3;
        pGrid[0][2] = 1;
        pGrid[1][2] = 1;
        pGrid[2][0] = 1;
        pGrid[2][1] = 1;
        pGrid[2][2] = 1;
    }
    else if (piece == 6)
    {
        width = 1;
        height = 2;
        pGrid[0][0] = 1;
        pGrid[1][0] = 1;
    }
    else if (piece == 7)
    {
        width = 2;
        height = 1;
        pGrid[0][0] = 1;
        pGrid[0][1] = 1;
    }
    else if (piece == 8)
    {
        width = 2;
        height = 2;
        pGrid[0][0] = 1;
        pGrid[0][1] = 1;
        pGrid[1][0] = 1;
    }
    else if (piece == 9)
    {
        width = 2;
        height = 2;
        pGrid[0][0] = 1;
        pGrid[0][1] = 1;
        pGrid[1][1] = 1;
    }
    else if (piece == 10)
    {
        width = 2;
        height = 2;
        pGrid[0][1] = 1;
        pGrid[1][1] = 1;
        pGrid[1][0] = 1;
    }
    else if (piece == 11)
    {
        width = 2;
        height = 2;
        pGrid[0][0] = 1;
        pGrid[1][1] = 1;
        pGrid[1][0] = 1;
    }
    else if (piece == 12)
    {
        width = 1;
        height = 5;
        pGrid[0][0] = 1;
        pGrid[1][0] = 1;
        pGrid[2][0] = 1;
        pGrid[3][0] = 1;
        pGrid[4][0] = 1;
    }
    else if (piece == 13)
    {
        width = 5;
        height = 1;
        pGrid[0][0] = 1;
        pGrid[0][1] = 1;
        pGrid[0][2] = 1;
        pGrid[0][3] = 1;
        pGrid[0][4] = 1;
    }
    else if (piece == 14)
    {
        width = 1;
        height = 4;
        pGrid[0][0] = 1;
        pGrid[1][0] = 1;
        pGrid[2][0] = 1;
        pGrid[3][0] = 1;
    }
    else if (piece == 15)
    {
        width = 4;
        height = 1;
        pGrid[0][0] = 1;
        pGrid[0][1] = 1;
        pGrid[0][2] = 1;
        pGrid[0][3] = 1;
    }
    else if (piece == 16)
    {
        width = 1;
        height = 1;
        pGrid[0][0] = 1;
    }
    else if (piece == 17)
    {
        width = 2;
        height = 2;
        pGrid[0][0] = 1;
        pGrid[0][1] = 1;
        pGrid[1][0] = 1;
        pGrid[1][1] = 1;
    }
    else if (piece == 18)
    {
        width = 3;
        height = 3;
        pGrid[0][0] = 1;
        pGrid[0][1] = 1;
        pGrid[0][2] = 1;
        pGrid[1][0] = 1;
        pGrid[1][1] = 1;
        pGrid[1][2] = 1;
        pGrid[2][0] = 1;
        pGrid[2][1] = 1;
        pGrid[2][2] = 1;
    }
}

__device__
int processGrid(int grid[GAME_BOARD_GRID_SIZE][GAME_BOARD_GRID_SIZE], int x, int y, int pWidth, int pHeight)
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

__device__
int isempty(int *stack, int &top) {

    if (top == -1)
        return 1;
    else
        return 0;
}

__device__
int peek(int *stack, int &top)  {
    return stack[top];
}

__device__
int pop(int *stack, int &top)  {
    int data;

    if (!isempty(stack, top)) {
        data = stack[top];
        top = top - 1;
        return data;
    } else {
        return -1;
    }
}

__device__
int isfull(int *stack, int &top)  {

    if (top == 100)
        return 1;
    else
        return 0;
}

__device__
void push(int *stack, int &top, int data) {

    if (!isfull(stack, top)) {
        top = top + 1;
        stack[top] = data;
    }
}


// Finds the maximum area under the histogram represented
// by histogram.  See below article for details.
// http://www.geeksforgeeks.org/largest-rectangle-under-histogram/
__device__
int maxHist(int row[GAME_BOARD_GRID_SIZE])
{
    /// Create an empty stack. The stack holds indexes of
    // hist[] array/ The bars stored in stack are always
    // in increasing order of their heights.
    // std::stack<int> result;
    int result[100];
    int top = 0;



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
        if (isempty(result, top) || row[peek(result, top)] <= row[i])
            push(result, top, i++);

        else
        {
            // If this bar is lower than top of stack, then
            // calculate area of rectangle with stack top as
            // the smallest (or minimum height) bar. 'i' is
            // 'right index' for the top and element before
            // top in stack is 'left index'
            top_val = row[peek(result, top)];
            pop(result, top);
            area = top_val * i;

            if (!isempty(result, top))
                area = top_val * (i - peek(result, top) - 1 );
            max_area = max(area, max_area);
        }
    }

    // Now pop the remaining bars from stack and calculate area
    // with every popped bar as the smallest bar
    while (!isempty(result, top))
    {
        top_val = row[peek(result, top)];
        pop(result, top);
        area = top_val * i;
        if (!isempty(result, top))
            area = top_val * (i - peek(result, top) - 1 );

        max_area = max(area, max_area);
    }
    return max_area;
}

// Returns area of the largest rectangle with all 1s in A[][]
__device__
int maxRectangle(int A[GAME_BOARD_GRID_SIZE][GAME_BOARD_GRID_SIZE])
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
        result = max(result, maxHist(A[i]));
    }

    return result;
}

__device__
float evaluateMove(int grid[GAME_BOARD_GRID_SIZE][GAME_BOARD_GRID_SIZE], float heuristicCoeff[NUMBER_OF_HEURISTICS], int numberOfLinesCleared)
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
            if (grid[y][x] != 0)
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
            if (grid[y][x] != 0)
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
            if (((x - 1) >= 0) && (grid[y][x - 1] == 0))
            {
                // Do nothing
            }
            else if (((y - 1) >= 0) && (grid[y - 1][x] == 0))
            {
                // Do nothing
            }
            else if (((y + 1) < GAME_BOARD_GRID_SIZE) && (grid[y + 1][x] == 0))
            {
                // Do nothing
            }
            else if (((x + 1) < GAME_BOARD_GRID_SIZE) && (grid[y][x + 1] == 0))
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
    largestRectangleArea = maxRectangle(grid);

    float moveScore = 0;
    moveScore =  (heuristicCoeff[0] * (float)numberOfLinesCleared);
    moveScore += (heuristicCoeff[1] * (float)numberOfFreeLines);
    moveScore += (heuristicCoeff[2] * (float)numberOfHoles);
    moveScore += (heuristicCoeff[3] * (float)largestRectangleArea);
    moveScore += (heuristicCoeff[4] * (float)totalNumberOfLineClusters);

    return moveScore;
}



__global__
void calculateMoves(int *grid,
                    int piece[NUMBER_OF_PIECES_PER_ROUND],
                    float heuristicCoeff[NUMBER_OF_HEURISTICS],
                    int *x,
                    int *y,
                    float *score,
                    int *linesCleared)
{
    int threadIndex = blockIdx.x * blockDim.x + threadIdx.x;

    if (threadIndex >= (GAME_BOARD_GRID_SIZE * GAME_BOARD_GRID_SIZE))
    {
        for (int t = 0; t < NUMBER_OF_PIECES_PER_ROUND; t++)
        {
            x[threadIndex * NUMBER_OF_PIECES_PER_ROUND + t] = -1;
            y[threadIndex * NUMBER_OF_PIECES_PER_ROUND + t] = -1;
        }
        return;
    }


    return;

    score[threadIndex] = 0;
    linesCleared[threadIndex] = 0;


    int localGrid[GAME_BOARD_GRID_SIZE][GAME_BOARD_GRID_SIZE];
    for (int gX = 0; gX < GAME_BOARD_GRID_SIZE; gX++)
    {
        for (int gY = 0; gY < GAME_BOARD_GRID_SIZE; gY++)
        {
            localGrid[gY][gX] = grid[gY * GAME_BOARD_GRID_SIZE  + gX];
        }
    }


    int xPos[NUMBER_OF_PIECES_PER_ROUND];
    int yPos[NUMBER_OF_PIECES_PER_ROUND];

    int positionIndex = threadIndex;
    for (int i = 0; i < NUMBER_OF_PIECES_PER_ROUND; i++)
    {
        xPos[i] = positionIndex % GAME_BOARD_GRID_SIZE;
        positionIndex /= GAME_BOARD_GRID_SIZE;
        yPos[i] = positionIndex % GAME_BOARD_GRID_SIZE;
        positionIndex /= GAME_BOARD_GRID_SIZE;
    }

    // Get the piece data
    int pWidth = 0;
    int pHeight = 0;
    int pGrid[5][5];

    for (int i = 0; i < NUMBER_OF_PIECES_PER_ROUND; i++)
    {
        // Get the piece data
        getGridForPiece(piece[i], pWidth, pHeight, pGrid);

        bool isValidMove = true;

        // Check if it is a valid move
        for (int pX = 0; pX < pWidth; pX++)
        {
            for (int pY = 0; pY < pHeight; pY++)
            {
                if ((pGrid[pY][pX] == 1) && (localGrid[yPos[i] + pY][xPos[i] + pX] == 1))
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
            for (int t = 0; t < NUMBER_OF_PIECES_PER_ROUND; t++)
            {
                x[threadIndex * NUMBER_OF_PIECES_PER_ROUND + t] = -1;
                y[threadIndex * NUMBER_OF_PIECES_PER_ROUND + t] = -1;
            }
            return;
        }

        x[threadIndex * NUMBER_OF_PIECES_PER_ROUND + i] = xPos[i];
        y[threadIndex * NUMBER_OF_PIECES_PER_ROUND + i] = yPos[i];

        // Place the piece since valid
        for (int pX = 0; pX < pWidth; pX++)
        {
            for (int pY = 0; pY < pHeight; pY++)
            {
                localGrid[yPos[i] + pY][xPos[i] + pX] += pGrid[pY][pX];
            }
        }

        linesCleared[threadIndex] += processGrid(localGrid, xPos[i] , yPos[i], pWidth, pHeight);
    }

    score[threadIndex] =  evaluateMove(localGrid, heuristicCoeff, linesCleared[threadIndex]);
}

extern "C"
int launchCuda(int grid[GAME_BOARD_GRID_SIZE][GAME_BOARD_GRID_SIZE],
               int piece[NUMBER_OF_PIECES_PER_ROUND],
               float heuristicCoeff[NUMBER_OF_HEURISTICS],
               int moveX[NUMBER_OF_PIECES_PER_ROUND],
               int moveY[NUMBER_OF_PIECES_PER_ROUND]
              )
{
    int numberOfMoves = 1;
    for (int i = 0; i < NUMBER_OF_PIECES_PER_ROUND; i++)
    {
        numberOfMoves *= GAME_BOARD_GRID_SIZE * GAME_BOARD_GRID_SIZE;
    }


    int *x;
    int *y;
    float *score;
    int *linesCleared;

    x = (int*)malloc(numberOfMoves * NUMBER_OF_PIECES_PER_ROUND * sizeof(int));
    y = (int*)malloc(numberOfMoves * NUMBER_OF_PIECES_PER_ROUND * sizeof(int));
    score = (float*)malloc(numberOfMoves * sizeof(float));
    linesCleared = (int*)malloc(numberOfMoves * sizeof(int));

    int *d_x;
    int *d_y;
    float *d_score;
    int *d_linesCleared;

    cudaMalloc(&d_x, numberOfMoves * NUMBER_OF_PIECES_PER_ROUND * sizeof(int));
    cudaMalloc(&d_y, numberOfMoves * NUMBER_OF_PIECES_PER_ROUND * sizeof(int));
    cudaMalloc(&d_score, numberOfMoves * sizeof(float));
    cudaMalloc(&d_linesCleared, numberOfMoves * sizeof(int));


    int *d_grid;
    int *d_piece;
    float *d_heuristicCoeff;

    cudaMalloc(&d_grid, GAME_BOARD_GRID_SIZE * GAME_BOARD_GRID_SIZE * sizeof(int));
    cudaMalloc(&d_piece, NUMBER_OF_PIECES_PER_ROUND * sizeof(int));
    cudaMalloc(&d_heuristicCoeff, NUMBER_OF_HEURISTICS * sizeof(float));

    // cudaMemcpy(d_grid, grid, GAME_BOARD_GRID_SIZE * GAME_BOARD_GRID_SIZE * sizeof(int), cudaMemcpyHostToDevice);
    // cudaMemcpy(d_piece, piece, NUMBER_OF_PIECES_PER_ROUND * sizeof(int), cudaMemcpyHostToDevice);
    // cudaMemcpy(d_heuristicCoeff, heuristicCoeff, NUMBER_OF_HEURISTICS * sizeof(float), cudaMemcpyHostToDevice);


    // int threadsPerBlock = 128;

    // calculateMoves <<<(numberOfMoves / threadsPerBlock) + 1, threadsPerBlock>>>(d_grid,
    //                              d_piece,
    //                              d_heuristicCoeff,
    //                              d_x,
    //                              d_y,
    //                              d_score,
    //                              d_linesCleared);


    // cudaMemcpy(x, d_x, numberOfMoves * NUMBER_OF_PIECES_PER_ROUND * sizeof(int), cudaMemcpyDeviceToHost);
    // cudaMemcpy(y, d_y, numberOfMoves * NUMBER_OF_PIECES_PER_ROUND * sizeof(int), cudaMemcpyDeviceToHost);
    // cudaMemcpy(score, d_score, numberOfMoves * sizeof(float), cudaMemcpyDeviceToHost);
    // cudaMemcpy(linesCleared, d_linesCleared, numberOfMoves * sizeof(int), cudaMemcpyDeviceToHost);


    // int bestMove = -1;
    // float bestMoveScore = -10000000000;
    // for (int i = 0; i < numberOfMoves; i++)
    // {
    //     if (x[i * NUMBER_OF_PIECES_PER_ROUND] == -1)
    //     {
    //         continue;
    //     }

    //     if (score[i] > bestMoveScore)
    //     {
    //         bestMoveScore = score[i];
    //         bestMove = i;
    //     }
    // }

    // if (bestMove == -1)
    // {
    //     cudaFree(d_grid);
    //     cudaFree(d_piece);
    //     cudaFree(d_heuristicCoeff);
    //     cudaFree(d_x);
    //     cudaFree(d_y);
    //     cudaFree(d_score);
    //     cudaFree(d_linesCleared);

    //     free(x);
    //     free(y);
    //     free(score);
    //     free(linesCleared);

    //     return 0;
    // }


    // for (int i = 0 ; i < NUMBER_OF_PIECES_PER_ROUND; i++)
    // {
    //     moveX[i] = x[bestMove * NUMBER_OF_PIECES_PER_ROUND + i];
    //     moveY[i] = y[bestMove * NUMBER_OF_PIECES_PER_ROUND + i];
    // }



    cudaFree(d_grid);
    cudaFree(d_piece);
    cudaFree(d_heuristicCoeff);
    cudaFree(d_x);
    cudaFree(d_y);
    cudaFree(d_score);
    cudaFree(d_linesCleared);

    free(x);
    free(y);
    free(score);
    free(linesCleared);

    return 1;
}