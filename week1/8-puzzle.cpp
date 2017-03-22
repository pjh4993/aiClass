#include <iostream>
#include "search.hpp"
using namespace std;
int exp_dir[9][4] = {{1,4},{1,4,3},{3,4},{2,1,4},{1,2,3,4},{2,3,4},{2,1},{3,2,1},{2,3}};
int swap(string state,int loc, int dir){
    int m_loc;
    switch(dir){
        case 1:
            m_loc = loc + 1;
            break;
        case 2:
            m_loc = loc - 3; 
            break;
        case 3:
            m_loc = loc - 1;
            break;
        case 4:
            m_loc = loc + 3;
            break;
    }
    state.replace(loc,1,string(1,state.at(m_loc)));
    state.replace(m_loc, 1, "9");
    return stoi(state);
}
int puzzle_expand(int state, Graph<int>* _this, int len, int dir){
    string s_state = to_string(state);
    int loc = s_state.find("9"),m_state,j;
    for(j=0;j<4;j++){
        if(exp_dir[loc][j] == 0)
            break;
        m_state = swap(s_state,loc,exp_dir[loc][j]);
        _this->open->_push(Node<int>(m_state,len));
    }
    return j;
};
int main(void){
    DfsStack<int> *dfs = new DfsStack<int>();
    BfsQueue<int> *bfs = new BfsQueue<int>();
    Graph<int> bfsGraph (bfs);
    Graph<int> dfsGraph (dfs);
    result rc;
    int st, en, type;
    while(1){
        cin >> st >> en >> type;
        switch(type){
            case 0:
                return 0;
            case 1:
                dfsGraph.search(st,en, puzzle_expand, &rc);
                cout << "DFS - visited : " << rc.visit << " len : " <<rc.len << endl;
                dfsGraph.init();
                break;
            case 2:
                bfsGraph.search(st,en, puzzle_expand, &rc);
                cout << "BFS - visited : " << rc.visit << " len : " <<rc.len << endl;
                bfsGraph.init();
                break;
            case 3:
                /*
                graph.ids_graph(st,en, puzzle_expand, &rc);
                cout << "IDS - visited : " << rc.visit << " len : " <<rc.len << endl;
                */
                break;
        }
    }
}

