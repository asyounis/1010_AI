#include "window.h"
#include "game.h"
#include "aiplayer.h"
#include <QApplication>
#include <iostream>


int main(int argc, char *argv[])
{
    std::cout << "Starting... \n" ;//<< std::endl();

    QApplication a(argc, argv);
    Window window;
    window.show();


    AIPlayer player =  AIPlayer();
    Game game = Game(&player);
    
    game.play();

    return a.exec();
}
