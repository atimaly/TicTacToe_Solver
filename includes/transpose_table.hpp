#include <bits/stdc++.h>

using namespace std;

#ifndef TRANP_TABLE
#define TRANP_TABLE

template<typename MoveT>
struct TrTEntry{

	uint64_t hash_key;
	uint16_t value_pos;
	MoveT opt_move;

};

template<typename T, size_t S>
class TranspositionTable{
	std::array<T, S> table_;
};

#endif
