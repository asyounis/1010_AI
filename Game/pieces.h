#ifndef PIECES_H
#define PIECES_H

#include <QWidget>
#include "Global.h"

class Pieces : public QWidget
{
    Q_OBJECT
public:
    explicit Pieces(QWidget *parent = nullptr);

    void setPosition(int x, int y);
    void setPiece(int p);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void drawGrid();
    void drawCells();

    int pGrid[5][5];
    int pWidth;
    int pHeight;


signals:

public slots:
};

#endif // PIECES_H