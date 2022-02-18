#include <iostream>
#include "ryu.h"

int
main ()
{
  double a = 2.1471;
  std::string a_str = d2fixed(a, 8);
  std::cout << a_str << std::endl;

  return 0;
}
