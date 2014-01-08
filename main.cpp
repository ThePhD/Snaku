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
	IWindowServiceTracker windowservice;
	IGraphicsDeviceServiceTracker graphicsservice;
	Image2D image;
	std::unique_ptr<QuadBatch> qbatch;
	std::unique_ptr<Texture2D> texture;
	std::unique_ptr<RasterFont> font;

public:
	Snaku( ) : FurrovineGame( ),
		windowdriver( ),
		window( windowdriver, WindowDescription( "~ Snaku ~", WindowStyles::BorderlessTransparent ) ),
		windowservice( Services, window ), graphicsservice( Services, graphics ) {
		window.Show( );
	}

	void Initialize( ) {
		graphics.SetBlend( BlendState( BlendState::AlphaBlend ) );
		qbatch = std::make_unique<QuadBatch>( graphics );
		ImageLoader imageloader;
		image = std::move( imageloader( "test.wbmp" )[ 0 ] );
		TextureLoader t( graphics );
		texture = std::make_unique<Texture2D>( graphics, image );
		font = std::make_unique<RasterFont>( RasterFontLoader( graphics )( RasterFontDescription( "Papyrus", 24.0f ) ) );
	}

	void Loop( ) {
		WindowMessage message;
		while ( windowdriver.NextMessage( window, message ) ) {

		}
		FurrovineGame::Loop( );
	}

	void Update( ) {

	}

	void Render( ) {
		graphics.Clear( Color( 96, 96, 128, 128 ) );
		qbatch->Begin( );
		qbatch->RenderString( *font, "Hell yeah!", { } );
		qbatch->End( );
	}

};

int main( ) {
	Snaku snaku{ };
	snaku.Run( );
}
