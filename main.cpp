#include "StateStack.h"
#include "GameState.h"
#include "PauseState.h"
#include "HexGrid.h"

#include <Furrovine++/queue.h>
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
#include <Furrovine++/Input/KeyboardDevice.h>
#include <Furrovine++/Input/MouseDevice.h>
#include <Furrovine++/Input/HIDDevice.h>
#include <Furrovine++/Input/InputEvents.h>
#include <iostream>

using namespace Furrovine;
using namespace Furrovine::Input;
using namespace Furrovine::IO;
using namespace Furrovine::Graphics;
using namespace Furrovine::Text;
using namespace Furrovine::Pipeline;

enum class Control {
	MoveUp,
	MoveDown,
	MoveRight,
	MoveLeft,
};

enum class MoveFlags {
	None = 0x0,
	Up = 0x01,
	Down = 0x02,
	Right = 0x04,
	Left = 0x08
};

template <typename Cont>
MoveFlags FromControls( Cont&& cont ) {
	using namespace Furrovine::enums::operators;
	MoveFlags flags = MoveFlags::None;
	for ( const Control& control : cont ) {
		switch ( control ) {
		case Control::MoveLeft:
			flags |= MoveFlags::Left;
			break;
		case Control::MoveDown:
			flags |= MoveFlags::Down;
			break;
		case Control::MoveUp:
			flags |= MoveFlags::Up;
			break;
		case Control::MoveRight:
			flags |= MoveFlags::Right;
			break;
		}
	}
	return flags;
}

template <>
struct Furrovine::enums::is_flags<MoveFlags> : std::true_type{};

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
	InputEvents<Control> inputevents;
	HexGrid grid;
	MouseDevice mousedevice;
	KeyboardDevice keyboarddevice;
	HIDDevice hiddevice;
	std::vector<Control> controls;

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
		SetupControls( );
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

	void SetupControls( ) {
		inputevents.Intent += [ & ] ( Control c ) {
			controls.push_back( c );
		};

		ButtonInput input{ 
			StateInputType::KeyboardKey,
			0,
			static_cast<int32>( Key::A ),
			false };
		inputevents.Map( input, Control::MoveLeft );

		input.Id = static_cast<intuz>( Key::D );
		inputevents.Map( input, Control::MoveRight );
		
		input.Id = static_cast<intuz>( Key::W );
		inputevents.Map( input, Control::MoveUp );
		
		input.Id = static_cast<intuz>( Key::S );
		inputevents.Map( input, Control::MoveDown );
	}

	void Loop( ) {
		optional<Message> opmessagedata;
		windowdriver.Push( window, messages );
		while ( ( opmessagedata = messages.pop_front( ) ) ) {
			Message& messagedata = opmessagedata.value();
			inputevents.Process( messagedata );
			switch ( messagedata.class_idx ) {
			case Message::index<MouseEvent>::value: {
				MouseEvent& message = messagedata.get<MouseEvent>( );
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
				break; }
			case -1:
			default:
				break;
			}
		}
		FurrovineGame::Loop( );
	}

	void Update( ) {
		MoveFlags movement = FromControls( controls );
		mousedevice.Update( );
		keyboarddevice.Update( );
		hiddevice.Update( );
		
		if ( movement != MoveFlags::None ) {
			static int woof = 0;
			std::cout << "Movement! " << woof++ << std::endl;
		}

		// Feedback works on X360 right now, nothin'
		// else however until HID Report Packing
		// is implemented...
		if ( keyboarddevice.Down( Key::LeftShift ) ) {
			hiddevice.Feedback( 0, 1.0 );
		}
		else {
			hiddevice.Feedback( 0, 0.0 );
		}

		if ( keyboarddevice.Down( Key::RightShift ) ) {
			hiddevice.Feedback( 1, 1.0 );
		}
		else {
			hiddevice.Feedback( 1, 0.0 );
		}
		
		states.Update( );

		controls.clear( );
	}

	void Render( ) {
		graphics.Clear( Color( 96, 96, 128, 128 ) );
		nymph.Begin( );
		grid.Render( { 400, 300 }, mousedevice.Position(), nymph );
		nymph.RenderGradient( Region( mousedevice.Position() - 3.0f, Size2( 6.0f, 6.0f ) ), Color::Blue );
		
		nymph.End( );

		states.Render( );
	}

};

int main( ) {
	Snaku snaku{ };
	snaku.Run( );
}
