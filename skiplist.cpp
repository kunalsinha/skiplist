#include <iostream>
#include <cstddef>
#include "skipnode.hpp"
#include "skiplist.hpp"

/* Create a skip list with a given max height and probability */
template <class T>
SkipList<T>::SkipList(int mh, double p)
{
    max_height = mh;
    probability = p;
    cur_height = 0;
    random = new RandomLevel(max_height, probability);
    head = new SkipNode<T>(max_height);
}

template <class T>
SkipList<T>::~SkipList()
{
    delete random;
    SkipNode<T> *traverser = head;
    SkipNode<T> *next;
    
    /* Delete all the nodes */
    while(traverser != NULL)
    {
        next = traverser->fwdnodes[0];
        delete traverser;
        traverser = next;
    }
}

template <class T>
void SkipList<T>::insert(T &d)
{
    int height;
    SkipNode<T> *predecessor[max_height+1];
    SkipNode<T> *traverser = head;
    
    /* find the predecessors of the inserted node */
    for(height=cur_height; height >= 0; --height)
    {
        while(traverser->fwdnodes[height] != NULL && *(traverser->fwdnodes[height]->getData()) < d)
            traverser = traverser->fwdnodes[height];
        predecessor[height] = traverser;
    }
    
    int level = random->getRandomLevel();
    SkipNode<T> *node = new SkipNode<T>(d, level);
    if(level > cur_height)
    {
        for(height = level; height > cur_height; --height)
            predecessor[height] = head;
        cur_height = level;
    }
    
    /* set the proper links at each level */
    for(height=level; height >=0; --height)
    {
        node->fwdnodes[height] = predecessor[height]->fwdnodes[height];
        predecessor[height]->fwdnodes[height] = node;
    }
};

template <class T>
bool SkipList<T>::remove(T d)
{
    SkipNode<T> *traverser = head;
    SkipNode<T> *predecessor[cur_height+1];
    int height;
    
    /* find the predecessors of the node to be removed */
    for(height=cur_height; height >= 0; --height)
    {
        while(traverser->fwdnodes[height] != NULL && *(traverser->fwdnodes[height]->getData()) < d)
            traverser = traverser->fwdnodes[height];
        predecessor[height] = traverser;
    }
    
    traverser = traverser->fwdnodes[0];
    
    /* return false if the node to be removed does not exist */
    if(traverser == NULL || *(traverser->getData()) != d)
        return false;
    
    /* fix the links  and remove the node */
    for(height = 0; height <= cur_height; ++height)
    {
        if(predecessor[height]->fwdnodes[height] != traverser)
            break;
        predecessor[height]->fwdnodes[height] = traverser->fwdnodes[height];
    }
    delete traverser;
    
    /* if the removed node was the only node at some levels then fix the current height of
     * the skip list */
    while(head->fwdnodes[cur_height] == NULL)
        --cur_height;
    return true;
}

template <class T>
SkipNode<T> *SkipList<T>::search(T d)
{
    SkipNode<T> *traverser = head;
    int height;
    
    for(height = cur_height; height >= 0; --height)
    {
        while(traverser->fwdnodes[height] != NULL && *(traverser->fwdnodes[height]->getData()) <= d)
            traverser = traverser->fwdnodes[height];
        if(traverser != head && *(traverser->getData()) == d)
            return traverser;
    }
    return NULL;
}

template <class T>
void SkipList<T>::clear()
{
    SkipNode<T> *traverser = head->fwdnodes[0];
    SkipNode<T> *next;
    
    /* delete all the nodes of the skip list except the head */
    while(traverser != NULL)
    {
        next = traverser->fwdnodes[0];
        delete traverser;
        traverser = next;
    }
    
    /* reset all forward nodes of head to NULL */
    for(int i=0; i<=head->getNodeHeight(); ++i)
        head->fwdnodes[i] = NULL;
}

template class SkipList<int>;
