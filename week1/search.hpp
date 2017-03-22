#ifndef GRAPH_SEARCH
#define GRAPH_SEARCH
#include <stack>
#include <queue>
#include <unordered_set>
#include <vector>
#include <deque>
#include <functional>
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

//template class CustomContainer<T,_open> declaration
template <typename T>
class CustomContainer{
    public:
        virtual void _push(Node<T> node) = 0;
        virtual Node<T> _top() = 0;
        virtual int _empty() = 0;
        virtual void _pop() = 0;
        virtual void _clear() = 0;
};
template <typename T>
class DfsStack : public CustomContainer<T>{
    stack<Node<T>> container;
    virtual void _push(Node<T> node);
    virtual Node<T> _top();
    virtual int _empty();
    virtual void _pop();
    virtual void _clear();
};
template <typename T>
class BfsQueue : public CustomContainer<T>{
    queue<Node<T>> container;
    virtual void _push(Node<T> node);
    virtual Node<T> _top();
    virtual int _empty();
    virtual void _pop();
    virtual void _clear();
};



//template class Graph<T,_open> declaration
template <
    typename T
    >
class Graph{
    public:
        CustomContainer<T> *open;
        unordered_set<T> visited;
        int search(T , T , int (*)(T ,Graph<T>* ,int, int),result *);
        int iter_search(T , T , int (*)(T ,Graph<T>* ,int, int),result *);
        int search(T , T , int (*)(T ,Graph<T>* ,int, int),int,result *);
        void init();
        Graph(CustomContainer<T> *m_open){
            open = m_open;
        };
};
#include "search.tpp"
#endif
