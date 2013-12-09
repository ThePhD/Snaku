#define FURROVINEDEBUG
#define FURROVINEDLL

#include <Furrovine++/FurrovineGame.h>
#include <Furrovine++/WindowDriver.h>
#include <Furrovine++/ServiceTracker.h>
#include <Furrovine++/IWindowService.h>
#include <Furrovine++/Text/RasterFont.h>
#include <Furrovine++/Graphics/Window.h>
#include <Furrovine++/Graphics/GraphicsDevice.h>
#include <Furrovine++/Pipeline/RasterFontDataLoader.h>
#include <Furrovine++/Pipeline/RasterFontLoader.h>
#include <Furrovine++/Pipeline/TextureLoader.h>
#include <Furrovine++/Pipeline/ImageLoader.h>
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
	
public:
	Snaku( ) : FurrovineGame( ),
		windowdriver( ),
		window( windowdriver, WindowDescription( "~ Snaku ~", WindowStyles::BorderlessTransparent ) ),
		windowservice( Services, window ), graphicsservice( Services, graphics ) {
		window.Show( );
	}

	void Initialize( ) {
	
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
		graphics.Clear( Color( 20, 20, 50, 50 ) );

	}

};

int main( ) {
	Snaku snaku{ };
	snaku.Run( );
}