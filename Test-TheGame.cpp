#include "catch.hpp"
#include "TheGame.h"
#include "TheGame.cpp"



TheGame<int> theGameTest;

TEST_CASE( "Konstruktor moveCurrentBlock") {
REQUIRE( theGameTest.move_current_block(1) == 1 );
REQUIRE( Factorial(2) == 2 );
REQUIRE( Factorial(3) == 6 );
REQUIRE( Factorial(10) == 3628800 );
}
