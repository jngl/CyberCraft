#include <catch.hpp>

#include <ECS/Scene.h>

struct TestComponent {
    int foo;
};
struct TestComponent2 {
    float bar;
};

TEST_CASE( "ECS : Construct", "[ECS][Scene]" ) {
    /*Scene scn;

    REQUIRE( scn.numberOfEntity() == 0 );*/
}

TEST_CASE( "ECS : Create a  Entity", "[ECS][Scene][Entity]" ) {
   /* Scene scn;

    Entity e1 = scn.createEntity();

    REQUIRE( scn.numberOfEntity() == 1);
    REQUIRE( e1.id > 0);

    Entity e2 = scn.createEntity();

    REQUIRE( scn.numberOfEntity() == 2);
    REQUIRE( e2.id > 0);
    REQUIRE( e1.id != e2.id);*/
}

TEST_CASE( "ECS : create a Component", "[ECS][Entity][Scene][Component]" ) {
   /* Scene scn;

    Entity e1 = scn.createEntity();
    Entity e2 = scn.createEntity();
    Entity e3 = scn.createEntity();
    Entity e4 = scn.createEntity();

    {
        auto &c1 = scn.createComponent<TestComponent>(e1);
        c1.foo = 1;

        auto &c2 = scn.createComponent<TestComponent>(e2);
        c2.foo = 2;

        REQUIRE( scn.numberOfComponentType() == 1 );
        REQUIRE( scn.getComponent<TestComponent>(e1) != nullptr );
        REQUIRE( scn.getComponent<TestComponent>(e3) == nullptr );
        REQUIRE( &c1 != &c2 );
    }

    {
        auto& c4 = scn.createComponent<TestComponent2>(e4);
        c4.bar = 3.14f;

        REQUIRE( scn.numberOfComponentType() == 2 );
    }

    {
        auto *c1 = scn.getComponent<TestComponent>(e1);
        auto *c2 = scn.getComponent<TestComponent>(e2);
        auto *c3 = scn.getComponent<TestComponent>(e3);
        auto *c4 = scn.getComponent<TestComponent>(e4);

        REQUIRE(c1 != nullptr);
        REQUIRE(c2 != nullptr);
        REQUIRE(c3 == nullptr);
        REQUIRE(c4 == nullptr);

        REQUIRE(c1->foo == 1);
        REQUIRE(c2->foo == 2);
    }

    {
        auto *c1 = scn.getComponent<TestComponent2>(e1);
        auto *c2 = scn.getComponent<TestComponent2>(e2);
        auto *c3 = scn.getComponent<TestComponent2>(e3);
        auto *c4 = scn.getComponent<TestComponent2>(e4);

        REQUIRE(c1 == nullptr);
        REQUIRE(c2 == nullptr);
        REQUIRE(c3 == nullptr);
        REQUIRE(c4 != nullptr);

        REQUIRE( 3.1399 < c4->bar);
        REQUIRE(c4->bar < 3.1401);
    }*/
}
/*
Scene createScene(){
    return Scene{};
}*/

TEST_CASE( "ECS : iterator", "[ECS][Iterator]" ) {
   /* auto scn = createScene();

    Range range = scn.allEntityWith<TestComponent, TestComponent2>();
    for(auto it: range){
        auto& c1 = it.get<TestComponent>();
        auto& c2 = it.get<TestComponent2>();

        c1.foo++;
        c2.bar+=0.42f;
    }*/
}
 