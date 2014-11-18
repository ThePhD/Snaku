#pragma once

#include "State.hpp"
#include "Everything.hpp"

class PauseState : public State {
private:
	std::reference_wrapper<Everything> everythingref;

public:

	PauseState( Everything& everything );

	virtual void Render( ) override;

};