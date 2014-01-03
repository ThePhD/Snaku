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
	std::unique_ptr<NymphBatch> batch;
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
		graphics.SetBlend( 0, BlendState( BlendState::AlphaBlend ) );
		batch = std::make_unique<NymphBatch>( graphics );
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
//#pragma comment( lib, "dwmapi.lib")
		//auto hwnd = FindWindowW( NULL, L"C:\\windows\\System32\\cmd.exe" );
		//MARGINS m = { -1, -1, -1, -1 };
		//auto r = DwmExtendFrameIntoClientArea( hwnd, &m );
		graphics.Clear( Color( 20, 20, 50, 50 ) );
		//qbatch->Begin( );
		//qbatch->RenderString( *font, "Hell yeah!", { } );
		//qbatch->End( );
		batch->Begin( );
		batch->RenderString( *font, "Hell yeah!", { } );
		batch->End( );
	}

};

int main( ) {
	Snaku snaku{ };
	snaku.Run( );
}