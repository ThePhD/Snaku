#include "types.h"
#include "StateStack.h"
#include "GameState.h"
#include "PauseState.h"
#include "Everything.h"

#include <Furrovine++/FurrovineGame.h>
#include <Furrovine++/ResourceCache.h>
#include <Furrovine++/Text/RasterFont.h>
#include <Furrovine++/Graphics/Window.h>
#include <Furrovine++/Graphics/BlendState.h>
#include <Furrovine++/Graphics/NymphBatch.h>
#include <Furrovine++/Text/TextDevice.h>
#include <Furrovine++/Pipeline/ImageLoader.h>
#include <Furrovine++/Pipeline/TextureLoader.h>
#include <Furrovine++/Pipeline/RasterFontLoader.h>
#include <Furrovine++/Pipeline/PNGSaver.h>

using namespace Furrovine;
using namespace Furrovine::Input;
using namespace Furrovine::IO;
using namespace Furrovine::Graphics;
using namespace Furrovine::Text;
using namespace Furrovine::Pipeline;

class Snaku : public FurrovineGame {
private:
	WindowDriver windowdriver;
	Window window;
	GraphicsDevice graphics;
	GraphicsDevice2D graphics2d;
	TextDevice textdevice;
	NymphBatch batch;
	ResourceCache<String> cache;
	StateStack states;
	Everything everything;
	GameState gamestate;
	PauseState pausestate;
	MessageQueue messages;

public:

	Snaku( ) : FurrovineGame( ),
	windowdriver( ),
	window( windowdriver, WindowDescription( "~ Snaku ~" ) ),
	graphics( window ),
	textdevice( window ),
	graphics2d( graphics ),
	batch( graphics ),
	cache(),
	everything( { windowdriver, window, graphics, textdevice, batch, cache, states } ),
	gamestate( everything ),
	pausestate( everything ) {
		WindowService = window;
		GraphicsService = graphics;
		Graphics2DService = graphics2d;
		states.push( gamestate );
		cache.add( "test", ImageLoader( )( load_single, "test.wbmp" ) );
		cache.add( "test.texture", TextureLoader( graphics )( cache.get<Image2D>( "test" ) ) );
		cache.add( "Font", RasterFontLoader( graphics, textdevice )( RasterFontDescription( "Arial", 24.0f ) ) );
		window.Show( );
	}

protected:

	void Loop( ) {
		optional<MessageData> opmessagedata;
		windowdriver.Push( window, messages );
		while ( ( opmessagedata = messages.pop( ) ) ) {
			MessageData& messagedata = opmessagedata.value();
			switch ( messagedata.header.id ) {
			case MessageId::Mouse:
				
				break;
			case MessageId::Keyboard: { 
				Message<KeyboardEvent>& message = messagedata.as<KeyboardEvent>( );
				if ( message.item.Key == Key::Enter ) {
					if ( !states.contains( pausestate ) ) {
						states.push( pausestate );
					}
					else {
						states.pop( );
					}
				}
				} break;
			case MessageId::None:
			default:
				break;
			}
		}
		FurrovineGame::Loop( );
	}

	void Update( ) {
		states.Update( );
	}

	void Render( ) {
		graphics.Clear( Color( 96, 96, 128, 128 ) );
		states.Render( );
	}

};

int main( ) {
	Snaku snaku{ };
	snaku.Run( );
}
