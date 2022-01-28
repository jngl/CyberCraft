//
// Created by jngl on 05/12/2020.
//

#include <catch.hpp>
#include <CyberBase/typeName.h>

class Foo{};

constexpr std::string_view intTypeName = cc::typeName<int>();
constexpr std::string_view fooTypeName = cc::typeName<Foo>();

TEST_CASE( "cc::typeName" ) {
    REQUIRE(intTypeName == "int");
    REQUIRE(fooTypeName == "Foo");
}