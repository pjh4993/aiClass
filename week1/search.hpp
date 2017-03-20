#ifndef GRAPH_SEARCH
#define GRAPH_SEARCH
#include <stack>
#include <queue>
#include <unordered_set>
using namespace std;
typedef struct RESULT result;
struct RESULT{
    int visit;
    int open;
    int len;
};
template <typename T>
class Node{
    public:
        int len;
        T val;
        Node(T v, int len);
};
template <typename T>
class Search{
    public:
        stack<Node<T>> graph_stack;
        queue<Node<T>> graph_queue;
        unordered_set<T> visited;
        int visit, open, len;
        int bfs_graph(T st, T en, int (*expand)(T state,Search<T>* _this,int len, int dir),result *rc);
        int dfs_graph(T st, T en, int (*expand)(T state, Search<T>* _this,int len, int dir),result *rc);
        int dfs_graph(T st, T en, int (*expand)(T state, Search<T>* _this,int len, int dir),int depth,result *rc);
        int ids_graph(T st, T en, int (*expand)(T state, Search<T>* _this,int len, int dir),result *rc);
        void init();
        Search();
};
#include "search.tpp"
#endif
