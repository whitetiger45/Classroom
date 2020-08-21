#include <exception>
#include <iostream>
#include "LRUCache.h"
 
using namespace std;
// https://stackoverflow.com/questions/3591024/typedef-alias-of-an-generic-class
template<typename T>
using pr = pair<int, T>;

LRUCache::LRUCache( int capacity ) : m_capacity{ capacity }{}
/* ----------------------------------------------- */
int LRUCache::size() const{
    return m_capacity;
}
/* ----------------------------------------------- */
/* 
- inside the list store the key 
- store address (iterator) of key, & value in map
- must be O(1)
*/
int LRUCache::get(int key) const {
    int ret{0};
    try{
       ret = m_cacheMap.at( key ).value;
    }
    catch( const out_of_range& oor ){
        ret =  -1;
    }
    return ret;
}
/* ----------------------------------------------- */
void LRUCache::put(int key, int value) {
    /* 
    must be O(1)
    branch 1 - if key exists, update value 
    branch 2 - 
        a. - if key does not exist & less than the capacity 
        b. - if key does not exist & key == capacity, remove oldest key 
            and push new key-value
    */
    int tmp = get( key );
    if( tmp == -1 ){
        if( m_queue.size() == m_capacity ){
            int last = m_queue.back();
            m_queue.pop_back();
            m_cacheMap.erase( last );
        }
    }
    else if ( tmp != -1 ){
        m_queue.erase( m_cacheMap[key].it );
    }

    m_queue.push_front( key );
    LRUCache::Node x{ m_queue.begin(), value };
    m_cacheMap.insert( pr<Node>( key, x ) );
}
/* ----------------------------------------------- */
void LRUCache::display() const {
    cout << "cache holds:\n";
    for( auto it = m_cacheMap.begin(); it != m_cacheMap.end(); ){
        cout << it->second.value;
        ( ++it != m_cacheMap.end() ) ? cout << ", " : cout << endl;
    }
}
 