#include <catch.hpp>
#include <Core/pointer.h>

constexpr int testValue1 = 42;
constexpr int testValue2 = -1;

TEST_CASE( "cc::Ref constructor ptr", "NotNull constructor from ptr" ) {
    REQUIRE_THROWS_AS( cc::Ref<int>(nullptr), cc::NullPointerException);

    int i = testValue1;

    cc::Ref<int> a(&i);
    REQUIRE(*a == testValue1);

    *a = testValue2;
    REQUIRE(i == testValue2);
}

TEST_CASE( "cc::Ref constructor copy", "NotNull constructor from copy" ) {
    int i = testValue1;

    cc::Ref<int> a(&i);
    cc::Ref<int> b(a);

    REQUIRE(*b == testValue1);

    *b = testValue2;
    REQUIRE(i == testValue2);
}

TEST_CASE( "cc::Ref constructor move", "NotNull constructor from copy" ) {
    int i = testValue1;

    cc::Ref<int> a(&i);
    cc::Ref<int> b(std::move(a));

    REQUIRE(*b == testValue1);

    *b = testValue2;
    REQUIRE(i == testValue2);
}

TEST_CASE( "cc::Ref assign copy", "NotNull constructor from copy" ) {
    int i = testValue1;
    int j = testValue2;

    cc::Ref<int> a(&i);
    cc::Ref<int> b(&j);

    a = b;

    REQUIRE(*a == testValue2);
}

TEST_CASE( "cc::Ref assign move", "NotNull constructor from copy" ) {
    int i = testValue1;
    int j = testValue2;

    cc::Ref<int> a(&i);
    cc::Ref<int> b(&j);

    a = std::move(b);

    REQUIRE(*a == testValue2);
}

TEST_CASE( "cc::Ref get", "NotNull constructor from copy" ) {
    int i = testValue1;

    cc::Ref<int> a(&i);
    const cc::Ref<int>& b(a);

    REQUIRE(*b == testValue1);
}
