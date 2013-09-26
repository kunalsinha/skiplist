/* The SkipList class represents the skip list. Each node in the skip list is
** represented by a SkipNode object.
*/

#ifndef _SKIPLIST_H
#define _SKIPLIST_H

#include "randomlevel.hpp"
#include "skipnode.hpp"

template <class T>
class SkipList
{
    private:
        int max_height;
        int cur_height;
        double probability;
        RandomLevel *random;
        SkipNode<T> *head;
        
    public:
        SkipList(int mh, double p);
        ~SkipList();
        void insert(T &d);
        bool remove(T d);
        SkipNode<T> *search(T d);
        void clear();
        
        template <class Y>
        friend std::ostream& operator<<(std::ostream& stream, const SkipList<Y>& ob);
};

template <class Y>
std::ostream& operator<<(std::ostream& stream, const SkipList<Y>& ob)
{
    SkipNode<Y> *traverser = ob.head->fwdnodes[0];
    while(traverser != NULL)
    {
        stream << *(traverser->getData()) << " ";
        traverser = traverser->fwdnodes[0];
    }
    return stream;
}

#endif // end of _SKIPLIST_H