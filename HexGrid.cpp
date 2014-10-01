#include "HexGrid.h"

const Furrovine::TVector2<std::ptrdiff_t> HexGrid::Neighbors[ 6 ] = {
		{ +1, 0 }, { +1, -1 }, { 0, -1 },
		{ -1, 0 }, { -1, +1 }, { 0, +1 }
};

std::ptrdiff_t HexGrid::Count( std::ptrdiff_t r ) {
	return 1 + ( 3 * r ) + ( 3 * r *r );
}

void HexGrid::Render( Furrovine::Vector2 offset, Furrovine::Vector2 mouse, Furrovine::Graphics::NymphBatch& batch ) {
	using namespace Furrovine;
	Furrovine::Vector2 v = mouse - offset;
	//v.y = -v.y;
	HexAxial hexmouse = round( HexAxial( v, 20.0f, default_hextop_constant ) );
	std::vector<HexAxial> axials;
	for ( Hex& ohex : hexes ) {
		Hex& hex = ohex;
		Furrovine::Vector2 pixel = to_pixel( hex.axial, 20.0 );
		Furrovine::Color color = Furrovine::Color::White;
		if ( hex.axial == hexmouse )
			color = Furrovine::Color::Red;
		batch.RenderPolygon( shape, Furrovine::nullopt, pixel + offset, 0.0f, Furrovine::Vector2::One, Furrovine::Vector2::Zero, color );
		axials.push_back( hex.axial );
	}
	axials.clear( );
}

template <typename TFx>
void HexGrid::for_each( TFx&& fx, HexDirection start /*= HexDirection::Four */ ) {
	for ( std::size_t k = 1; k <= radius; ++k ) {
		std::reference_wrapper<Hex> h( ( *this )[ {0, 0} ] );
		std::size_t kminus1 = k - 1;
		for ( std::size_t s = 0; s < kminus1; ++s ) {
			h = std::ref( Neighbor( h.get( ), start ) );
		}
		for ( std::size_t i = 0; i < 6; ++i ) {
			for ( std::size_t j = 0; < k; ++j ) {
				fx( h.get( ) );
				// Rebind
				h = std::ref( Neighbor( h.get( ), static_cast<HexDirection>( i ) ) );
			}
		}
	}
}

const Hex& HexGrid::Neighbor( const Hex& hex, HexDirection direction ) const {
	return const_cast<HexGrid&>( *this ).Neighbor( hex, direction );
}

Hex& HexGrid::Neighbor( const Hex& hex, HexDirection direction ) {
	THexAxial<std::ptrdiff_t> ax = hex.axial;
	ax += Neighbors[ static_cast<std::size_t>( direction ) ];
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
hexes( Count( radius ) ),
hexesview( hexes, { radius, radius } ),
shape( Furrovine::Graphics::Nymphgon::CreateNgon( 20, 6 ) ) {
	HexCubez minimum{ -r, -r, -r };
	HexCubez maximum{ r, r, r };
	for ( std::ptrdiff_t x = minimum.x; x <= maximum.x; ++x ) {
		auto yfirst = std::max( minimum.y, -x - maximum.z );
		auto ylast = std::min( maximum.y, -x - minimum.z );
		for ( std::ptrdiff_t y = yfirst; y <= ylast; ++y ) {
			( *this )[ { x, y } ] = Hex( HexAxial( static_cast<float>( x ), static_cast<float>( y ) ) );
		}
	}
}

