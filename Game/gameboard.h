#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>

class GameBoard : public QWidget
{
    Q_OBJECT
public:
    explicit GameBoard(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;


private:
    void drawGameGrid();
    void drawGameCells();

signals:

public slots:
};

#endif // GAMEBOARD_H