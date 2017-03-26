#include "search.hpp"
template <typename T>
Node<T>::Node(){
    this->len = 0;
    this->hcost = 0;
};
template <typename T>
Node<T>::Node(T v, int len){
    this->val = v;
    this->len = len;
};
template <typename T>
Node<T>::Node(T v, int len, int hcost){
    this->val = v;
    this->len = len;
    this->hcost = hcost;
};
template <typename T>
void Graph<T>::init(void){
    open->_clear();
    visited.clear();
};

template <typename T>
int Graph<T>::search(Node<T> st, Node<T> en, int (*expand)(T,Graph<T>*,int,int),result *rc){  
    open->_push(st);
    Node<T> node;
    int exrc;
    while(1){
        if(open->_empty()){
            return 0;
        }
        do{
            node = open->_top();    
            open->_pop();
        }while(open->_test((visited.find(node)!=visited.end())?visited.find(node)->len:-1, node));
        if(node == en){
            rc->visit = visited.size();
            rc->len = node.len;
            return 1;
        }
        visited.insert(node);
        exrc = expand(node.val,this,node.len+1,1);
    }
};
template <typename T>
int Graph<T>::search(Node<T> st, Node<T> en, int (*expand)(T,Graph<T>*,int,int),int depth,result *rc){  
    open->_push(st);
    Node<T> node;
    int exrc;
    while(1){
        if(open->_empty()){
            return 0;
        }
        do{
            if(open->_size() == 0)
                return 0;
            node = open->_top();    
            open->_pop();
        }while(visited.find(node)!=visited.end() || open->_test(node.len, depth));
        if(node == en){
            rc->visit = visited.size();
            rc->len = node.len;
            return 1;
        }
        visited.insert(node);
        exrc = expand(node.val,this,node.len+1,1);
    }
};
template <typename T>
int Graph<T>::iter_search(Node<T> st, Node<T> en, int (*expand)(T,Graph<T>*,int,int),result *rc){
    int depth = 1;
    while(!search(st, en, expand, depth++, rc)){
        init();
    }
    return 0;
};

