#include "GameState.h"
#include <Furrovine++/Graphics/Texture2D.h>

using namespace Furrovine;
using namespace Furrovine::Graphics;

void GameState::Render( ) {
	Everything& everything = everythingref;
	ResourceCache<String>& cache = everything.cache;
	GraphicsDevice& graphics = everything.graphics;
	NymphBatch& nymph = everything.nymphbatch;

	nymph.Begin( );
	nymph.Render( cache.get<Texture2D>( "test.texture" ), nullopt );
	nymph.End( );
}

void GameState::Update( ) {

}

GameState::GameState( Everything& everything ) : everythingref( everything ) {

}
