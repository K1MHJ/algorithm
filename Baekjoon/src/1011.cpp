//#define _TEST

#ifdef _TEST
#include "gtest/gtest.h"
#include <istream>
#include <sstream>
#include <cmath>
#else
#include <iostream>
#include <cmath>
#endif

void test(std::istream &input, std::ostream &output) {
  int result = 0;
  int c;
  uint32_t x, y;
  uint32_t d;
  input >> c;
  for (int i = 0; i < c; i++) {
    result = 0;
    input >> x >> y;
    d = (y - x);

    double f = d;
    uint32_t h = (int)sqrt(f);
    result = h * 2 - 1;
    uint32_t r = d - h * h;

    while (r > 0) {
      result += r / h;
      r = r % h;
      h--;
    }

    output << result << std::endl;
  }
}

#ifdef _TEST
TEST(Some, Test) {
  std::ostringstream ostr;
  ostr << "3" << std::endl;
  ostr << "0 3" << std::endl;
  ostr << "1 5" << std::endl;
  ostr << "45 50" << std::endl;
  std::ostringstream exp_ostr;
  exp_ostr << "3" << std::endl;
  exp_ostr << "3" << std::endl;
  exp_ostr << "4" << std::endl;

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
