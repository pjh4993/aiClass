#include <iostream>
#include <cstdlib>
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
int puzzle_expand(int state, Graph<int>* _this, int len){
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
int puzzle_expand(int state, Graph<int>* _this, int (*_hcost)(int), int len){
    string s_state = to_string(state);
    int loc = s_state.find("9"),m_state,j;
    for(j=0;j<4;j++){
        if(exp_dir[loc][j] == 0)
            break;
        m_state = swap(s_state,loc,exp_dir[loc][j]);
        _this->open->_push(Node<int>(m_state,len,_hcost(m_state)));
    }
    return j;
};


int hcost1(int state){
    //# of tiles out of place
    int hcost = 0;
    for(int i=9;i>0;i--){
        if(state % 10 != i)
            hcost++;
        state = state/10;
    }
    return hcost;
};
int hcost2(int state){
    //summation of the manhattan distance to the place
    int hcost = 0, m_node,m_dis_sum = 0;
    for(int i=8; i>=0 ; i--){
        m_node = state % 10 - 1;
        m_dis_sum += abs(m_node/3 - i /3) + abs(m_node%3 - i%3);
        state = state/10;
    }
    return m_dis_sum;
};

int main(void){
    DfsStack<int> *dfs = new DfsStack<int>();
    BfsQueue<int> *bfs = new BfsQueue<int>();
    Astar<int> *ast = new Astar<int>();
    Graph<int> bfsGraph (bfs);
    Graph<int> dfsGraph (dfs);
    Graph<int> aStarGraph (ast);
    result rc;
    int st, en, type;
    while(1){
        cin >> st >> en >> type;
        switch(type){
            case 0:
                return 0;
            case 1:
                dfsGraph.search(Node<int> (st,0),Node<int> (en,0), puzzle_expand, &rc);
                cout << "DFS - visited : " << rc.visit << " len : " <<rc.len <<" open : " << rc.open << endl;
                dfsGraph.init();
                break;
            case 2:
                bfsGraph.search(Node<int> (st,0),Node<int> (en,0), puzzle_expand, &rc);
                cout << "BFS - visited : " << rc.visit << " len : " <<rc.len <<" open : " << rc.open << endl;
                bfsGraph.init();
                break;
            case 3:
                dfsGraph.iter_search(Node<int>(st,0),Node<int>(en,0), puzzle_expand, &rc);
                cout << "IDS - visited : " << rc.visit << " len : " <<rc.len <<" open : " << rc.open << endl;
                dfsGraph.init();
                break;
            case 4:
                aStarGraph.search(Node<int> (st,0,hcost1(st)),Node<int> (en,0), puzzle_expand, hcost1, &rc);
                cout << "Ah1 - visited : " << rc.visit << " len : " <<rc.len <<" open : " << rc.open << endl;
                aStarGraph.init();
                break;
            case 5:
                aStarGraph.search(Node<int> (st,0,hcost2(st)),Node<int> (en,0), puzzle_expand, hcost2, &rc);
                cout << "Ah2 - visited : " << rc.visit << " len : " <<rc.len <<" open : " << rc.open << endl;
                aStarGraph.init();
                break;
                
        }
    }
}

