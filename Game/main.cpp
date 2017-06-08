#include "window.h"
#include "game.h"
#include "aiplayer.h"
#include <QApplication>
#include <iostream>
#include <thread>
#include <math.h>

Game *game;

#define POPULATION_SIZE (1000)
#define NUMBER_OF_THREADS (8)



float population[POPULATION_SIZE][NUMBER_OF_HEURISTICS];
int scores[POPULATION_SIZE];

void gamePlay(Game *game, int i) {

    // std::cout << "thread \n" ;
    game->play();
    scores[i] = game->getNumberOfLinesCleared();
    delete game;
}



int main(int argc, char *argv[])
{
    std::cout << "Starting... \n" ;

    QApplication a(argc, argv);
    Window window;
    window.show();

    float population[POPULATION_SIZE][NUMBER_OF_HEURISTICS];

    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        float mag = 0;
        for (int t = 0; t < NUMBER_OF_HEURISTICS; t++)
        {
            population[i][t] = (rand() % 2000000000) - 1000000000;

            mag += (population[i][t] * population[i][t]);
        }

        mag = sqrt(mag);

        for (int t = 0; t < NUMBER_OF_HEURISTICS; t++)
        {
            population[i][t] /= mag;
        }
    }



    // AIPlayer player =  AIPlayer(population[i]);
    // Game *game = new Game(&player, NULL);
    // std::thread *t1 = new std::thread(gamePlay, game);
    // threads.push_back(t1);


    for (int i = 0; i < POPULATION_SIZE; i += NUMBER_OF_THREADS)
    {
        std::cout << "i: " << i << "\n" ;



        int numberOfThreadsToLaunch = std::min(POPULATION_SIZE - i, NUMBER_OF_THREADS);

        std::thread t[numberOfThreadsToLaunch];


        // std::cout << "Threads Launched" << "\n" ;
        for (int j = 0; j < numberOfThreadsToLaunch; j++)
        {
            AIPlayer *player = new AIPlayer(population[i + j]);
            Game *game = new Game(player, NULL);
            t[j] = std::thread(gamePlay, game, i + j);
        }


        // std::cout << "Waiting for join" << "\n" ;

        for (int j = 0; j < numberOfThreadsToLaunch; j++)
        {
            // std::cout << "Pre j: " << i << "\n" ;
            t[j].join();
            // std::cout << "Post j: " << i << "\n" ;
        }
    }


// AIPlayer player =  AIPlayer();
// Game *game = new Game(&player, NULL);
// game = new Game(&player, &window);

// std::thread t1(gamePlay, game);

    return a.exec();
}
