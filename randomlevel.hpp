/* A class that generates a random level for a node to be inserted into the skip list
 * with a given probability.
 */

#ifndef _RANDOMLEVEL_H
#define _RANDOMLEVEL_H

class RandomLevel
{
    private:
        int max_level;
        double probability;
    
    public:
        RandomLevel(int level, double p);
        double getRandomLevel();
};

#endif // end of _RANDOMLEVEL_H