//
// Created by jngl on 05/12/2020.
//

#include <catch.hpp>
#include <Core/TypeId.h>
#include <unordered_map>

struct Foo{};
struct Bar{};

TEST_CASE( "cc::typeId value" ) {
    REQUIRE(cc::TypeId::get<int>().value() != cc::TypeId::get<float>().value());
}

TEST_CASE( "cc::typeId hashmap" ) {
    std::unordered_map<cc::TypeId, int> map;

    map[cc::TypeId::get<Foo>()] = 1;
    map[cc::TypeId::get<Bar>()] = 2;

    REQUIRE(map[cc::TypeId::get<Foo>()] == 1);
    REQUIRE(map[cc::TypeId::get<Bar>()] == 2);
}
