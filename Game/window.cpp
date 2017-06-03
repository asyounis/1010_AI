#include "window.h"
#include "gameboard.h"
#include "Global.h"
#include "pieces.h"

#include <QPainter>
#include <QGridLayout>

#include <iostream>


Window::Window(QWidget *parent) : QWidget(parent)
{
    // Set the size of the main window
    this->setFixedSize(QSize(WINDOW_WIDTH, WINDOW_HEIGHT));

    // Add the game board to the window
    gameBoard = new GameBoard(this);


    int spacing = WINDOW_WIDTH - (NUMBER_OF_PIECES_PER_ROUND * PIECES_WIDTH);
    spacing /= (NUMBER_OF_PIECES_PER_ROUND + 1);


    int xPos = spacing;
    for (int i = 0; i < NUMBER_OF_PIECES_PER_ROUND; i++)
    {
        piece[i] = new Pieces(this);
        piece[i]->setPosition(xPos, 350);
        piece[i]->update();
        xPos += spacing + PIECES_WIDTH;
    }
}




void Window::renderPieces(int pieces[NUMBER_OF_PIECES_PER_ROUND])
{
    for (int i = 0; i < NUMBER_OF_PIECES_PER_ROUND; i++)
    {
        piece[i]->setPiece(pieces[i]);
        piece[i]->update();
    }
}


void Window::renderGrid(int grid[GAME_BOARD_GRID_SIZE][GAME_BOARD_GRID_SIZE])
{
    gameBoard->setGrid(grid);
    gameBoard->update();
}


void Window::paintEvent(QPaintEvent * /* event */)
{
    // std::cout << "Rendering \n";

    // QRect rect(10, 20, 80, 60);


    // QBrush brush = QBrush(QColor(255,0,0));
    // QPen pen = QPen(QColor(0,0,0));

    // QPainter painter(this);
    // painter.setPen(pen);
    // painter.setBrush(brush);
    // painter.setRenderHint(QPainter::Antialiasing, true);

    // painter.drawRect(rect);

    // painter.setRenderHint(QPainter::Antialiasing, false);
    // painter.setPen(palette().dark().color());
    // painter.setBrush(Qt::NoBrush);
    // painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
}
