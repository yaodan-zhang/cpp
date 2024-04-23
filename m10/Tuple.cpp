/*
    Implement a Tuple struct so that we can get elements from it by type as well as index.
    See main() below for usage.
*/
#include<iostream>
using namespace std;

template<typename ...Ts> struct Tuple;

// Specializations:
template<> struct Tuple<> {};

template<typename T, typename ...Ts>
struct Tuple<T, Ts...> : public Tuple<Ts...>
{
	Tuple(T const &t, Ts const &... ts) : Tuple<Ts...>(ts...), val(t) {}
	T val;
};

// Getter function that get elements from Tuple by index
template<int i, typename ...Ts>
struct Getter;

template<typename T, typename ...Ts>
struct Getter<0, T, Ts...> {
	static auto &get(Tuple<T, Ts...> &tup) {
		return tup.val;
	}
};

template<int i, typename T, typename ...Ts>
struct Getter<i, T, Ts...> {
	static auto &get(Tuple<T, Ts...> &tup) {
		return Getter<i - 1, Ts...>::get(static_cast<Tuple<Ts...>&>(tup));
	}
};

template<int i, typename ...Ts>
auto &
get(Tuple<Ts...> &tup) {
	return Getter<i, Ts...>::get(tup);
}

// Getter function that get elements from Tuple by type
template<typename A, typename ...Ts>
struct Getter2;

template<typename T, typename ...Ts>
struct Getter2<T, T, Ts...> {
	static auto &get(Tuple<T, Ts...> &tup) {
		return tup.val;
	}
};

template<typename A, typename T, typename ...Ts>
struct Getter2<A, T, Ts...> {
	static auto &get(Tuple<T, Ts...> &tup) {
		return Getter2<A, Ts...>::get(static_cast<Tuple<Ts...>&>(tup));
	}
};

template<typename T, typename ...Ts>
auto &
get(Tuple<Ts...> &tup) {
	return Getter2<T, Ts...>::get(tup);
}

int main(){
    Tuple<int, double> tid(4, 5.6);
	
    cout << "get<1>(tid) = " << get<1>(tid) << endl; // by index
	cout << "get<0>(tid) = " << get<0>(tid) << endl; // by index

    cout << "get<int>(tid) = " << get<int>(tid) << endl; // by type
	cout << "get<double>(tid) = " << get<double>(tid)<< endl; // by type
}