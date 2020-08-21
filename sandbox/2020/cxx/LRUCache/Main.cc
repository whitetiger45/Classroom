// https://www.geeksforgeeks.org/lru-cache-implementation/
#include "LRUCache.h"
#include <string>

#define CAPACITY 9

int main(){

    LRUCache cache{CAPACITY};
    for(int i{0}; i < cache.size()+3; i++){
        cache.put(i,i*9);
    }

    cache.display();

    return 0;
}
