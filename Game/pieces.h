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
    
protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void drawGameGrid();
    // void drawGameCells();

signals:

public slots:
};

#endif // PIECES_H