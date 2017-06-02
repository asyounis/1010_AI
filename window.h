#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

class GameBoard;

class Window : public QWidget
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    GameBoard *gameBoard;  // Main gameboard


signals:

public slots:
};

#endif // WINDOW_H