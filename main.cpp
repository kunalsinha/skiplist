/* Sample usage of the SkipList class */

#include <iostream>
#include "skiplist.hpp"

int main()
{
    SkipList<int> sl(10, 0.5);
    int num;
    char ch;
    while(true)
    {
        std::cout << "Press i to insert, s to search, r to remove, c to clear and p to print the skip list and e to exit" << std::endl;
        std::cin >> ch;
        switch(ch)
        {
            case 'i':
                std::cout << "Enter a number: ";
                std::cin >> num;
                sl.insert(num);
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
            case 'c':
                sl.clear();
                break;
            case 'p':
                std::cout << sl << std::endl;
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