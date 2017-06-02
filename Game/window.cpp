#include "window.h"
#include "gameboard.h"
#include "Global.h"

#include <QPainter>
#include <QGridLayout>

#include <iostream>


Window::Window(QWidget *parent) : QWidget(parent)
{
    // Set the size of the main window
    this->setFixedSize(QSize(WINDOW_WIDTH, WINDOW_HEIGHT));

    // Add the game board to the window
    gameBoard = new GameBoard(this);
}




void Window::renderPieces(int pieces[NUMBER_OF_PIECES_PER_ROUND])
{

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
