#include "PauseState.h"
#include <Furrovine++/Pipeline/RasterFontLoader.h>

void PauseState::Render( ) {
	Fur::Viewport viewport = graphics->GetViewport( );
	nymphbatch->Begin( );
	nymphbatch->RenderString( font, "P a u s e", viewport.center() );
	nymphbatch->End( );
}

PauseState::PauseState( Fur::Graphics::GraphicsDevice& graphics, Fur::Graphics::NymphBatch& nymphbatch ) 
: font( Fur::Pipeline::RasterFontLoader( graphics )( Fur::Text::RasterFontDescription( "Arial", 24.0f ) ) ), 
nymphbatch( &nymphbatch ), graphics( &graphics ) {
	StopsUpdate = true;
}
