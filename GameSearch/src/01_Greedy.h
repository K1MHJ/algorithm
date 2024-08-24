#include "00_MazeState.h"

using ScoreType = int64_t;
constexpr const ScoreType INF = 1000000000LL;

class Greedy : public MazeState {
public:
  Greedy(int seed) : MazeState(seed) {}

public:
  ScoreType evaluated_score = 0;
  void evaluateScore() { this->evaluated_score = this->game_score_; }
};
