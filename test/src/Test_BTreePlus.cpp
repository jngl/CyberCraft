#include <catch.hpp>
#include <Core/BTreePlus.h>
#include <string>

TEST_CASE( "BTreePlus", "[BTreePlus]" ) {
    ccCore::BTreePlus<int, std::string, 4> bt;

    // After construct
    REQUIRE( bt.size() == 0 );
    REQUIRE_THROWS_AS( bt.get(0), std::out_of_range);

    // first insert
    bt.insert(1, "1");

    REQUIRE( bt.size() == 1 );
    REQUIRE( bt.get(1) == "1" );

    // second insert
    bt.insert(5, "5");

    REQUIRE( bt.size() == 2 );
    REQUIRE( bt.get(5) == "5" );
}

