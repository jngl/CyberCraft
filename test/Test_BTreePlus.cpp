#include <catch.hpp>
#include <Core/BTreePlus.h>
#include <string>

TEST_CASE( "BTreePlus", "[BTreePlus]" ) {
    ccCore::BTreePlus<int, std::string, 4> bt;

    // After construct
    REQUIRE( bt.size() == 0 );
    REQUIRE_THROWS_AS( bt.get(0), std::out_of_range);

    // first insert
    constexpr const char* firstInsertValueStr = "1";
    constexpr int firstInsertValueInt = 1;

    bt.insert(firstInsertValueInt, firstInsertValueStr);

    REQUIRE( bt.size() == 1 );
    REQUIRE( bt.get(firstInsertValueInt) == firstInsertValueStr );

    // second insert
    constexpr const char* secondInsertValueStr = "5";
    constexpr int secondInsertValueInt = 5;

    bt.insert(secondInsertValueInt, secondInsertValueStr);

    REQUIRE( bt.size() == 2 );
    REQUIRE( bt.get(secondInsertValueInt) == secondInsertValueStr );
}

