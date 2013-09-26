/* This class represents an individual node in the skip list */

#ifndef _SKIPNODE_H
#define _SKIPNODE_H

template <class T>
class SkipNode
{
    private:
        int nodeheight;
        T *data;
        
    public:
        SkipNode **fwdnodes;
        
        SkipNode(int nh);
        SkipNode(T &d, int nh);
        ~SkipNode();
        T *getData();
        int getNodeHeight();
};

#endif //end of _SKIPNODE_H