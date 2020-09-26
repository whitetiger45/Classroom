// https://www.geeksforgeeks.org/lru-cache-implementation/
#include "LRUCache.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <string>

#define CAPACITY 9

int main(){

    LRUCache cache{CAPACITY};
    for(int i{0}; i < cache.capacity()+3; i++){
        cache.put(i,i*9);
    }

    cache.display();
    srand(time(NULL));
    int n = rand() % cache.capacity()+4; // generate a random number between 1 and cache size
    std::cout << "what's the queue look like before using our random key (" << n-1 << "):" << std::endl;
    cache.printQueue();
    std::cout << "our random key ("<< n-1 <<") in the cache is: " << cache.get(n-1) << std::endl;
    std::cout << "what's the queue look like after using our random key (" << n-1 << "):" << std::endl;
    cache.printQueue();
    return 0;
}
