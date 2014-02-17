#include "types.h"
#include "StateStack.h"
#include "PartyState.h"
#include "PauseState.h"

#include <Furrovine++/FurrovineGame.h>
#include <Furrovine++/Text/RasterFont.h>
#include <Furrovine++/Graphics/Window.h>
#include <Furrovine++/Graphics/BlendState.h>
#include <Furrovine++/Graphics/NymphBatch.h>
#include <Furrovine++/Text/TextResources.h>
#include <Furrovine++/Pipeline/ImageLoader.h>
#include <Furrovine++/Pipeline/TextureLoader.h>

using namespace Furrovine;
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
	TextResources textresources;
	NymphBatch batch;
	MessageQueue messages;
	StateStack states;
	PartyState partystate;
	PauseState pausestate;
	Texture2D texture;
	Image2D image;

public:

	Snaku( ) : FurrovineGame( ),
	windowdriver( ),
	window( windowdriver, WindowDescription( "~ Snaku ~" ) ),
	graphics( window ),
	graphics2d( graphics ),
	batch( graphics ),
	partystate( graphics, graphics2d, textresources, batch ),
	pausestate( graphics, batch ) {
		WindowService = window;
		GraphicsService = graphics;
		Graphics2DService = graphics2d;
		states.Push( &partystate );
		graphics.SetBlend( BlendState( BlendState::AlphaBlend ) );
		image = ImageLoader( )( load_single, "test.wbmp" );
		texture = TextureLoader( graphics )( image );
		window.Show( );
	}

protected:

	void Loop( ) {
		optional<MessageData> opmessage;
		windowdriver.Push( window, messages );
		while ( ( opmessage = messages.pop( ) ) ) {
			MessageData& message = opmessage.value();
			switch ( message.header.id ) {
			case MessageId::Mouse:
				
				break;
			case MessageId::Keyboard:
				break;
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
		graphics.RenderImage( image );
		states.Render( );
	}

};

int main( ) {
	Snaku snaku{ };
	snaku.Run( );
}
