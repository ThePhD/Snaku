#define FURROVINEDEBUG
#define FURROVINEDLL

#include <Furrovine++/FurrovineGame.h>
#include <Furrovine++/WindowDriver.h>
#include <Furrovine++/ServiceTracker.h>
#include <Furrovine++/IWindowService.h>
#include <Furrovine++/Text/RasterFont.h>
#include <Furrovine++/Graphics/Window.h>
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
	ptr<NymphBatch> batch;
	ptr<QuadBatch> qbatch;
	ptr<Texture2D> texture;
	
public:
	Snaku( ) : FurrovineGame( ),
		windowdriver( ),
		window( windowdriver, WindowDescription( "~ Snaku ~", WindowStyles::BorderlessTransparent ) ),
		windowservice( Services, window ), graphicsservice( Services, graphics ) {
		window.Show( );
	}

	void Initialize( ) {
		batch = new NymphBatch( graphics );
		qbatch = new QuadBatch( graphics );
		ImageLoader imageloader;
		image = std::move( imageloader( "test.wbmp" )[ 0 ] );
		TextureLoader t( graphics );
		texture = std::make_unique<Texture2D>( graphics, image );
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
		FindWindowW( NULL, L"cmd.exe" );
		graphics.Clear( Color( 20, 20, 50, 50 ) );
		qbatch->Begin( );
		qbatch->Render( *texture, Colors::White, Region( 0.0f, 128, 128, 128 ) );
		qbatch->End( );
		batch->Begin( );
		batch->Render( *texture, Colors::White, Region( 0.0f, 0.0f, 128, 128 ) );
		batch->End( );
	}

};

int main( ) {
	Snaku snaku{ };
	snaku.Run( );
}