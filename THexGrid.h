#pragma once

#include "THex.h"
#include <vector>

template <typename T>
class THexGrid {
private:
	std::vector<THex<T>> hexes;
	THexCube<std::ptrdiff_t> minimum;
	THexCube<std::ptrdiff_t> maximum;

public:
	THexGrid( std::ptrdiff_t r ) : THexGrid( THexCube<std::ptrdiff_t>( -r, -r, -r ), THexCube<std::ptrdiff_t>( r, r, r ) ) {}

	THexGrid( THexCube<std::ptrdiff_t> min, THexCube<std::ptrdiff_t> max ) : minimum( min ), maximum( max ) {
		for ( std::ptrdiff_t x = minimum.x; x <= maximum.x; ++x ) {
			auto yfirst = std::min( minimum.y, -x - maximum.z );
			auto ylast = std::min( maximum.y, -x - minimum.z );
			for ( std::ptrdiff_t y = yfirst; y <= ylast; ++y ) {
				T z = -x - y;
				hexes.push_back( THex<T>( THexCube<T>( x, y, z ) ) );
			}
		}
	}

	/*void Render( Furrovine::TVector2<float> offset, Furrovine::TVector2<float> mouse, Furrovine::Graphics::NymphBatch& batch ) {
		HexAxialPoint hexmouse = new HexAxialPoint( mouse - offset, 20 );
		foreach( Hex hex in hexes ) {
			Vector2 pixel = hex.Face.Axial.ToPixel( 20 );
			Color color = Color.White;
			if ( hex.Face.Axial == hexmouse )
				color = Color.Red;
			//batch.RenderGradient( new Vector2( 5, 5 ), color, color, pixel + offset, 0, Vector2.One, Vector2.Zero, SpriteEffects.None );
			batch.RenderPolygon( shape, null, color, pixel + offset );
		}
	}*/
};
