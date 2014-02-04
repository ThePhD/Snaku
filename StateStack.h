#pragma once

#include "State.h"
#include <vector>

class StateStack {
private:
	std::vector<State*> states;

public:

	StateStack( );

	void Push( State* state );

	void Pop( );

	void Update( );

	void Render( );

};