#include <cstddef>
#include <new>
#include "skipnode.hpp"

template <class T>
SkipNode<T>::SkipNode(int nh) : nodeheight(nh)
{
    data = NULL;
    fwdnodes = new SkipNode<T> *[nodeheight+1];
    for(int i=0; i<=nodeheight; ++i)
        fwdnodes[i] = NULL;
}

template <class T>
SkipNode<T>::SkipNode(T *d, int nh) : nodeheight(nh)
{
    data = d;
    fwdnodes = new SkipNode<T> *[nodeheight+1];
    for(int i=0; i<=nodeheight; ++i)
        fwdnodes[i] = NULL;
}

template <class T>
SkipNode<T>::~SkipNode()
{
    delete data;
    delete[] fwdnodes;
}

template <class T>
T *SkipNode<T>::getData()
{
   return data; 
}

template <class T>
int SkipNode<T>::getNodeHeight()
{
    return nodeheight;
}

template class SkipNode<int>;
