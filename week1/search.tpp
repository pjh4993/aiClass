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
    this->hcost = 0;
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
int Graph<T>::search(Node<T> st, Node<T> en, int (*expand)(T,Graph<T>*,int),result *rc){  
    int max_open = 0;
    open->_push(st);
    Node<T> node;
    int exrc;
    while(1){
        if(open->_empty()){
            return 0;
        }
        if(max_open < open->_size())
            max_open = open->_size();
        do{
            node = open->_top();    
            open->_pop();
        }while(open->_test((visited.find(node)!=visited.end())?visited.find(node)->len:-1, node));
        if(node == en){
            rc->visit = visited.size();
            rc->len = node.len;
            rc->open = max_open;
            return 1;
        }
        auto m_pair = visited.insert(node);
        if(m_pair.second != true){
            visited.erase(m_pair.first);
            visited.insert(node);
        }
        exrc = expand(node.val,this,node.len+1);
    }
};
template <typename T>
int Graph<T>::search(Node<T> st, Node<T> en, int (*expand)(T,Graph<T>*,int (*)(T),int),int (*_hcost)(T),result *rc){  
    int max_open = 0;
    open->_push(st);
    Node<T> node;
    int exrc;
    while(1){
        if(open->_empty()){
            return 0;
        }
        if(max_open < open->_size())
            max_open = open->_size();
        do{
            node = open->_top();    
            open->_pop();
        }while(open->_test((visited.find(node)!=visited.end())?visited.find(node)->len:-1, node));
        if(node == en){
            rc->visit = visited.size();
            rc->len = node.len;
            rc->open = max_open;
            return 1;
        }
        auto m_pair = visited.insert(node);
        if(m_pair.second != true){
            visited.erase(m_pair.first);
            visited.insert(node);
        }
        exrc = expand(node.val,this,_hcost,node.len+1);
    }
};
template <typename T>
int Graph<T>::search(Node<T> st, Node<T> en, int (*expand)(T,Graph<T>*,int),int depth,int *max_open,result *rc){  
    open->_push(st);
    Node<T> node;
    int exrc;
    while(1){
        if(open->_empty()){
            return 0;
        }
        if(*max_open < open->_size())
            *max_open = open->_size();
        do{
            if(open->_size() == 0)
                return 0;
            node = open->_top();    
            open->_pop();
        }while(visited.find(node)!=visited.end() || open->_test(node.len, depth));
        if(node == en){
            rc->visit = visited.size();
            rc->len = node.len;
            rc->open = *max_open;
            return 1;
        }
        auto m_pair = visited.insert(node);
        if(m_pair.second != true){
            visited.erase(m_pair.first);
            visited.insert(node);
        }
        exrc = expand(node.val,this,node.len+1);
    }
};
template <typename T>
int Graph<T>::iter_search(Node<T> st, Node<T> en, int (*expand)(T,Graph<T>*,int),result *rc){
    int depth = 1;
    int max_open = 0;
    while(!search(st, en, expand, depth++, &max_open, rc)){
        init();
    }
    return 0;
};

