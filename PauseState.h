#pragma once

#include "State.h"
#include "Everything.h"

class PauseState : public State {
private:
	std::reference_wrapper<Everything> everythingref;

public:

	PauseState( Everything& everything );

	virtual void Render( ) override;

};