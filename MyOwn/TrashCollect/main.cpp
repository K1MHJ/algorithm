#include <vector>
#include <string>
#include "main.h"
#include <map>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <array>
#include <list>
#include <queue>
#include <set>
#include <climits>


using namespace std;

vector<bool> visited; // 방문 유무를 저장하는 벡터 선언
vector<int> d; // 시작 노드에서부터 각 노드까지의 최단 거리를 저장하는 벡터 선언
//
//distance between trashes
int DBT[(MAX_TRASH + 1)*(MAX_TRASH + 1)];
std::map<int, POS> nodes;
std::vector<int> visit_order;
POS goal_pos;

char *arrMap;
int map_w, map_h;

void debug(POS p){
  cout << "[" << p.x << "," << p.y << "]" << endl;
}
# define INF 99999999

int GetPathDistance(POS start,POS goal)
{
  goal_pos = goal;
  Node topNode(start, nullptr);
  std::priority_queue<Node*, std::vector<Node*>, cmp> searchingCells;

  POS nPos;

  for(int i = 0;i<DIR::MAX;++i){
    if(AroundPos(nPos, start.x, start.y, (DIR)i, arrMap, map_w, map_h)){
      if(nPos.x == goal.x && nPos.y == goal.y){
        return 2;
      }
    }
  }

  ClearSearch();
  SetSearch(start.x, start.y, true);
  POS pos = start;
  for(int i = 0;i<DIR::MAX;++i){
    if(AroundPos(nPos, pos.x, pos.y, (DIR)i, arrMap, map_w, map_h)){
      Node* n = topNode.AddChild(nPos);
      searchingCells.push(n);
    }
  }
  std::vector<Node*> findPath;
  bool found_path = false;
  while(true){
    auto node = searchingCells.top();
    node->parent_node->neargoal_node = node;
    searchingCells.pop();
    SetSearch(node->cell.pos.x, node->cell.pos.y, true);
    for(int i = 0;i<DIR::MAX;++i){
      if(AroundPos(nPos, node->cell.pos.x,node->cell.pos.y, (DIR)i, arrMap, map_w, map_h)){
        if(!GetSearch(nPos.x,nPos.y)){
          Node* n = node->AddChild(nPos);
          if(nPos.x == goal.x && nPos.y == goal.y){
            while(n!=nullptr){
              findPath.push_back(n);
              n = n->parent_node;
            }
            found_path = true;
            break;
          }else{
            searchingCells.push(n);
          }
        }
      }
    }
    if(found_path){
      break;
    }
  }
  return findPath.size();
}

int getSmallestNode(int V) // 방문하지 않은 노드 중에서, 가장 최단 거리가 짧은 노드의 번호를 반환.
{
    int min_value=INT_MAX;
    int index = 0;
    
    for(int i=0; i<V; i++)
    {
        if(d[i] < min_value && !visited[i])
        {
            min_value = d[i];
            index = i;
        }
    }
    
    return index;
}

void dijkstra(int V, vector<pair<int,int>> graph[], int start)
{
    d[start]=0;
    visited[start]= true;
    
    for(int j=0; j<graph[start].size(); j++)
    {
        int adj = graph[start][j].first;
        d[adj] = graph[start][j].second; // 최단거리 테이블에 초기값 세팅
    }
    
    for(int i=0; i<V-1; i++)
    {
        int now = getSmallestNode(V);
        visited[now]=true;
        visit_order.push_back(now);
        
        for(int j=0; j<graph[now].size(); j++)
        {
            int cost = d[now] + graph[now][j].second;
            if(cost<d[graph[now][j].first])
            {
                d[graph[now][j].first]=cost;  // 최단 거리 업데이트
            }
        }
    }
}

int main()
{
  std::vector<std::string> map = {
      "0000000000",
      "0S T0 T0G0",
      "0 0 0     ",
      "0T0 T0 0 0",
      "0 T0   0T0",
      "0000000000"
  };
  map_h = map.size();
  map_w = map.begin()->length();
  arrMap = new char[map_h * map_w];
  for(int i = 0;i<map_h;i++){
    for(int j = 0;j<map[i].length();j++){
      arrMap[i * map_w + j] = map[i].c_str()[j];
    }
  }
  
  POS start;
  std::vector<POS> boxes;
  std::vector<POS> trashes;

  for(int i = 0;i<map_h;++i){
    for(int j = 0;j<map_w;++j){
      if('S' == arrMap[i * map_w + j]){
        start = POS{j,i};
      }
      else if('T' == arrMap[i * map_w + j]){
        trashes.push_back(POS{j,i});
      }
      else if('B' == arrMap[i * map_w + j]){
        boxes.push_back(POS{j,i});
      }
    }
  }
  nodes[0] = start;
  int n = 1;
  for(auto& t : trashes){
    nodes[n++] = t;
  }
  for(int i = 0;i<MAX_TRASH+1;++i){
    DBT[(MAX_TRASH+1) * i + i] = 0;
  }
  bool exit = false;

  int V;  // (V: # of nodes, E: # of edges, start: source)
  V = n;

  vector<pair<int,int>> graph[V];  // pair를 저장하는 벡터 V 개 생성 
  
  for(int i = 0;i<n;++i){
    for(int j = 0;j<i;++j){
      int from, to, cost;  // 간선의 시작점, 끝점, 가중치
      from = j;
      to = i;
      cost = DBT[(MAX_TRASH+1) * i + j] = DBT[(MAX_TRASH+1) * j + i] = 
        GetPathDistance(nodes[i],nodes[j]);
      graph[from].push_back({to, cost});  // graph[] 에 from에서 to까지 가는 가는 비용 저장
    }
    if(exit) break;
  }
  d.assign(V, INT_MAX);  // 초기 값을 무한대로 저장
  visited.assign(V, 0);  // 방문한 적 없음을 선언
  //
  visit_order.clear();
  visit_order.push_back(0);
  dijkstra(V, graph, 0);
  for(auto& it : visit_order){
    cout << "[" << it << "]" << nodes[it].x << "," << nodes[it].y << endl;
  }  
  // cout << "\t";
  // for(int j = 0;j<MAX_TRASH+1;++j){
  //   cout <<"" << j << "\t";
  // }
  // cout << endl;
  // for(int i = 0;i<MAX_TRASH+1;++i){
  //   cout << i << "\t";
  //   for(int j = 0;j<MAX_TRASH+1;++j){
  //     cout << DBT[(MAX_TRASH+1) * i + j] << "\t";
  //   }
  //   cout << endl;
  // }

  delete[] arrMap;
  return 0;
}

