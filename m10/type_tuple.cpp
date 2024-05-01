/* Functional programming type conversion */
#include<tuple>
#include<iostream>
#include <type_traits>
using namespace std;

/* Appending the types in two tuples */
template<class First, class Second> struct Append;
template<typename... Ts, typename... Us>
struct Append<tuple<Ts...>, tuple<Us...> >
{
using type = tuple<Ts..., Us...>;
};

/*  
    A ReplaceAll<TL, T, U> template that replaces all occurrence of T in TL with U.
    For example, ReplaceAll<tuple<char, int, char>,char, double>::type 
    should be tuple<double, int, double>
*/
template<typename T, typename A, typename B> struct ReplaceAll;
template<typename A, typename B>
struct ReplaceAll<tuple<>, A, B> {
using type = tuple<>;
};
template<typename... Ts, typename A, typename B>
struct ReplaceAll<tuple<A, Ts...>, A, B>
: public Append<tuple<B>, typename ReplaceAll<tuple<Ts...>, A, B>::type> {
};
template<typename H, typename... Ts, typename A, typename B>
struct ReplaceAll<tuple<H, Ts...>, A, B>
: public Append<tuple<H>, typename ReplaceAll<tuple<Ts...>, A, B>::type> {
};

static_assert(is_same_v<ReplaceAll<tuple<char, int, char>,char,double>::type, tuple<double, int, double>>);

/* 
    A Reverse template that reverses the parameters of a tuple
    For example, Reverse<tuple<A, B, C, B>, A, B>::type will be tuple<B, A, C, A>
*/
template<typename T, typename A, typename B> struct Reverse;
template<typename A, typename B>
struct Reverse<tuple<>, A, B> {
using type = tuple<>;
};
// Replace A with B
template<typename... Ts, typename A, typename B>
struct Reverse<tuple<A, Ts...>, A, B>
: public Append<tuple<B>, typename Reverse<tuple<Ts...>, A, B>::type> {
};
// Replace B with A
template<typename... Ts, typename A, typename B>
struct Reverse<tuple<B, Ts...>, A, B>
: public Append<tuple<A>, typename Reverse<tuple<Ts...>, A, B>::type> {
};
// Skip
template<typename H, typename... Ts, typename A, typename B>
struct Reverse<tuple<H, Ts...>, A, B>
: public Append<tuple<H>, typename Reverse<tuple<Ts...>, A, B>::type> {
};

static_assert(is_same_v<Reverse<tuple<char, int>, char, int>::type, tuple<int, char>>);
static_assert(is_same_v<Reverse<tuple<char, int, double, int>, int, char>::type, tuple<int, char, double, char>>);
