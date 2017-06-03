#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include "Global.h"

class GameBoard;
class Pieces;

class Window : public QWidget
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = nullptr);

    void renderPieces(int pieces[NUMBER_OF_PIECES_PER_ROUND]);
    void renderGrid(int grid[GAME_BOARD_GRID_SIZE][GAME_BOARD_GRID_SIZE]);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    GameBoard *gameBoard;  // Main gameboard
    Pieces *piece[NUMBER_OF_PIECES_PER_ROUND];


signals:

public slots:
};

#endif // WINDOW_H