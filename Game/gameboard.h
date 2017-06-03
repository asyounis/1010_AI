#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "Global.h"
#include <QWidget>


class GameBoard : public QWidget
{
    Q_OBJECT
public:
    explicit GameBoard(QWidget *parent = nullptr);

    void setGrid(int gridIn[GAME_BOARD_GRID_SIZE][GAME_BOARD_GRID_SIZE]);

protected:
    void paintEvent(QPaintEvent *event) override;
    
private:
    void drawGameGrid();
    void drawGameCells();

    int grid[GAME_BOARD_GRID_SIZE][GAME_BOARD_GRID_SIZE];

signals:

public slots:
};

#endif // GAMEBOARD_H