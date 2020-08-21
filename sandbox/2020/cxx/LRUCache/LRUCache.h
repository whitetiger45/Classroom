#ifndef LRU_CACHE_H
#define LRU_CACHE_H
#include <list> 
#include <unordered_map>

struct LRUCache {
    LRUCache( int );
    int size() const;
    int get(int) const;
    void put(int, int);
    void display() const;
    
private:
    struct Node {
        std::list<int>::iterator it;
        int value;
    };

    std::list<int> m_queue;
    int m_capacity;
    std::unordered_map<int, Node> m_cacheMap;
};

#endif // LRU_CACHE_H
