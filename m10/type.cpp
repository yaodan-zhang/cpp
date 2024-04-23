/*
    Functional programming in C++ for type modifications.
*/
#include<tuple>
#include<iostream>
using namespace std;

/* 
    Concatenate the types in two tuples
*/
template<class First, class Second> struct Append;
template<typename... Ts, typename... Us>
struct Append<tuple<Ts...>, tuple<Us...> >
{
using type = tuple<Ts..., Us...>;
};

/*  
    A ReplaceAll<TL, T, U> template that replaces all occurrence of type T in TL with type U.
    For example, ReplaceAll<tuple<char, int, char>,char, double>::type is tuple<double, int, double>.
*/
template<typename T, typename A, typename B> struct ReplaceAll; // primary template - calling format
template<typename T, typename A, typename B>
using ReplaceAll_t = typename ReplaceAll<T,A,B>::type;

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

/* 
    A Reverse template that reverses the types in a tuple.
    For example, Reverse<tuple<A, B>>::type is tuple<B, A>.
*/
template<typename T, typename A, typename B> struct Reverse;
template<typename T>
using Reverse_t = Reverse<t>::type;

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
template<typename H, typename... Ts, typename A, typename B>
struct Reverse<tuple<H, Ts...>, A, B>
: public Append<tuple<H>, typename Reverse<tuple<Ts...>, A, B>::type> {
};
