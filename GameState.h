#pragma once

#include "Everything.h"

class GameState : public State {
private:
	std::reference_wrapper<Everything> everythingref;
	
public:

	GameState( Everything& everything );

	virtual void Update( ) override;

	virtual void Render( ) override;

};
