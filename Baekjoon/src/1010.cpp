//#define _TEST

#ifdef _TEST
#include "gtest/gtest.h"
#include <istream>
#include <sstream>
#else
#include <iostream>
#endif

void test(std::istream &input, std::ostream &output) {
  int c, n, m;
  double v; 
  input >> c;
  for (int i = 0; i < c; i++) {
    input >> n >> m;
    v = 1.0;
    for (int j = 0; j < n; j++) {
      v *= (m - j);
      v /= (1+j);
    }
    output << (long long)v << std::endl;
  }
}

#ifdef _TEST
TEST(Some, Test) {
  std::ostringstream ostr;
  ostr << "3" << std::endl;
  ostr << "2 2" << std::endl;
  ostr << "1 5"<< std::endl;
  ostr << "13 29"<< std::endl;
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
