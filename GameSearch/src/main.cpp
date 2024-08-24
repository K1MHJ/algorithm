#include "00_MazeState.h"
#include "01_Greedy.h"

using State = Greedy;

std::mt19937 mt_for_action(0);
int randomAction(const State &state) {
  auto legal_actions = state.legalActions();
  return legal_actions[mt_for_action() % (legal_actions.size())];
}

void playGame(const int seed) {
  using std::cout;
  using std::endl;

  auto state = State(seed);
  cout << state.toString() << endl;
  while (!state.isDone()) {
    state.advance(randomAction(state));
    cout << state.toString() << endl;
  }
}
int main()
{
  using std::cout;
  using std::endl;
  playGame(121321);
  return 0;
}
