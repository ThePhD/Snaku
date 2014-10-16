#include "StateStack.h"
#include "GameState.h"
#include "PauseState.h"
#include "HexGrid.h"

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
#include <Furrovine++/queue.h>

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
	NymphBatch nymph;
	ResourceCache<String> cache;
	StateStack states;
	Everything everything;
	GameState gamestate;
	PauseState pausestate;
	Furrovine::queue<Message> messages;
	HexGrid grid;
	Vector2 mouse;
	String typed;

public:

	Snaku( ) : FurrovineGame( ),
	windowdriver( ),
	window( windowdriver, WindowDescription( "~ Snaku ~" ) ),
	graphics( window ),
	textdevice( window ),
	graphics2d( graphics ),
	nymph( graphics ),
	cache(),
	everything( { windowdriver, window, graphics, textdevice, nymph, cache, states } ),
	gamestate( everything ),
	pausestate( everything ),
	grid( 7 ) {
		WindowService = window;
		GraphicsService = graphics;
		Graphics2DService = graphics2d;
		RasterFontDescription desc = RasterFontDescription( "Arial", 24.0f );
		desc.CharacterRanges.push_back( CodepointRange( 0x2661, 0x2665 ) );
		states.push( gamestate );
		cache.add( "test", ImageLoader( )( load_single, "test.wbmp" ) );
		cache.add( "test.texture", TextureLoader( graphics )( cache.get<Image2D>( "test" ) ) );
		cache.add( "Font", RasterFontLoader( graphics, textdevice )( desc ) );
		window.SetCursorVisible( false );
		window.Show( );
	}

protected:

	void Loop( ) {
		optional<Message> opmessagedata;
		windowdriver.Push( window, messages );
		while ( ( opmessagedata = messages.pop( ) ) ) {
			Message& messagedata = opmessagedata.value();
			switch ( messagedata.class_idx ) {
			case Message::index<MouseEvent>::value: {
				MouseEvent& message = messagedata.get<MouseEvent>( );
				mouse = message.relative;
				break; }
			case Message::index<WindowEvent>::value: {
				WindowEvent& message = messagedata.get<WindowEvent>( );
				if ( message.Signal == WindowEventSignal::Destroy ) {
					Exit( );
				}
				break; }
			case Message::index<KeyboardEvent>::value: {
				KeyboardEvent& message = messagedata.get<KeyboardEvent>( );
				if ( message.key == Key::Enter ) {
					if ( !states.contains( pausestate ) ) {
						states.push( pausestate );
					}
					else {
						states.pop( );
					}
				}
				break; }
			case Message::index<TextEvent>::value: {
				TextEvent& message = messagedata.get<TextEvent>( );
				typed.Append( message.cp );
				break; }
			case -1:
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
		nymph.Begin( );
		grid.Render( { 400, 300 }, mouse, nymph );
		nymph.RenderGradient( Region( mouse - 3.0f, Size2( 6.0f, 6.0f ) ), Color::Blue );
		nymph.RenderString( cache.get<RasterFont>( "Font" ), typed, { 0, 0 } );
		nymph.RenderGradient( Region( Vector2( 50.0f, 50.0f ), Size2( 50.0f, 50.0f ) ), Color::Blue );
		nymph.End( );

		states.Render( );
	}

};

int main( ) {
	Snaku snaku{ };
	snaku.Run( );
}
