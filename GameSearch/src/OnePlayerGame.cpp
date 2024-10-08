// Copyright [2022] <Copyright Eita Aoki (Thunder) >
#include <chrono>
#include <iostream>
#include <queue>
#include <random>
#include <sstream>
#include <string>

// 座標を保持する
struct Coord {
  int y_;
  int x_;
  Coord(const int y = 0, const int x = 0) : y_(y), x_(x) {}
};

class TimeKeeper {
private:
  std::chrono::high_resolution_clock::time_point start_time_;
  int64_t time_threshold_;

public:
  TimeKeeper(const int64_t &time_threshold)
      : start_time_(std::chrono::high_resolution_clock::now()),
        time_threshold_(time_threshold) {}
  bool isTimeOver() const {
    auto diff = std::chrono::high_resolution_clock::now() - start_time_;
    return std::chrono::duration_cast<std::chrono::milliseconds>(diff)
               .count() >= time_threshold_;
  }
};

std::mt19937 mt_for_action(0); // 行動選択用の乱数生成器を初期化
using ScoreType = int64_t; // ゲームの評価スコアの型を決めておく。
constexpr const ScoreType INF =
    1000000000LL; // あり得ないぐらい大きなスコアの例を用意しておく

constexpr const int H = 30;  // 迷路の高さ
constexpr const int W = 30;  // 迷路の幅
constexpr int END_TURN = 100; // ゲーム終了ターン

// 一人ゲームの例
// 1ターンに上下左右四方向のいずれかに1マスずつ進む。
// 床にあるポイントを踏むと自身のスコアとなり、床のポイントが消える。
// END_TURNの時点のスコアを高くすることが目的
class MazeState {
private:
  static constexpr const int dx[4] = {1, -1, 0,
                                      0}; // 右、左、下、上への移動方向のx成分
  static constexpr const int dy[4] = {0, 0, 1,
                                      -1}; // 右、左、下、上への移動方向のy成分

  int points_[H][W] = {}; // 床のポイントを1~9で表現する
  int turn_ = 0;          // 現在のターン

public:
  Coord character_ = Coord();
  int game_score_ = 0;            // ゲーム上で実際に得たスコア
  ScoreType evaluated_score_ = 0; // 探索上で評価したスコア
  int first_action_ = -1;
  MazeState() {}

  // h*wの迷路を生成する。
  MazeState(const int seed) {
    auto mt_for_construct =
        std::mt19937(seed); // 盤面構築用の乱数生成器を初期化
    this->character_.y_ = mt_for_construct() % H;
    this->character_.x_ = mt_for_construct() % W;

    for (int y = 0; y < H; y++)
      for (int x = 0; x < W; x++) {
        if (y == character_.y_ && x == character_.x_) {
          continue;
        }
        this->points_[y][x] = mt_for_construct() % 10;
      }
  }

  // [どのゲームでも実装する] : ゲームの終了判定
  bool isDone() const { return this->turn_ == END_TURN; }
  // [どのゲームでも実装する] : 探索用の盤面評価をする
  void evaluateScore() {
    this->evaluated_score_ =
        this->game_score_; // 簡単のため、まずはゲームスコアをそのまま盤面の評価とする
  }
  // [どのゲームでも実装する] : 指定したactionでゲームを1ターン進める
  void advance(const int action) {
    this->character_.x_ += dx[action];
    this->character_.y_ += dy[action];
    auto &point = this->points_[this->character_.y_][this->character_.x_];
    if (point > 0) {
      this->game_score_ += point;
      point = 0;
    }
    this->turn_++;
  }

  // [どのゲームでも実装する] : 現在の状況でプレイヤーが可能な行動を全て取得する
  std::vector<int> legalActions() const {
    std::vector<int> actions;
    for (int action = 0; action < 4; action++) {
      int ty = this->character_.y_ + dy[action];
      int tx = this->character_.x_ + dx[action];
      if (ty >= 0 && ty < H && tx >= 0 && tx < W) {
        actions.emplace_back(action);
      }
    }
    return actions;
  }

  // [実装しなくてもよいが実装すると便利] : 現在のゲーム状況を文字列にする
  std::string toString() const {
    std::stringstream ss;
    ss << "turn:\t" << this->turn_ << "\n";
    ss << "score:\t" << this->game_score_ << "\n";
    for (int h = 0; h < H; h++) {
      for (int w = 0; w < W; w++) {
        if (this->character_.y_ == h && this->character_.x_ == w) {
          ss << '@';
        } else if (this->points_[h][w] > 0) {
          ss << points_[h][w];
        } else {
          ss << '.';
        }
      }
      ss << '\n';
    }

    return ss.str();
  }
};

using State = MazeState;

// ランダムに行動を決定する
int randomAction(const State &state) {
  auto legal_actions = state.legalActions();
  return legal_actions[mt_for_action() % (legal_actions.size())];
}

bool operator<(const MazeState &maze_1, const MazeState &maze_2) {
  return maze_1.evaluated_score_ < maze_2.evaluated_score_;
}

int chokudaiSearchActionWithTimeThreshold(const State &state, const int beam_width,
                         const int beam_depth, const int64_t time_threshold) {
  auto time_keeper = TimeKeeper(time_threshold);
  auto beam = std::vector<std::priority_queue<State>>(beam_depth + 1);

  for (int t = 0; t < beam_depth + 1; ++t) {
    beam[t] = std::priority_queue<State>();
  }
  beam[0].push(state);
  for (int cnt = 0; ; ++cnt) {
    for (int t = 0; t < beam_depth; ++t) {
      auto &now_beam = beam[t];
      auto &next_beam = beam[t + 1];
      for (int i = 0; i < beam_width; ++i) {
        if (now_beam.empty()) {
          break;
        }
        State now_state = now_beam.top();
        if (now_state.isDone()) {
          break;
        }
        now_beam.pop();
        auto legal_actions = now_state.legalActions();
        for (const auto &action : legal_actions) {
          State next_state = now_state;
          next_state.advance(action);
          next_state.evaluateScore();
          if (t == 0) {
            next_state.first_action_ = action;
          }
          next_beam.push(next_state);
        }
      }
    }
    if(time_keeper.isTimeOver()){
      break;
    }
  }
  for (int t = beam_depth; t >= 0; t--) {
    const auto &now_beam = beam[t];
    if (!now_beam.empty()) {
      return now_beam.top().first_action_;
    }
  }
  return -1;
}

// ゲームをgame_number回プレイして平均スコアを表示する
void testAiScore(const int game_number) {
  using std::cout;
  using std::endl;
  std::mt19937 mt_for_construct(0);
  double score_mean = 0;
  for (int i = 0; i < game_number; i++) {
    auto state = State(mt_for_construct());
    bool isfirst = true;
    while (!state.isDone()) {
      state.advance(chokudaiSearchActionWithTimeThreshold(state, 1, END_TURN, 1));
      if (isfirst) {
        isfirst = false;
      }
    }
    auto score = state.game_score_;
    score_mean += score;
  }
  score_mean /= (double)game_number;
  cout << "Score:\t" << score_mean << endl;
}
int main() {
  testAiScore(/*ゲームを繰り返す回数*/ 100);
  return 0;
}
