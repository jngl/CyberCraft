//
// Created by jngl on 21/08/2021.
//

#include <catch.hpp>
#include <Core/Component.h>
#include <Core/Common.h>
#include <Core/Id.h>

using Id = cc::Id<cc::Uint16, struct id>;

struct Comp {
    int value = 0;
};

TEST_CASE( "cc::ComponentManager" ) {
    constexpr int value = 42;
    Id id(0);

    cc::ComponentManager<Comp, Id> componentManager;

    { // Construct
        cc::OptionalRef<Comp> comp = componentManager.get(id);
        REQUIRE(!comp.hasValue());
    }

    { // create
        Comp &comp2 = componentManager.create(id);
        comp2.value = value;

        cc::OptionalRef<Comp> comp3 = componentManager.get(id);
        REQUIRE(comp3.hasValue());
        REQUIRE(comp3->value == value);
    }

    { // destroy
        componentManager.destroy(Id(0));

        cc::OptionalRef<Comp> comp4 = componentManager.get(id);
        REQUIRE(!comp4.hasValue());
    }
}
