#ifndef GRAPH_SEARCH
#define GRAPH_SEARCH
#include <stack>
#include <queue>
#include <unordered_set>
using namespace std;
typedef struct RESULT result;
//result structure
struct RESULT{
    int visit;
    int open;
    int len;
};
//template class Node<T> declaration
template <typename T>
class Node{
    public:
        int len;
        T val;
        Node(T v, int len);
};

//SEARCHFUNC structure
template <typename T>
struct searchFunc{
    void (*_push)(Node<T> node);
    Node<T> (*_top)();
    int (*_empty)();
    void (*_pop)();
    void (*_clear)();
};
//template class CustomContainer<T,_open> declaration
template <
    typename T,
    template <typename> class _open
    >
class CustomContainer{
    public:
        _open<Node<T>> container;
        void (*_push)(Node<T> node);
        Node<T> (*_top)();
        int (*_empty)();
        void (*_pop)();
        void (*_clear)();
        CustomContainer(struct searchFunc<T> *sf){
            _push = sf->_push;
            _pop = sf->_pop;
            _empty = sf->empty;
            _top = sf->_top;
            _clear = sf->_cle   _push = sf->_push;
    
            _pop = sf->_pop;
            _empty = sf->empty;
            _top = sf->_top;
            _clear = sf->_clear;;
        };
};
//template class Graph<T,_open> declaration
template <
    typename T,
    template <typename> class _open
    >
class Graph{
    public:
        CustomContainer<T,_open> open;
        unordered_set<T> visited;
        int search(T , T , int (*)(T ,Graph<T,_open>* ,int, int),result *);
        void init();
        Graph(struct searchFunc<T> *sf) : open(sf){
        };
};
#include "search.tpp"
#endif
