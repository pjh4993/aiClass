#include "search.hpp"
template <typename T>
Node<T>::Node(T v, int len){
    this->val = v;
    this->len = len;
};
template <
    typename T,
    template <typename> class _open
    >
void Graph<T,_open>::init(void){
    open._clear();
    visited.clear();
};
template <
    typename T,
    template <typename> class _open
    >
int Graph<T,_open>::search(T st, T en, int (*expand)(T,Graph<T,_open>*,int,int),result *rc){  
    open._push(Node<T>(st,0));
    T v;
    int exrc,m_len=0;
    while(1){
        if(open._empty()){
            return 0;
        }
        do{
            v = open._top().val;    
            m_len = open._top().len;    
            open._pop();
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
