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
void SkipList<T>::insert(T *d)
{
    int height;
    SkipNode<T> *predecessor[max_height+1];
    SkipNode<T> *traverser = head;
    
    for(height=cur_height; height >= 0; --height)
    {
        while(traverser->fwdnodes[height] != NULL && *(traverser->fwdnodes[height]->getData()) < *d)
            traverser = traverser->fwdnodes[height];
        predecessor[height] = traverser;
    }
    
    int level = random->getRandomLevel();
    #if DEBUG
    std::cout << "Level: " << level << std::endl;
    #endif
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

int main()
{
    SkipList<int> sl(10, 0.5);
    int num;
    int *p;
    char ch;
    while(true)
    {
        std::cout << "Press i to insert, s to search, r to remove and p to print the skip list and e to exit" << std::endl;
        std::cin >> ch;
        switch(ch)
        {
            case 'i':
                std::cout << "Enter a number: ";
                std::cin >> num;
                p = new int(num);
                sl.insert(p);
                break;
            case 'r':
                std::cout << "Enter the number to remove: ";
                std::cin >> num;
                if(sl.remove(num))
                    std::cout << num << " removed successfully" << std::endl;
                else
                    std::cout << num << " not found in the skip list" << std::endl;
                    break;
            case 's':
                std::cout << "Enter the number to search: " << std::endl;
                std::cin >> num;
                if(sl.search(num) != NULL)
                    std::cout << num << " found" << std::endl;
                else
                    std::cout << num << " not found" << std::endl;
                break;
            case 'p':
                sl.print();
                break;
            case 'e':
                break;
            default:
                std::cout << "Wrong choice. Try again" << std::endl;
                break;
        }
        if(ch == 'e')
            break;
    }
    return 1;
}
