#include "search.hpp"
template <typename T>
Node<T>::Node(T v, int len){
    this->val = v;
    this->len = len;
};
template <
    typename T
    >
void Graph<T>::init(void){
    open->_clear();
    visited.clear();
};

template <typename T>
int Graph<T>::search(T st, T en, int (*expand)(T,Graph<T>*,int,int),result *rc){  
    open->_push(Node<T>(st,0));
    T v;
    int exrc,m_len=0;
    while(1){
        if(open->_empty()){
            return 0;
        }
        do{
            v = open->_top().val;    
            m_len = open->_top().len;    
            open->_pop();
        }while(visited.find(v)!=visited.end());
        if(v == en){
            rc->visit = visited.size();
            rc->len = m_len;
            return 1;
        }
        visited.insert(v);
        exrc = expand(v,this,++m_len,1);
    }
};
template <typename T>
int Graph<T>::search(T st, T en, int (*expand)(T,Graph<T>*,int,int),int depth,result *rc){  
    open->_push(Node<T>(st,0));
    T v;
    int exrc,m_len=0;
    while(1){
        if(open->_empty()){
            return 0;
        }
        do{
            v = open->_top().val;    
            m_len = open->_top().len;    
            open->_pop();
        }while(m_len >= depth || visited.find(v)!=visited.end());
        if(v == en){
            rc->visit = visited.size();
            rc->len = m_len;
            return 1;
        }
        visited.insert(v);
        exrc = expand(v,this,++m_len,1);
    }
};
template <typename T>
int Graph<T>::iter_search(T st, T en, int (*expand)(T,Graph<T>*,int,int),result *rc){
    int depth = 1;
    while(!search(st, en, expand, depth++, rc)){
        this->init();
    }
    return 0;
};


template <typename T>
void DfsStack<T>::_push(Node<T> node){
    container.push(node);
};
template <typename T>
Node<T> DfsStack<T>::_top(){
    return container.top();
}
template <typename T>
int DfsStack<T>::_empty(){
    return container.empty();
}
template <typename T>
void DfsStack<T>::_pop(){
    container.pop();
}
template <typename T>
void DfsStack<T>::_clear(){
    stack<Node<T>> empty_stack;
    swap(container,empty_stack);
}

template <typename T>
void BfsQueue<T>::_push(Node<T> node){
    container.push(node);
};
template <typename T>
Node<T> BfsQueue<T>::_top(){
    return container.front();
}
template <typename T>
int BfsQueue<T>::_empty(){
    return container.empty();
}
template <typename T>
void BfsQueue<T>::_pop(){
    container.pop();
}
template <typename T>
void BfsQueue<T>::_clear(){
    queue<Node<T>> empty_stack;
    swap(container,empty_stack);
}


