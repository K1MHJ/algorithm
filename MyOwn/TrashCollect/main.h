#pragma once
#include <math.h>
#include <vector>

#define MAX_W 20
#define MAX_H 20
#define MAX_TRASH 10

typedef struct{
  int x;
  int y;
}POS;

typedef enum{
  UP,
  DOWN,
  LEFT,
  RIGHT,
  MAX
}DIR;

bool GetSearch(int x, int y);
void SetSearch(int x, int y, bool s);
void ClearSearch();

class Cell{
public:
  Cell(POS _pos):g(0),h(0),pos(_pos)
  {
  }
  POS pos;
  int g;
  int h;//heuristic cost
};

class Node{
public:
  Node(POS pos, Node* parent);
  ~Node();
  Node* AddChild(POS pos);

  Cell cell;
  Node* parent_node;
  Node* neargoal_node;
  std::vector<Node*> neighbour_nodes;
};

struct cmp{
  bool operator()(Node* n1, Node* n2){
    if(n1->cell.g + n1->cell.h < n2->cell.g + n2->cell.h){
      return false;
    }
    return true;
  }
};

int ManhattanDist(const POS& a, const POS& b);
bool AroundPos(POS& pos, int x, int y, DIR dir, char* org, int w, int h);
