//#define _TEST

#ifdef _TEST
#include "gtest/gtest.h"
#include <istream>
#include <sstream>
#else
#include <iostream>
#include <vector>
#endif

long long sum(std::vector<int> &a)
{
  long long r = 0;
  for(const auto& it: a){
    r += it;
  }
  return r;
}

#ifdef _TEST
TEST(Test_15596, sum) {
  std::vector<int> a = {1,2};
  long long eVal = 3;
  ASSERT_EQ(sum(a), eVal);
}
#endif

int main(int argc, char **argv) {
#ifndef _TEST
  // sum(std::cin, std::cout);
  // return 0;
#else
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
#endif
}
