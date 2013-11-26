#define FURROVINEDEBUG
#define FURROVINEDLL

#include <Furrovine++/FurrovineGame.h>
#include <Furrovine++/WindowDriver.h>
#include <Furrovine++/ServiceTracker.h>
#include <Furrovine++/IWindowService.h>
#include <Furrovine++/Graphics/Window.h>
#include <Furrovine++/Graphics/GraphicsDevice.h>

using namespace Furrovine;
using namespace Furrovine::Graphics;

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
	window( windowdriver, WindowDescription{ ">=== Snaku ===<", WindowStyle::Bordered | WindowStyle::Transparent } ),
	windowservice( Services, window ), graphicsservice( Services, graphics ) {
		window.Show( );
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