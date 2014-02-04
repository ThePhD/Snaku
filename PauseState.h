#pragma once

#include "types.h"
#include "State.h"
#include <Furrovine++/Graphics/NymphBatch.h>

class PauseState : public State {
private:
	Fur::Graphics::GraphicsDevice* graphics;
	Fur::Graphics::NymphBatch* nymphbatch;
	Fur::Text::RasterFont font;

public:

	PauseState( Fur::Graphics::GraphicsDevice& graphics, 
		Fur::Graphics::NymphBatch& nymphbatch );

	virtual void Render( ) override;

};