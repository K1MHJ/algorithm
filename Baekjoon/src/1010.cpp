#define _TEST

#ifdef _TEST
#include "gtest/gtest.h"
#include <istream>
#include <sstream>
#else
#include <iostream>
#endif

void test(std::istream &input, std::ostream &output) {
  int c, n, m;
  int n_link[30];

  input >> c;
  for (int i = 0; i < c; i++) {
    input >> n >> m;

    bool end = true;
    for (int j = 1; j < n; j++) {
      if (n_link[n - j] != m - j){
        end = false;
        break;
      }
    }
  }
  // output << A%B << /std::endl;
}

#ifdef _TEST
TEST(Some, Test) {
  std::ostringstream ostr;
  ostr << "3";
  ostr << "2 2";
  ostr << "1 5";
  ostr << "13 29";
  std::ostringstream exp_ostr;
  exp_ostr << "1" << std::endl;
  exp_ostr << "5" << std::endl;
  exp_ostr << "67863915" << std::endl;

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
