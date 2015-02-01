#include "PauseState.hpp"
#include <Furrovine++/Pipeline/TextureFontLoader.hpp>
#include <Furrovine++/Graphics/TextureFont.hpp>

using namespace Furrovine;
using namespace Furrovine::Graphics;
using namespace Furrovine::Text;

void PauseState::Render( ) {
	// This is actually easier to reason about, and I can expand the Everything struct
	// when I need to.... nice!
	Everything& everything = everythingref;
	ResourceCache<string>& cache = everything.cache;
	TextureFont& font = cache.get<TextureFont>( "Font" );
	GraphicsDevice& graphics = everything.graphics;
	NymphBatch& nymph = everything.nymphbatch;

	Viewport viewport = graphics.GetViewport( );
	Vector2 origin = font.MeasureString( "P a u s e" );
	nymph.Begin( );
	nymph.RenderGradient( viewport, Color( 0, 0, 0, 128 ) );
	nymph.RenderString( font, "P a u s e", viewport.Center(), 0.0f, Vector2::One, origin / 2.0f );
	nymph.End( );
}

PauseState::PauseState( Everything& everything ) 
: everythingref( everything ) {
	// Prevents the state below it from updating,
	// but still renders the state below it
	StopsUpdate = true;
	StopsRender = false;
}
