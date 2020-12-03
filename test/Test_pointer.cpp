#include <catch.hpp>
#include <Core/pointer.h>

constexpr int testValue1 = 42;
constexpr int testValue2 = -1;

class Foo{
public:
    void a(){}
};

class Bar : public Foo{};

TEST_CASE( "cc::Ref constructor ref" ) {
    int i = testValue1;

    cc::Ref<int> a(i);
    REQUIRE(*a == testValue1);

    *a = testValue2;
    REQUIRE(i == testValue2);
}

TEST_CASE( "cc::Ref constructor copy" ) {
    int i = testValue1;

    cc::Ref<int> a(i);
    cc::Ref<int> b(a);

    REQUIRE(*b == testValue1);

    *b = testValue2;
    REQUIRE(i == testValue2);
}

TEST_CASE( "cc::Ref constructor move" ) {
    int i = testValue1;

    cc::Ref<int> a(i);
    cc::Ref<int> b(std::move(a));

    REQUIRE(*b == testValue1);

    *b = testValue2;
    REQUIRE(i == testValue2);
}

TEST_CASE( "cc::Ref assign copy" ) {
    int i = testValue1;
    int j = testValue2;

    cc::Ref<int> a(i);
    cc::Ref<int> b(j);

    a = b;

    REQUIRE(*a == testValue2);
}

TEST_CASE( "cc::Ref assign move" ) {
    int i = testValue1;
    int j = testValue2;

    cc::Ref<int> a(i);
    cc::Ref<int> b(j);

    a = std::move(b);

    REQUIRE(*a == testValue2);
}

TEST_CASE( "cc::Ref get" ) {
    int i = testValue1;

    cc::Ref<int> a(i);
    const cc::Ref<int>& b(a);

    REQUIRE(*b == testValue1);
}

TEST_CASE( "cc::Ref ->" ) {
    Foo a;

    cc::Ref<Foo> b(a);

    b->a();
}

TEST_CASE( "cc::make_ref" ) {
    Bar a;

    cc::Ref<Foo> b = cc::make_ref(a);

    b->a();
}

TEST_CASE( "cc::OptionalRef default constructor" ) {
    cc::OptionalRef<int> a;

    REQUIRE(a == nullptr);
}

TEST_CASE( "cc::OptionalRef construct from ptr" ) {
    int i = testValue1;

    cc::OptionalRef<int> a(&i);

    REQUIRE(a == &i);
}

TEST_CASE( "cc::OptionalRef construct from ref" ) {
    int i = testValue1;

    cc::OptionalRef<int> a(i);

    REQUIRE(a == &i);
}

TEST_CASE( "cc::OptionalRef construct from copy" ) {
    int i = testValue1;

    cc::OptionalRef<int> a(i);
    cc::OptionalRef<int> b(a);

    REQUIRE(b == &i);
}

TEST_CASE( "cc::OptionalRef construct from move" ) {
    int i = testValue1;

    cc::OptionalRef<int> a(i);
    cc::OptionalRef<int> b(std::move(a));

    REQUIRE(b == &i);
}

TEST_CASE( "cc::OptionalRef assign copy" ) {
    int i = testValue1;

    cc::OptionalRef<int> a(i);
    cc::OptionalRef<int> b;

    b = a;

    REQUIRE(b == &i);
}

TEST_CASE( "cc::OptionalRef assign move" ) {
    int i = testValue1;

    cc::OptionalRef<int> a(i);
    cc::OptionalRef<int> b;

    b = a;

    REQUIRE(b == &i);
}

