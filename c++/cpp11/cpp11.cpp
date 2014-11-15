#include "stdafx.h"
#include "Set.h"

// Compile this with VS2013

// N1720: static asserts
template <typename T>
struct Check {
    static_assert(sizeof(int) <= sizeof(T), "not big enough");
};

// N2541: trailing return types
// N3276: decltype
template<class T>
auto mul(T a, T b) -> decltype(a*b)
{
    return a*b;
}

// N2927: lambdas
void abssort(float *x, unsigned N)
{
    std::sort(x, x + N,
    [](float a, float b) {
        return std::abs(a) < std::abs(b);
    });
}

// N1987: extern template!
extern template class std::vector<int>;

// N1791: extended friend declaration
template <class T> class B {
    friend T;
};

template <class T>
void foo(T t)
{
}

int _tmain(int argc, _TCHAR* argv[])
{
    Check<long> okChecker; // Check<uint8_t> WON'T COMPILE -- GOOD!
    okChecker;

    uint64_t a = mul<uint64_t>(3, 4);

    float f[] = { 3, 1, 5, 4, 9 };
    abssort(f, sizeof(f) / sizeof(float));

    // N1757: right angle brackets works now!
    typedef vector<vector<int>> VVInt;

    // N2431: nullptr
    int* p = nullptr;

    // N2347: strongly typed enums
    enum class Color {
        RED, GREEN, BLUE
    };
    enum class Feelings {
        EXCITED, MOODY, BLUE
    };

    // N2764:	forward declared enums
    enum myEnum : uint8_t;

    B<Check<int>> b;
    b;

    // N2930: range based for-loop
    for (float& x : f)
        x *= 2;

    // N2657: local and unnamed types as template arguments
    struct Local {
        int a, b;
    } local = { 1, 2 };
    enum { Red, Orange, Green };
    foo(local);
    foo(Orange);

    Set<int> set1 { 123, 456, 789, 101112 };
    Set<int> set2 { 456, 789, 101112, 131415 };
    Set<int> set3 = set1 + set2;

    return 0;
}

