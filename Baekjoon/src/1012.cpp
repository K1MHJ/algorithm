//#define _TEST

#ifdef _TEST
#include "gtest/gtest.h"
#include <cmath>
#include <istream>
#include <sstream>
#endif
#include <iostream>

uint8_t field[51][51];
bool check[51][51];
int W, H;
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};
bool dfs(int y, int x) {
  if (check[y][x]) {
    return false;
  }
  check[y][x] = true;
  for (int i = 0; i < 4; i++) {
    int next_x = x + dx[i];
    int next_y = y + dy[i];
    if (0 <= next_x && 0 <= next_y && next_x < W && next_y < H &&
        field[next_y][next_x] == 1) {
      dfs(next_y, next_x);
    }
  }
  return true;
}
void test(std::istream &input, std::ostream &output) {
  int T, K;
  int result = 0;
  input >> T;
  for (int i = 0; i < T; i++) {
    input >> W >> H >> K;
    for (int y = 0; y < H; y++) {
      for (int x = 0; x < W; x++) {
        field[y][x] = 0;
        check[y][x] = false;
      }
    }
    for (int j = 0; j < K; j++) {
      int X, Y;
      input >> X >> Y;
      field[Y][X] = 1;
    }

    result = 0;
    for (int y = 0; y < H; y++) {
      for (int x = 0; x < W; x++) {
        if (1 == field[y][x] && !check[y][x]) {
          if (dfs(y, x))
            result++;
        }
      }
    }
    output << result << std::endl;
  }
}

#ifdef _TEST
TEST(Some, Test1) {
  std::ostringstream ostr;
  ostr << "1" << std::endl;
  ostr << "5 3 6" << std::endl;
  ostr << "0 2" << std::endl;
  ostr << "1 2" << std::endl;
  ostr << "2 2" << std::endl;
  ostr << "3 2" << std::endl;
  ostr << "4 2" << std::endl;
  ostr << "4 0" << std::endl;

  std::ostringstream exp_ostr;
  exp_ostr << "2" << std::endl;

  std::istringstream istr(ostr.str());
  ostr.str("");
  ostr.clear();
  test(istr, ostr);
  ASSERT_STREQ(ostr.str().c_str(), exp_ostr.str().c_str());
}
TEST(Some, Test2) {
  std::ostringstream ostr;
  ostr << "2" << std::endl;
  ostr << "10 8 17" << std::endl;
  ostr << "0 0" << std::endl;
  ostr << "1 0" << std::endl;
  ostr << "1 1" << std::endl;
  ostr << "4 2" << std::endl;
  ostr << "4 3" << std::endl;
  ostr << "4 5" << std::endl;
  ostr << "2 4" << std::endl;
  ostr << "3 4" << std::endl;
  ostr << "7 4" << std::endl;
  ostr << "8 4" << std::endl;
  ostr << "9 4" << std::endl;
  ostr << "7 5" << std::endl;
  ostr << "8 5" << std::endl;
  ostr << "9 5" << std::endl;
  ostr << "7 6" << std::endl;
  ostr << "8 6" << std::endl;
  ostr << "9 6" << std::endl;
  ostr << "10 10 1" << std::endl;
  ostr << "5 5" << std::endl;

  std::ostringstream exp_ostr;
  exp_ostr << "5" << std::endl;
  exp_ostr << "1" << std::endl;

  std::istringstream istr(ostr.str());
  ostr.str("");
  ostr.clear();
  test(istr, ostr);
  ASSERT_STREQ(ostr.str().c_str(), exp_ostr.str().c_str());
}
#endif

int main(int argc, char **argv) {
#ifndef _TEST
  test(std::cin, std::cout);
  return 0;
#else
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
#endif
}
