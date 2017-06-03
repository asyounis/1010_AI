#include "pieces.h"
#include "game.h"

#include <QPainter>

Pieces::Pieces(QWidget *parent) : QWidget(parent)
{
    for (int x = 0; x < 5; x++)
    {
        for (int y = 0; y < 5; y++)
        {
            pGrid[x][y] = 0;
        }
    }
}

void Pieces::setPosition(int x, int y)
{
    this->setGeometry(x, y, PIECES_WIDTH, PIECES_HEIGHT);
}


void Pieces::setPiece(int p)
{
    for (int x = 0; x < 5; x++)
    {
        for (int y = 0; y < 5; y++)
        {
            pGrid[x][y] = 0;
        }
    }

    // Get the piece data
    Game::getGridForPiece(p, pWidth, pHeight, pGrid);

    // Update the rendering
    update();
}

void Pieces::paintEvent(QPaintEvent * /* event */)
{
    drawCells();
    drawGrid();
}

void Pieces::drawCells()
{

    QBrush brush = QBrush(QColor(255, 0, 0));
    QPen pen = QPen(QColor(255, 0, 0));

    QPainter painter(this);
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.setRenderHint(QPainter::Antialiasing, true);

    const int cellWidth = PIECES_WIDTH / 5;
    const int cellHeight = PIECES_HEIGHT / 5;

    for (int x = 0; x < 5; x++)
    {
        for (int y = 0; y < 5; y++)
        {
            if (pGrid[x][y] != 0)
            {
                QRect rect(x * cellWidth, y * cellHeight, cellWidth, cellHeight);
                painter.drawRect(rect);
            }
        }
    }
}



void Pieces::drawGrid()
{
    // Make a black pen
    QPen pen = QPen(QColor(0, 0, 0));

    // Create a painter and set the correct parameters
    QPainter painter(this);
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // Draw the Column Lines
    int xPos = 0;
    for (int x = 0; x < (5 + 1); x++)
    {
        painter.drawLine(xPos, 0, xPos, PIECES_HEIGHT);
        xPos += (PIECES_WIDTH / 5);
    }

    // Draw the Row Lines
    int yPos = 0;
    for (int y = 0; y < (5 + 1); y++)
    {
        painter.drawLine(0, yPos, PIECES_WIDTH, yPos);
        yPos += (PIECES_HEIGHT / 5);
    }
}