#include <cstdlib>
#include <ctime>
#include "randomlevel.hpp"


RandomLevel::RandomLevel(int level, double p) : max_level(level), probability(p)
{
    srand(time(NULL));
}
        
double RandomLevel::getRandomLevel()
{
    int level = 0;
    double temp;
    while(level < max_level)// &&  ((double)rand() / RAND_MAX) < probability)
    {
        temp = (double)rand() / RAND_MAX;
        if(temp > probability)
            break;
        ++level;
    }
    return level;
}
