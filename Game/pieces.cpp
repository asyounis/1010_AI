#include "pieces.h"

#include <QPainter>

Pieces::Pieces(QWidget *parent) : QWidget(parent)
{
}

void Pieces::setPosition(int x, int y)
{
    this->setGeometry(x, y, PIECES_WIDTH, PIECES_HEIGHT);
}


void Pieces::paintEvent(QPaintEvent * /* event */)
{
    // drawGameCells();
    drawGameGrid();
}




void Pieces::drawGameGrid()
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
        xPos += (PIECES_WIDTH / 10);
    }

    // Draw the Row Lines
    int yPos = 0;
    for (int y = 0; y < (5 + 1); y++)
    {
        painter.drawLine(0, yPos, PIECES_WIDTH, yPos);
        yPos += (PIECES_HEIGHT / 10);
    }
}