//
// Created by jngl on 05/12/2020.
//

#include <catch.hpp>
#include <Core/Id.h>


TEST_CASE( "cc::Id Generator" ) {
    using IdGenerator = cc::IdGenerator<unsigned int, struct TestId>;
    using Id = IdGenerator::ThisId;

    IdGenerator gen;

    Id a = gen.create();
    Id b = gen.create();
    gen.destroy(a);
    Id c = gen.create();
    Id d = gen.create();
    Id e = gen.create();
    gen.destroy(c);
    gen.destroy(b);
    gen.destroy(b);
    gen.destroy(e);
    gen.destroy(d);

    REQUIRE(gen.sizeOfAvailableIds() == std::numeric_limits<unsigned int>::max()-1);

}

TEST_CASE( "cc::Id Generator full" ) {
    using IdGenerator = cc::IdGenerator<unsigned char, struct TestIdFull>;
    using Id = IdGenerator::ThisId;

    IdGenerator gen;

    for(int i=0; i<255; ++i){
        Id id = gen.create();
        REQUIRE(id.isValid());
    }

    Id id = gen.create();
    REQUIRE(!id.isValid());
}