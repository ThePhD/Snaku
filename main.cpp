#define FURROVINEDEBUG
#define FURROVINEDLL

#include <Furrovine++/FurrovineGame.h>
#include <Furrovine++/WindowDriver.h>
#include <Furrovine++/ServiceTracker.h>
#include <Furrovine++/IWindowService.h>
#include <Furrovine++/Text/RasterFont.h>
#include <Furrovine++/Graphics/Window.h>
#include <Furrovine++/Graphics/BlendState.h>
#include <Furrovine++/Graphics/GraphicsDevice.h>
#include <Furrovine++/Graphics/GraphicsDevice2D.h>
#include <Furrovine++/Graphics/QuadBatch.h>
#include <Furrovine++/Graphics/NymphBatch.h>
#include <Furrovine++/Pipeline/RasterFontDataLoader.h>
#include <Furrovine++/Pipeline/RasterFontLoader.h>
#include <Furrovine++/Pipeline/TextureLoader.h>
#include <Furrovine++/Pipeline/ImageLoader.h>
#include <Furrovine++/Pipeline/WBMPLoader.h>
#include <Furrovine++/Pipeline/JPGSaver.h>
#include <Furrovine++/Pipeline/PNGSaver.h>
#include <Furrovine++/IO/FileStream.h>
#include <Furrovine++/Format.h>
#include <Furrovine++/Text/TextResources.h>

#include <iostream>

using namespace Furrovine;
using namespace Furrovine::IO;
using namespace Furrovine::Graphics;
using namespace Furrovine::Pipeline;
using namespace Furrovine::Text;

class Snaku : public FurrovineGame {
private:
	WindowDriver windowdriver;
	Window window;
	GraphicsDevice graphics;
	GraphicsDevice2D graphics2d;
	TextResources textresources;
	Image2D image;
	std::unique_ptr<QuadBatch> qbatch;
	std::unique_ptr<Texture2D> texture;
	std::unique_ptr<RasterFont> rasterfont;
	std::unique_ptr<Font> font;
	MessageQueue messages;

public:

	Snaku( ) : FurrovineGame( ),
		windowdriver( ),
		window( windowdriver, WindowDescription( "~ Snaku ~", WindowStyles::BorderlessTransparent ) ) {
		WindowService = window;
		GraphicsService = graphics;
		Graphics2DService = graphics2d;
	}

protected:

	void Initialize( ) {
		graphics.SetBlend( BlendState( BlendState::AlphaBlend ) );
		ImageLoader imageloader;
		image = std::move( imageloader( "test.wbmp" )[ 0 ] );
		make_unique( texture, graphics, image );
		make_unique( rasterfont, RasterFontLoader( graphics )( RasterFontDescription( "Consolas", 30.0f ) ) );
		make_unique( font, textresources, FontDescription{ "Arial", 24.0f } );
		make_unique( qbatch, graphics );

		graphics.Clear( Colors::Black );
		window.Show( );
	}

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

	}

	void Render( ) {
		graphics2d.End( );
		graphics.Clear( Color( 96, 96, 128, 128 ) );
		graphics2d.Begin( );
		graphics2d.Clear( Colors::Transparent );
		graphics2d.End( );
		graphics2d.Begin( );
		graphics2d.RenderText( *font, L"Woofℒ!" );
		qbatch->Begin( );
		qbatch->RenderString( *rasterfont, "Hell yeah!", { 0, 100 } );
		qbatch->End( );
	}

};

int main( ) {
	Snaku snaku{ };
	snaku.Run( );
}
