#include "window.h"
#include "game.h"
#include "aiplayer.h"
#include <QApplication>
#include <iostream>
#include <thread>

Game *game;

void gamePlay() {
    game->play();
}


int main(int argc, char *argv[])
{
    std::cout << "Starting... \n" ;//<< std::endl();

    QApplication a(argc, argv);
    Window window;
    window.show();


    AIPlayer player =  AIPlayer();
    game = new Game(&player, &window);

    // std::thread t1(gamePlay);   

    return a.exec();
}
