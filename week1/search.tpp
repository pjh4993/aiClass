#include "search.hpp"
template <typename T>
Node<T>::Node(T v, int len){
    this->val = v;
    this->len = len;
};
template <typename T>
Search<T>::Search(void){
    init();
};
template <typename T>
void Search<T>::init(void){
    visit = open = len = 0;
    std::stack<Node<T>> empty_stack;
    std::queue<Node<T>> empty_queue;
    std::swap(graph_queue,empty_queue);
    std::swap(graph_stack,empty_stack);
    visited.clear();

};
template <typename T>
int Search<T>::bfs_graph(T st, T en, int (*expand)(T,Search<T>*,int, int),result *rc){  
    graph_queue.push(Node<T>(st,0));
    T v;
    int exrc,m_len=0;
    while(1){
        if(graph_queue.empty()){
            return 0;
        }
        do{
            v = graph_queue.front().val;    
            m_len = graph_queue.front().len;    
            graph_queue.pop();
        }while(visited.find(v)!=visited.end());
        if(v == en){
            rc->visit = visited.size();
            rc->len = m_len;
            return 1;
        }
        visited.insert(v);
        exrc = expand(v,this,++m_len,0);
    }
};

template <typename T>
int Search<T>::dfs_graph(T st, T en, int (*expand)(T,Search<T>*,int,int),result *rc){  
    graph_stack.push(Node<T>(st,0));
    T v;
    int exrc,m_len=0;
    while(1){
        if(graph_stack.empty()){
            return 0;
        }
        do{
            v = graph_stack.top().val;    
            m_len = graph_stack.top().len;    
            graph_stack.pop();
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
int Search<T>::dfs_graph(T st, T en, int (*expand)(T,Search<T>*,int,int),int depth,result *rc){  
    graph_stack.push(Node<T>(st,0));
    T v;
    int exrc,m_len=0;
    while(1){
        if(graph_stack.empty()){
            return 0;
        }
        do{
            if(graph_stack.size() == 0)
                return 0;
            v = graph_stack.top().val;    
            m_len = graph_stack.top().len;    
            graph_stack.pop();
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
int Search<T>::ids_graph(T st, T en, int (*expand)(T,Search<T>*,int,int),result *rc){  
    int depth = 1;
    while(!dfs_graph(st, en, expand, depth++, rc)){
        this->init();   
    }
    return 0;
}
