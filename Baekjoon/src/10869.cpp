#include "gtest/gtest.h"
#include <iostream>
#include <istream>
#include <sstream>

#define _TEST

void test(std::istream &input, std::ostream &output) {
  int value[2];
  input >> value[0] >> value[1];
  output << 1;
}

TEST(Some, Test) {
  std::ostringstream ostr;
  ostr << "7 3";
  std::istringstream istr(ostr.str());
  ostr.str("");
  ostr.clear();
  test(istr, ostr);
  ASSERT_STREQ(ostr.str().c_str(), "2");
}

int main(int argc, char **argv) {
#ifndef _TEST
  test(std::cin, std::cout);
  return 0;
#else
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
#endif
}
