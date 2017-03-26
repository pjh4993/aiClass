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
        int hcost;
        T val;
        Node(T v, int len, int hcost);
        Node(T v, int len);
        Node();
        bool operator == (const Node<T> &other){
            return val == other.val;
        }
};
template <typename T>
bool operator == (const Node<T> &lhs, const Node<T> &rhs){
    return lhs.val == rhs.val;
};
template <typename T>
bool operator <= (const Node<T> &lhs, const Node<T> &rhs){
    return (lhs.len + lhs.hcost) <= (rhs.len + lhs.hcost);
};

template<typename T>
struct nodeHasher{
    size_t operator()(const Node<T> &node)const{
        return hash<T>()(node.val);
    }
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
        virtual int _size() = 0;
        virtual int _test(int len, Node<T> &node){
            if(len == -1)
                return 0;
            else
                return 1;
        };
        virtual int _test(int len, int depth){
        };
};
template <typename T>
class DfsStack : public CustomContainer<T>{
    stack<Node<T>> container;
    virtual void _push(Node<T> node){
        container.push(node);
    };
    virtual Node<T> _top(){
        return container.top();
    };
    virtual int _empty(){
        return container.empty();
    };
    virtual void _pop(){
        container.pop();
    };
    virtual void _clear(){
        stack<Node<T>> empty_stack;
        swap(container,empty_stack);
    };
    virtual int _size(){
        return container.size();
    };
    virtual int _test(int len, int depth){
        return len >= depth;
    };
};
template <typename T>
class BfsQueue : public CustomContainer<T>{
    queue<Node<T>> container;
    virtual void _push(Node<T> node){ 
        container.push(node);
    };
    virtual Node<T> _top(){ 
        return container.front();
    };
    virtual int _empty(){ 
        return container.empty();
    };
    virtual void _pop(){ 
        container.pop();
    };
    virtual void _clear(){ 
        queue<Node<T>> empty_queue;
        swap(container,empty_queue);
    };
    virtual int _size(){ 
        return container.size();
    };
};
template <typename T>
class Astar : public CustomContainer<T>{
    priority_queue<Node<T>> container;
    virtual void _push(Node<T> node){
        container.push(node);
    };
    virtual Node<T> _top(){
        return container.top();
    };
    virtual int _empty(){
        return container.empty();
    };
    virtual void _pop(){
        container.pop();
    };
    virtual void _clear(){
        priority_queue<Node<T>> empty_queue;
        swap(container,empty_queue);
    };
    virtual int _size(){
        return container.size();
    };
    virtual int _test(int len, Node<T> &node){
        if(len == -1){
            return 0;
        }else if(node.len >= len){
            return 0;
        }else{
            return 1;
        }
    };
};

//template class Graph<T,_open> declaration
template <typename T>
class Graph{
    public:
        CustomContainer<T> *open;
        unordered_set<Node<T>,nodeHasher<T>> visited;
        int search(Node<T> , Node<T> , int (*)(T ,Graph<T>* ,int, int),result *);
        int search(Node<T> , Node<T> , int (*)(T ,Graph<T>* ,int, int),void (*)(Node<T> &node),result *);
        int iter_search(Node<T> , Node<T> , int (*)(T ,Graph<T>* ,int, int),result *);
        int search(Node<T> , Node<T>, int (*)(T ,Graph<T>* ,int, int),int,result *);
        void init();
        Graph(CustomContainer<T> *m_open){
            open = m_open;
        };
};
#include "search.tpp"
#endif
