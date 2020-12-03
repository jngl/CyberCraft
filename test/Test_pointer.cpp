#include <catch.hpp>
#include <Core/pointer.h>

constexpr int testValue1 = 42;
constexpr int testValue2 = -1;

TEST_CASE( "ccCore::Ref constructor ptr", "NotNull constructor from ptr" ) {
    REQUIRE_THROWS_AS( ccCore::Ref<int>(nullptr), ccCore::NullPointerException);

    int i = testValue1;

    ccCore::Ref<int> a(&i);
    REQUIRE(*a == testValue1);

    *a = testValue2;
    REQUIRE(i == testValue2);
}

TEST_CASE( "ccCore::Ref constructor copy", "NotNull constructor from copy" ) {
    int i = testValue1;

    ccCore::Ref<int> a(&i);
    ccCore::Ref<int> b(a);

    REQUIRE(*b == testValue1);

    *b = testValue2;
    REQUIRE(i == testValue2);
}

TEST_CASE( "ccCore::Ref constructor move", "NotNull constructor from copy" ) {
    int i = testValue1;

    ccCore::Ref<int> a(&i);
    ccCore::Ref<int> b(std::move(a));

    REQUIRE(*b == testValue1);

    *b = testValue2;
    REQUIRE(i == testValue2);
}

TEST_CASE( "ccCore::Ref assign copy", "NotNull constructor from copy" ) {
    int i = testValue1;
    int j = testValue2;

    ccCore::Ref<int> a(&i);
    ccCore::Ref<int> b(&j);

    a = b;

    REQUIRE(*a == testValue2);
}

TEST_CASE( "ccCore::Ref assign move", "NotNull constructor from copy" ) {
    int i = testValue1;
    int j = testValue2;

    ccCore::Ref<int> a(&i);
    ccCore::Ref<int> b(&j);

    a = std::move(b);

    REQUIRE(*a == testValue2);
}

TEST_CASE( "ccCore::Ref get", "NotNull constructor from copy" ) {
    int i = testValue1;

    ccCore::Ref<int> a(&i);
    const ccCore::Ref<int>& b(a);

    REQUIRE(*b == testValue1);
}
