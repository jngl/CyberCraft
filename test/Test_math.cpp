//
// Created by jngl on 05/06/2021.
//

#include <catch.hpp>
#include <Core/Math.h>

TEST_CASE( "math::equal" ) {
    REQUIRE(!cc::equal<float>(-42.f, 1.f));
    REQUIRE(!cc::equal<float>(1.f, 42.f));
    REQUIRE(cc::equal<float>(1.f, 1.0000001f));
}

TEST_CASE( "math::fractionalPart" ) {
    constexpr float a = 0;
    constexpr float b = 100;

    REQUIRE(cc::mix(a, b, 0.f) == a);
    REQUIRE(cc::mix(a, b, 1.f) == b);
    REQUIRE(cc::mix(a, b, 0.5f) == a/2 + b/2);
}

TEST_CASE( "math::mix" ) {
    REQUIRE(cc::equal<float>(cc::fractionalPart(42.666f),0.666f));
}
