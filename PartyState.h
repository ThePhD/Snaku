#pragma once

#include "types.h"
#include "State.h"
#include <Furrovine++/Graphics/NymphBatch.h>
#include <Furrovine++/Graphics/GraphicsDevice2D.h>

class PartyState : public State {
private:
	Fur::Graphics::GraphicsDevice* graphics;
	Fur::Graphics::GraphicsDevice2D* graphics2d;
	Fur::Text::TextResources* textresources;
	Furrovine::Graphics::NymphBatch* nymphbatch;
	
public:

	PartyState( Fur::Graphics::GraphicsDevice& graphics, 
		Fur::Graphics::GraphicsDevice2D& graphics2d,
		Fur::Text::TextResources& textresources,
		Fur::Graphics::NymphBatch& nymphbatch ) 
	: graphics( &graphics ), graphics2d( &graphics2d ), textresources( &textresources ), nymphbatch( &nymphbatch ) {

	}

	virtual void Update( ) override {

	}

	virtual void Render( ) override {

	}

};
