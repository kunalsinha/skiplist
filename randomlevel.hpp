/* A class that generates a random level between zero and a maximum number of levels */

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