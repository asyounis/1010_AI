#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include "Global.h"

class GameBoard;

class Window : public QWidget
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = nullptr);

    void renderPieces(int pieces[NUMBER_OF_PIECES_PER_ROUND]);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    GameBoard *gameBoard;  // Main gameboard


signals:

public slots:
};

#endif // WINDOW_H