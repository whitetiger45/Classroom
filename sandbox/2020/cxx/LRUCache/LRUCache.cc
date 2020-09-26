#include <exception>
#include <iostream>
#include "LRUCache.h"
 
using namespace std;
// https://stackoverflow.com/questions/3591024/typedef-alias-of-an-generic-class
template<typename T>
using pr = pair<int, T>;

LRUCache::LRUCache( int capacity ) : m_capacity{ capacity }{}
/* ----------------------------------------------- */
int LRUCache::capacity() const{
    return m_capacity;
}
/* ----------------------------------------------- */
/* 
- inside the list store the key 
- store address (iterator) of key, & value in map
- try to do this in constant time, O(1)
*/
int LRUCache::get(int key) {
    int ret{0};
    try{
        ret = m_cacheMap.at( key ).value;
        m_queue.erase( m_cacheMap[key].it );
        m_queue.push_front( key );   
        m_cacheMap[key].it = m_queue.begin();
    }
    catch( const exception& e ){
        ret =  -1;
    }
    return ret;
}
/* ----------------------------------------------- */
void LRUCache::put(int key, int value) {
    /* 
        can you get this to be O(1)?
    */
    int tmp = get( key );
    if( tmp == -1 ){
        if( m_queue.size() == capacity() ){
            int last = m_queue.back();
            m_queue.pop_back();
            m_cacheMap.erase( last );
        }
        m_queue.push_front(key);
        Node newNode{m_queue.begin(), value};
        m_cacheMap.insert(pr<Node>(key,newNode));
    }
    else if ( tmp != -1 ){
        m_queue.erase( m_cacheMap[key].it );
        m_queue.push_front(key);
        m_cacheMap[key] = Node{m_queue.begin(),value};
    }

    // m_queue.push_front( key );
    // LRUCache::Node x{ m_queue.begin(), value };
    // m_cacheMap.insert( pr<Node>( key, x ) );
}
/* ----------------------------------------------- */
void LRUCache::display() const {
    cout << "cache holds:\n";
    for( auto it = m_cacheMap.begin(); it != m_cacheMap.end(); ){
        cout << it->second.value;
        ( ++it != m_cacheMap.end() ) ? cout << ", " : cout << endl;
    }
}
/* -----------------------------------------------
    This is used to show that most recently used key is at the 
    front of the key, which includes using a 'get'
 */
void LRUCache::printQueue() const {
    for( auto it = m_queue.begin(); it != m_queue.end(); ){
        cout << *it;
        ( ++it != m_queue.end() ) ? cout << ", " : cout << endl;
    }
}
