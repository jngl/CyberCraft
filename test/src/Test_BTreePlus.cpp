#include <catch.hpp>
#include <Core/BTreePlus.h>
#include <string>

TEST_CASE( "BTreePlus", "[BTreePlus]" ) {
    BTreePlus<int, std::string, 4> bt;

    SECTION( "After construct" ) {
        REQUIRE( bt.size() == 0 );
        REQUIRE_THROWS_AS( bt.get(0), std::out_of_range);
    }

    SECTION( "Add 1" ) {
        bt.insert(1, "1");

        REQUIRE( bt.size() == 1 );
        REQUIRE( bt.get(1) == "1" );
    }
}

