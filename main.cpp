#include "linked_list.h"

int main()
{
    utec::linked_list<int> ll {1, 2, 3, 4};
    utec::linked_list<int>ll2 = {0, 1, 2, 3, 4, 5, 99};
    
    for ( unsigned i = 0; i < ll.size(); ++i )
        std::cout << ll[i] << ' ';
    
    std::cout << '\n';
    
    for ( auto i = ll2.begin(); i != ll2.traverse(6); i = i->next )
        std::cout << i->value << ' ';
    
    
    
    return 0;
}