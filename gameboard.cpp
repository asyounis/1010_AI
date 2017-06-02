#include "gameboard.h"
#include <QPainter>
#include "Global.h"


GameBoard::GameBoard(QWidget *parent) : QWidget(parent)
{
    // Set the position and the size of the game board
    this->setGeometry((WINDOW_WIDTH - GAME_BOARD_WIDTH) / 2, 10, GAME_BOARD_WIDTH, GAME_BOARD_HEIGHT);
}

void GameBoard::paintEvent(QPaintEvent * /* event */)
{
    drawGameCells();
    drawGameGrid();
}


void GameBoard::drawGameCells()
{

    int grid[GAME_BOARD_GRID_SIZE][GAME_BOARD_GRID_SIZE];

    for (int x = 0; x < GAME_BOARD_GRID_SIZE; x++)
    {
        for (int y = 0; y < GAME_BOARD_GRID_SIZE; y++)
        {
            grid[x][y] = 0;
        }
    }

    for (int i = 0; i < GAME_BOARD_GRID_SIZE; i++)
    {
        grid[i][i] = 1;
    }


    QBrush brush = QBrush(QColor(255, 0, 0));
    QPen pen = QPen(QColor(255, 0, 0));

    QPainter painter(this);
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.setRenderHint(QPainter::Antialiasing, true);

    const int cellWidth = GAME_BOARD_WIDTH / GAME_BOARD_GRID_SIZE;
    const int cellHeight = GAME_BOARD_HEIGHT / GAME_BOARD_GRID_SIZE;

    for (int x = 0; x < GAME_BOARD_GRID_SIZE; x++)
    {
        for (int y = 0; y < GAME_BOARD_GRID_SIZE; y++)
        {
            if (grid[x][y] != 0)
            {
                QRect rect(x * cellWidth, y * cellHeight, cellWidth, cellHeight);
                painter.drawRect(rect);
            }
        }
    }
}

void GameBoard::drawGameGrid()
{
    // Make a black pen
    QPen pen = QPen(QColor(0, 0, 0));

    // Create a painter and set the correct parameters
    QPainter painter(this);
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // Draw the Column Lines
    int xPos = 0;
    for (int x = 0; x < (GAME_BOARD_GRID_SIZE + 1); x++)
    {
        painter.drawLine(xPos, 0, xPos, GAME_BOARD_HEIGHT);
        xPos += (GAME_BOARD_WIDTH / 10);
    }

    // Draw the Row Lines
    int yPos = 0;
    for (int y = 0; y < (GAME_BOARD_GRID_SIZE + 1); y++)
    {
        painter.drawLine(0, yPos, GAME_BOARD_WIDTH, yPos);
        yPos += (GAME_BOARD_HEIGHT / 10);
    }
}