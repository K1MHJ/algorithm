#include "gtest/gtest.h"
#include <iostream>
#include <istream>
#include <sstream>

#define _TEST

void test(std::istream &input, std::ostream &output) {
  int A,B;
  input >> A >> B;
  output << A+B << std::endl;
  output << A-B << std::endl;
  output << A*B << std::endl;
  output << A/B << std::endl;
  output << A%B << std::endl;
}

TEST(Some, Test) {
  std::ostringstream ostr;
  ostr << "7 3";
  std::ostringstream exp_ostr;
  exp_ostr << "10\n4\n21\n2\n1\n";

  std::istringstream istr(ostr.str());
  ostr.str("");
  ostr.clear();
  test(istr, ostr);
  ASSERT_STREQ(ostr.str().c_str(), exp_ostr.str().c_str());
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
