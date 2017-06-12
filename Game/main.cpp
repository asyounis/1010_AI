#include "window.h"
#include "game.h"
#include "aiplayer.h"
#include <QApplication>
#include <iostream>
#include <thread>
#include <set>
#include <math.h>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <iomanip>
#include <mutex>
#include <sstream>
#include <ctime>
#include <chrono>


#define POPULATION_SIZE (1000)
#define RUNS_PER_PARAM_VECT (100)
#define SUBSET_OF_POPULATION_TO_SELECT (100)
#define NUMBER_OF_NEW_OFFSPRING (300)
#define NUMBER_OF_TUNING_RUNS (200)
#define NUMBER_OF_THREADS (7)
#define SAVE_FILE ("/Users/Ali/Desktop/1010_AI/Game/pop.txt")



float population[POPULATION_SIZE][NUMBER_OF_HEURISTICS];
int scores[POPULATION_SIZE];

int populationIndex = 0;
std::mutex populationIndexMutex;

void gamePlay() {

    while (true) {
        populationIndexMutex.lock();
        int i = populationIndex;
        populationIndex++;
        populationIndexMutex.unlock();

        if (i >= POPULATION_SIZE)
        {
            break;
        }

        if ((i % (POPULATION_SIZE / 100)) == 0)
        {
            std::cout << "i: " << i << "/" << POPULATION_SIZE << "\n";
        }

        scores[i] = 0;
        for (int j = 0; j < RUNS_PER_PARAM_VECT; j++)
        {
            AIPlayer *player = new AIPlayer(population[i]);
            Game *game = new Game(player, NULL, true);
            game->play();
            scores[i] += game->getNumberOfLinesCleared();
            delete game;
        }
    }
}

void gamePlay2(Game *game) {
    game->play();
}


std::vector<int> sort_indexes(int scores[POPULATION_SIZE]) {

    // initialize original index locations
    std::vector<int> idx(POPULATION_SIZE);
    iota(idx.begin(), idx.end(), 0);

    // sort indexes based on comparing values in v
    sort(idx.begin(), idx.end(), [scores](int i1, int i2) {return scores[i1] < scores[i2];});

    return idx;
}


void savePopulationToFile()
{

    std::remove(SAVE_FILE);

    std::ofstream myfile;
    myfile.open (SAVE_FILE);

    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        for (int j = 0; j < NUMBER_OF_HEURISTICS; j++)
        {
            myfile << std::setprecision(15) << population[i][j];

            if (j != NUMBER_OF_HEURISTICS - 1)
            {
                myfile << "  ";
            }
        }

        myfile << "\n";
    }

    myfile.close();
}


bool loadPopulationToFile()
{

    if (!(std::ifstream(SAVE_FILE)))
    {
        return false;
    }

    std::ifstream myfile;
    myfile.open (SAVE_FILE);

    int lineNumber = 0;

    std::string line;
    while (std::getline(myfile, line))
    {
        std::istringstream iss(line);


        for (int i = 0; i < NUMBER_OF_HEURISTICS; i++)
        {
            iss >> population[lineNumber][i];
        }

        lineNumber++;
    }

    myfile.close();

    return true;
}


void createNewPopulation()
{
    float newVect[NUMBER_OF_NEW_OFFSPRING][NUMBER_OF_HEURISTICS];

    for (int j = 0; j < NUMBER_OF_NEW_OFFSPRING; j++)
    {
        std::set<int> popSubSet;
        while (popSubSet.size() < SUBSET_OF_POPULATION_TO_SELECT)
        {
            int randSelection = rand() % POPULATION_SIZE;
            popSubSet.insert(randSelection);
        }

        int fittest1 = 0;
        int fittest2 = 0;

        std::set<int>::iterator it;
        for (it = popSubSet.begin(); it != popSubSet.end(); ++it)
        {
            int paramVectIndex = *it;
            if (scores[paramVectIndex] > scores[fittest1])
            {
                fittest1 = paramVectIndex;
            }
        }


        // popSubSet.erase(popSubSet.find(fittest1));



        if (fittest1 == 0)
        {
            fittest2 = 1;
        }

        for (it = popSubSet.begin(); it != popSubSet.end(); ++it)
        {
            int paramVectIndex = *it;

            if (paramVectIndex == fittest1)
            {
                continue;
            }

            if (scores[paramVectIndex] > scores[fittest2])
            {
                fittest2 = paramVectIndex;
            }
        }



        float mag = 0;
        for (int i = 0; i < NUMBER_OF_HEURISTICS; i++)
        {
            newVect[j][i] = (population[fittest1][i] * (float)scores[fittest1]) + (population[fittest2][i] * (float)scores[fittest2]);
            mag += (newVect[j][i] * newVect[j][i]);
        }

        if ((rand() % 100) < 10)
        {
            std::cout << "Mutating \n";

            int component = rand() % NUMBER_OF_HEURISTICS;
            float amount = rand() % 200000000;
            amount -= 100000000.0;
            amount /= 100000000.0;
            amount *= 0.2;
            // amount *= 0.002;

            mag -= (newVect[j][component] * newVect[j][component]);

            newVect[j][component] += newVect[j][component] * amount;

            mag += (newVect[j][component] * newVect[j][component]);
        }

        mag = sqrt(mag);

        for (int i = 0; i < NUMBER_OF_HEURISTICS; i++)
        {
            newVect[j][i] /= mag;
        }


        // for (int t = 0; t < NUMBER_OF_HEURISTICS; t++)
        // {
        //     // std::cout << population[2][t] << "    ";
        //         std::cout << newVect[j][t] << "    ";

        // }
        // std::cout << "\n";
    }


    std::vector<int> sortedIndices = sort_indexes(scores);

    for (int j = 0; j < NUMBER_OF_NEW_OFFSPRING; j++)
    {
        int index = sortedIndices.at(j);

        for (int i = 0; i < NUMBER_OF_HEURISTICS; i++)
        {
            population[index][i] =   newVect[j][i];
        }
    }

    savePopulationToFile();
}

void printBestParamVector()
{
    int fittest = 0;
    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        if (scores[i] > scores[fittest])
        {
            fittest = i;
        }
    }

    std::cout << "\n\n\n\n\n";
    for (int i = 0; i < NUMBER_OF_HEURISTICS; i++)
    {
        std::cout << population[fittest][i] << "\n";
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Window window;
    window.show();



    if (!loadPopulationToFile())
    {
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


            // for (int t = 0; t < NUMBER_OF_HEURISTICS; t++)
            // {
            //     std::cout << population[i][t] << "    ";
            // }
            // std::cout << "\n";
        }

        savePopulationToFile();
    }


    for (int tuningRun = 0; tuningRun < NUMBER_OF_TUNING_RUNS; tuningRun++)
    {

        std::clock_t c_start = std::clock();
        auto t_start = std::chrono::high_resolution_clock::now();


        std::cout << "Run: " << tuningRun + 1 << "/" << NUMBER_OF_TUNING_RUNS << "\n";
        //           << "    i: " << (i / NUMBER_OF_THREADS) + 1 << "/" << (POPULATION_SIZE / NUMBER_OF_THREADS) << "\n" ;

        std::thread t[NUMBER_OF_THREADS];


        for (int j = 0; j < NUMBER_OF_THREADS; j++)
        {
            t[j] = std::thread(gamePlay);
        }

        gamePlay();

        for (int j = 0; j < NUMBER_OF_THREADS; j++)
        {
            t[j].join();
        }


        // for (int i = 0; i < POPULATION_SIZE; i += NUMBER_OF_THREADS)
        // {
        //     // std::cout << "Run: " << tuningRun + 1 << "/" << NUMBER_OF_TUNING_RUNS
        //     //           << "    i: " << (i / NUMBER_OF_THREADS) + 1 << "/" << (POPULATION_SIZE / NUMBER_OF_THREADS) << "\n" ;



        //     int numberOfThreadsToLaunch = std::min(POPULATION_SIZE - i, NUMBER_OF_THREADS);

        //     std::thread t[numberOfThreadsToLaunch];


        //     // std::cout << "Threads Launched" << "\n" ;
        //     for (int j = 0; j < numberOfThreadsToLaunch; j++)
        //     {
        //         t[j] = std::thread(gamePlay, i + j);
        //     }


        //     // std::cout << "Waiting for join" << "\n" ;

        //     for (int j = 0; j < numberOfThreadsToLaunch; j++)
        //     {
        //         // std::cout << "Pre j: " << i << "\n" ;
        //         t[j].join();
        //         // std::cout << "Post j: " << i << "\n" ;
        //     }
        // }

        createNewPopulation();
        populationIndex = 0;

        std::clock_t c_end = std::clock();
        auto t_end = std::chrono::high_resolution_clock::now();

        // // std::cout << "Time: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;
        // std::cout << "Time: " << std::chrono::duration<double, std::milli>(end - start).count() << "\n";

        std::cout << std::fixed << std::setprecision(2) << "CPU time used: "
                  << 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC << " ms\n"
                  << "Wall clock time passed: "
                  << std::chrono::duration<double, std::milli>(t_end - t_start).count()
                  << " ms\n";
    }

    std::cout << "Tuning Done" << "\n" ;
    std::cout << "--------------------" << "\n" ;
    printBestParamVector();

    return a.exec();
}




int main2(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Window window;
    window.show();

    float heuristicCoeff[NUMBER_OF_HEURISTICS];
    heuristicCoeff[0] = 0.87644898891449;
    heuristicCoeff[1] =  0.473638504743576;
    heuristicCoeff[2] = -0.0289361644536257;
    heuristicCoeff[3] =  -0.0366345383226871;
    heuristicCoeff[4] =  -0.0729684233665466;

    AIPlayer player =  AIPlayer(heuristicCoeff);
    Game *game = new Game(&player, NULL);
    game = new Game(&player, &window);

    std::thread t1(gamePlay2, game);

    return a.exec();
}
