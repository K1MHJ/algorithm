//#define _TEST

#ifdef _TEST
#include "gtest/gtest.h"
#include <istream>
#include <sstream>
#else
#include <iostream>
#endif

void test(std::istream &input, std::ostream &output) {
  int n;
  int p_n;
  input >> n;
  int p_n_1;
  int p_n_2;
  p_n = 0;
  p_n_1 = 1;
  p_n_2 = 0;
  if (n == 0) {
    p_n = p_n_2;
  } else if (n == 1) {
    p_n = p_n_1;
  } else {
    for (int i = 1; i < n; i++) {
      p_n = p_n_1 + p_n_2;
      p_n_2 = p_n_1;
      p_n_1 = p_n;
    }
  }
  output << p_n;
}

#ifdef _TEST
TEST(Pibonacci, Test) {
  std::ostringstream ostr;
  ostr << "10";
  std::ostringstream exp_ostr;
  exp_ostr << "55";

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
