#include "HexGrid.hpp"

const Furrovine::Vector2z HexGrid::Neighbors[ 6 ] = {
	{ +1, 0 }, { +1, -1 }, { 0, -1 },
	{ -1, 0 }, { -1, +1 }, { 0, +1 }
};

void HexGrid::Render( Furrovine::Vector2 offset, Furrovine::Vector2 mouse, Furrovine::Graphics::NymphBatch& batch ) {
	using namespace Furrovine;
	Furrovine::Vector2 v = mouse - offset;
	HexAxial hexmouse = round( HexAxial( v, 20.0f, default_hextop_constant ) );
	std::vector<HexAxial> ringhex;
	float mousedist = hex_distance( hexmouse, HexAxial{} );
	for ( const auto& hex : *this ) {
		Furrovine::Vector2 pixel = to_pixel( hex.axial, 20.0 );
		Furrovine::Color color = Furrovine::Color::Black;
		if ( hex.axial == hexmouse ) {
			color.r = 255;
		}
		batch.RenderPolygon( shape, Furrovine::nullopt, pixel + offset, 0.0f, Furrovine::Vector2::One, Furrovine::Vector2::Zero, color );
	}
	
	if ( mousedist > radius )
		return;
	
	for ( const auto& hex : ring( static_cast<std::ptrdiff_t>( mousedist ) ) ) {
		Furrovine::Vector2 pixel = to_pixel( hex.axial, 20.0 );
		Furrovine::Color color = Furrovine::Color::Green;
		if ( hex.axial == hexmouse ) {
			color.r = 255;
		}
		batch.RenderPolygon( shape, Furrovine::nullopt, pixel + offset, 0.0f, Furrovine::Vector2::One, Furrovine::Vector2::Zero, color );
	}
}

const Hex& HexGrid::Neighbor( const Hex& hex, HexDirection direction ) const {
	return const_cast<HexGrid&>( *this ).Neighbor( hex, direction );
}

Hex& HexGrid::Neighbor( const Hex& hex, HexDirection direction ) {
	HexAxialz ax = hex.axial;
	ax = ax.neighbor( direction );
	return ( *this )[ ax ];
}

const Hex& HexGrid::operator[]( const THexAxial<std::ptrdiff_t>& ax ) const {
	return const_cast<HexGrid&>( *this )[ ax ];
}

Hex& HexGrid::operator[]( const THexAxial<std::ptrdiff_t>& ax ) {
	std::ptrdiff_t y = ax.y + radius;
	std::ptrdiff_t x = ax.x + radius + std::min( 0, ax.y );
	return hexesview[ y ][ x ];
}

HexGrid::HexGrid( std::ptrdiff_t r ) : radius( r ),
hexes( hex_storage_size( radius ) ),
hexesview( hexes, hex_storage_bounds( radius ) ),
shape( Furrovine::Graphics::Nymphgon::CreateNgon( 20, 6 ) ) {
	HexCubez minimum{ -radius, -radius, -radius };
	HexCubez maximum{ radius, radius, radius };
	for ( std::ptrdiff_t x = minimum.x; x <= maximum.x; ++x ) {
		auto yfirst = std::max( minimum.y, -x - maximum.z );
		auto ylast = std::min( maximum.y, -x - minimum.z );
		for ( std::ptrdiff_t y = yfirst; y <= ylast; ++y ) {
			( *this )[ { x, y } ] = Hex( HexAxial( static_cast<float>( x ), static_cast<float>( y ) ) );
		}
	}
}

