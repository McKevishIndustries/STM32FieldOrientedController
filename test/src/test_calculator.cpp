//
// Created by Kevin McElligott on 29/01/2025.
//

#include <catch2/catch_test_macros.hpp>
#include "calculator.h"

TEST_CASE("factorial tests") {

  CHECK(factorial(1) == 1);
  CHECK(factorial(2) == 2);
  CHECK(factorial(3) == 6);
  CHECK(factorial(4) == 24);
  CHECK(factorial(5) == 120);
  CHECK(factorial(6) == 720);
}
