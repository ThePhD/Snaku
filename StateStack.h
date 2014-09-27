#pragma once

#include "State.h"
#include <vector>

class StateStack {
private:
	std::vector<std::reference_wrapper<State>> states;

public:

	StateStack( );

	void push( State& state );

	State& top( );

	void pop( );

	bool is_empty( ) const;

	bool contains( const State& state ) const;

	void Update( );

	void Render( );

};