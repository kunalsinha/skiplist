#include <iostream>
#include <cstddef>
#include "skipnode.hpp"
#include "skiplist.hpp"

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
    
    for(height=cur_height; height >= 0; --height)
    {
        while(traverser->fwdnodes[height] != NULL && *(traverser->fwdnodes[height]->getData()) < d)
            traverser = traverser->fwdnodes[height];
        predecessor[height] = traverser;
    }
    
    traverser = traverser->fwdnodes[0];
    if(traverser == NULL || *(traverser->getData()) != d)
        return false;
    
    for(height = 0; height <= cur_height; ++height)
    {
        if(predecessor[height]->fwdnodes[height] != traverser)
            break;
        predecessor[height]->fwdnodes[height] = traverser->fwdnodes[height];
    }
    
    delete traverser;
    
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
    while(traverser != NULL)
    {
        next = traverser->fwdnodes[0];
        delete traverser;
        traverser = next;
    }
    for(int i=0; i<=head->getNodeHeight(); ++i)
        head->fwdnodes[i] = NULL;
}

template <class T>
void SkipList<T>::print()
{
    SkipNode<T> *traverser = head->fwdnodes[0];
    if(traverser == NULL)
        std::cout << "Skip list is empty";
    while(traverser != NULL)
    {
        std::cout << *(traverser->getData()) << " ";
        traverser = traverser->fwdnodes[0];
    }
    std::cout << std::endl;
}

template class SkipList<int>;
