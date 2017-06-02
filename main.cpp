#include "window.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    std::cout << "Starting... \n" ;//<< std::endl();

    QApplication a(argc, argv);
    Window window;
    window.show();
    return a.exec();
}
