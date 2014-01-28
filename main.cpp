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
#include <Furrovine++/Graphics/VertexImageQuad.h>
#include <Furrovine++/Pipeline/HLSLEffectLoader.h>

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
	//GraphicsDevice2D graphics2d;
	TextResources textresources;
	Image2D image;
	std::unique_ptr<QuadBatch> qbatch;
	std::unique_ptr<Texture2D> texture;
	std::unique_ptr<RasterFont> rasterfont;
	std::unique_ptr<Font> font;
	std::unique_ptr<ShaderEffect> effect;
	MessageQueue messages;

public:

	Snaku( ) : FurrovineGame( ),
	windowdriver( ),
	window( windowdriver, WindowDescription( "~ Snaku ~" ) ),
	graphics( window )/*, graphics2d( graphics )*/ {
		WindowService = window;
		GraphicsService = graphics;
		//Graphics2DService = graphics2d;

		graphics.SetBlend( BlendState( BlendState::AlphaBlend ) );
		ImageLoader imageloader;
		image = std::move( imageloader( "test.wbmp" )[ 0 ] );
		unique_reset( texture, graphics, image );
		unique_reset( rasterfont, RasterFontLoader( graphics )( RasterFontDescription( "Consolas", 30.0f ) ) );
		unique_reset( font, textresources, FontDescription{ "Arial", 24.0f } );
		unique_reset( qbatch, graphics );
		unique_reset( effect, HLSLEffectLoader( graphics )( "BasicShader.hlsl" ) );
		graphics.Clear( Colors::Black );
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

	}

	void tryit( ) {
		Viewport viewport = graphics.GetViewport( );
		Matrix projection = Matrix::CreateOrthographicProjectionOffCenter(
			viewport.x, viewport.x + viewport.width,
			viewport.y + viewport.height, viewport.y,
			-1.0f, 1.0f );

		uint16 indices[ 6 ] = {
			0, 1, 2,
			1, 3, 2
		};
		float right = 500;
		float bottom = 500;
		float texW = static_cast<float>( texture->Width( ) );
		float texH = static_cast<float>( texture->Height( ) );
		float lefttexel = 0 / texW;
		float righttexel = ( 0 + 500 ) / texW;
		float toptexel = 0 / texH;
		float bottomtexel = ( 0 + 500 ) / texH;
		Region bounds( 0, 0, 500, 500 );
		Matrix world = Matrix::Identity;
		world.m11 = bounds.width / texW;
		world.m22 = bounds.height / texH;

		world.m41 = bounds.x;
		world.m42 = bounds.y;

		VertexImageQuad quad[ 4 ] = {
			{ },
			{ },
			{ },
			{ },
		};
		VertexImageQuad quadvertex[ 6 ] = {
			{ },
			{ },
			{ },
			{ },
		};

		Color tint = Colors::White;

		quad[ 0 ].color = tint;
		quad[ 0 ].position.x = ( world.m11 * 0 ) + ( world.m21 * 0 ) + ( world.m31 * 0 ) + ( world.m41 );
		quad[ 0 ].position.y = ( world.m12 * 0 ) + ( world.m22 * 0 ) + ( world.m32 * 0 ) + ( world.m42 );
		quad[ 0 ].position.zw = Vector2::Zero;

		quad[ 1 ].color = tint;
		quad[ 1 ].position.x = ( world.m11 * right ) + ( world.m21 * 0 ) + ( world.m31 * 0 ) + ( world.m41 );
		quad[ 1 ].position.y = ( world.m12 * right ) + ( world.m22 * 0 ) + ( world.m32 * 0 ) + ( world.m42 );
		quad[ 1 ].position.zw = Vector2::Zero;

		quad[ 2 ].color = tint;
		quad[ 2 ].position.x = ( world.m11 * 0 ) + ( world.m21 * bottom ) + ( world.m31 * 0 ) + ( world.m41 );
		quad[ 2 ].position.y = ( world.m12 * 0 ) + ( world.m22 * bottom ) + ( world.m32 * 0 ) + ( world.m42 );
		quad[ 2 ].position.zw = Vector2::Zero;

		quad[ 3 ].color = tint;
		quad[ 3 ].position.x = ( world.m11 * right ) + ( world.m21 * bottom ) + ( world.m31 * 0 ) + ( world.m41 );
		quad[ 3 ].position.y = ( world.m12 * right ) + ( world.m22 * bottom ) + ( world.m32 * 0 ) + ( world.m42 );
		quad[ 3 ].position.zw = Vector2::Zero;
		( *effect )[ 0 ][ 0 ].Parameters( )[ "ViewProjection" ].SetValue( projection );
		( *effect )[ 0 ][ 0 ].Apply( );
		//RenderUserIndexedPrimitives( PrimitiveTopology::TriangleList, quad, 0, 4, indices, 0, 2 );
		for ( ulword i = 0; i < 6; ++i ) {
			quadvertex[ i ] = quad[ indices[ i ] ];
		}
		graphics.RenderUserPrimitives( PrimitiveTopology::TriangleList, quadvertex, 0, 2 );
	}

	void Render( ) {
		graphics.Clear( Color( 96, 96, 128, 128 ) );
		//graphics2d.RenderText( *font, L" ♡ Woof ♡" );
		//qbatch->Begin( );
		//qbatch->RenderString( *rasterfont, "Hell yeah!", { 0, 100 } );
		//qbatch->Render( *texture, Colors::White, Region( 0, 200, 200, 200 ) );
		//qbatch->Render( *texture, Colors::White, Region( 200, 200, 200, 200 ) );
		//qbatch->End( );
		tryit( );
		//graphics.RenderImage( *texture );
	}

};

int main( ) {
	Snaku snaku{ };
	snaku.Run( );
}
