#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <array>
#include <list>
#include <queue>
#include "main.h"
using namespace std;

extern POS goal_pos;

bool mapSearch[MAX_H * MAX_W];

bool GetSearch(int x, int y){
  return mapSearch[y * MAX_W + x];
}
void SetSearch(int x, int y, bool s){
  mapSearch[y * MAX_W + x] = s;
}
void ClearSearch(){
  for(int i = 0;i<MAX_H * MAX_W; ++i){
    mapSearch[i] = false;
  }
}

int ManhattanDist(const POS& a, const POS& b)
{
  return abs(a.x - b.x) + abs(a.y - b.y);
}
Node::~Node()
{
  for(auto& it : neighbour_nodes){
    delete it;
  }
  neighbour_nodes.clear();
}
Node::Node(POS pos, Node* parent):
  cell(pos),
  parent_node(parent)
{
  if(parent == nullptr){
    cell.g = 0;
  }else{
    cell.g = parent->cell.g + 1;
  }
  cell.h = ManhattanDist(pos, goal_pos);
}
Node* Node::AddChild(POS pos){
  for(auto& n : neighbour_nodes){
    if(n->cell.pos.x == pos.x && n->cell.pos.y == pos.y){
      return n;
    }
  }
  neighbour_nodes.push_back(new Node(pos, this));
  return *neighbour_nodes.rbegin();
}

bool AroundPos(POS& pos, int x, int y, DIR dir, char* org, int w, int h)
{
  int offset = 0;
  switch(dir){
    case DIR::UP: offset = -w;break;
    case DIR::DOWN: offset = w;break;
    case DIR::RIGHT:offset = 1;break;
    case DIR::LEFT:offset = -1;break;
    default:
      return false;
  }
  int i = y * w + x + offset;
  if(i < 0){
    return false;
  }
  if(i > w * h){
    return false;
  }
  if(org[i] == '0'){
    return false;
  }
  pos.x = i % w;
  pos.y = i / w;
  return true;
}
void run(char* arrMap, int map_w, int map_h, int &nx, int &ny)
{
  POS start, goal;
  start.x = -1;
  start.y = -1;
  goal.x = -1;
  goal.y = -1;
  for(int i = 0;i<map_h;++i){
    for(int j = 0;j<map_w;++j){
      if('S' == arrMap[i * map_w + j]){
        start.x = j;
        start.y = i;
      }
      else if('G' == arrMap[i * map_w + j]){
        goal.x = j;
        goal.y = i;
      }
    }
  }
  cout <<"start: "<< start.x << " " << start.y << endl;
  cout <<"goal: "<< goal.x << " " << goal.y << endl;
  goal_pos = goal;

  Node topNode(start, nullptr);
  std::priority_queue<Node*, std::vector<Node*>, cmp> searchingCells;
  SetSearch(start.x, start.y, true);
  POS pos = start;
  POS nPos;
  for(int i = 0;i<DIR::MAX;++i){
    if(AroundPos(nPos, pos.x, pos.y, (DIR)i, arrMap, map_w, map_h)){
      cout << nPos.x << "," << nPos.y << endl;
      Node* n = topNode.AddChild(nPos);
      searchingCells.push(n);
    }
  }
  cout << searchingCells.top()->cell.pos.x << endl;
  cout << searchingCells.top()->cell.pos.y << endl;

  std::vector<Node*> findPath;
  bool found_path = false;
  while(true){
    auto node = searchingCells.top();
    cout << "[Next] " << node->cell.pos.x << "," <<node->cell.pos.y << endl;

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
}

int _main()
{
  for(int i = 0;i<MAX_W;++i){
    for(int j = 0;j<MAX_H;++j){
      SetSearch(i,j,false);
    }
  }
  int map_w, map_h;
  std::vector<std::string> map = {
      "000000000",
      "0 S0 0 G0",
      "0 00    0",
      "0  0 0  0",
      "0    0  0",
      "000000000"
  };
  map_h = map.size();
  map_w = map.begin()->length();
  char *arrMap = new char[map_h * map_w];
  for(int i = 0;i<map_h;i++){
    for(int j = 0;j<map[i].length();j++){
      arrMap[i * map_w + j] = map[i].c_str()[j];
    }
  }
  int nx,ny;
  run(arrMap, map_w, map_h, nx, ny);
  return 0;
}

