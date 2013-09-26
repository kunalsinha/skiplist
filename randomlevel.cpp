#include <cstdlib>
#include <ctime>
#include "randomlevel.hpp"

/* RandomLevel constructor params:
 * level - max number of levels in the skip list
 * probability - the probability with the the skip list should be generated
 */
RandomLevel::RandomLevel(int level, double p) : max_level(level), probability(p)
{
    srand(time(NULL));
}

double RandomLevel::getRandomLevel()
{
    int level = 0;
    double temp;
    while(level < max_level)
    {
        temp = (double)rand() / RAND_MAX;
        if(temp > probability)
            break;
        ++level;
    }
    return level;
}
