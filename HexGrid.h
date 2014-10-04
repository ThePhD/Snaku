#pragma once

#include "HexDirection.h"
#include "HexCoord.h"
#include "Hex.h"
#include <Furrovine++/Size2.h>
#include <Furrovine++/optional.h>
#include <Furrovine++/Graphics/NymphBatch.h>
#include <Furrovine++/Graphics/Nymphgon.h>
#include <vector>
#include <Furrovine++/operator_overloads.h>

template <typename T>
struct hex_iterator : std::iterator<std::forward_iterator_tag, THexAxial<T>> {
	std::ptrdiff_t radius, x, yfirst, ylast, y;

	hex_iterator( std::ptrdiff_t r, std::size_t steps = 0 ) : radius( r ), 
		x( -radius ), 
		yfirst( compute_yfirst( x, radius ) ),
		ylast( compute_ylast( x, radius ) ),
		y( yfirst ) {
		for ( ; steps-- > 0; ) {
			this->operator++( );
		}
	}

	static std::ptrdiff_t compute_yfirst( std::ptrdiff_t x, std::ptrdiff_t radius ) {
		return std::max( -radius, -x - radius );
	}

	static std::ptrdiff_t compute_ylast( std::ptrdiff_t x, std::ptrdiff_t radius ) {
		return std::min( radius, -x + radius );
	}

	THexAxial<T> operator* ( ) const {
		return { static_cast<T>( x ) , static_cast<T>( y ) };
	}

	hex_iterator& operator++ ( ) {
		++y;
		if ( y <= ylast ) {
			return *this;
		}
		if ( x <= radius ) {
			++x;
			yfirst = compute_yfirst( x, radius );
			ylast = compute_ylast( x, radius );
			y = yfirst;
		}
		return *this;
	}

	hex_iterator operator++ ( Furrovine::op::postfix_overload_t ) {
		auto x = *this;
		this->operator++( );
		return x;
	}

	bool operator== ( const hex_iterator<T>& right ) const {
		return radius == right.radius && x == right.x && y == right.y;
	}

	bool operator!= ( const hex_iterator<T>& right ) const {
		return radius != right.radius || x != right.x || y != right.y;
	}
};

template <typename T>
struct hex_ring_iterator : std::iterator<std::forward_iterator_tag, THexAxial<T>> {
	std::ptrdiff_t radius, i, j;
	HexAxialz axial;
	
	hex_ring_iterator( std::ptrdiff_t r, HexDirection direction = HexDirection::One ) : radius( r ), i( 0 ), j( 0 ), axial(HexAxialz(0, 0).shift( direction, r )) {
		
	}

	THexAxial<T> operator* ( ) const {
		return THexAxial<T>( static_cast<T>( axial.q ), static_cast<T>( axial.r ) );
	}

	hex_ring_iterator& operator++ ( ) {
		++j;
		if ( j < radius ) {
			axial = axial.neighbor( static_cast<HexDirection>( i ) );
			return *this;
		}
		if ( i < 6 ) {
			++i;
		}
		j = 0;
		return *this;
	}

	hex_ring_iterator operator++ ( Furrovine::op::postfix_overload_t ) {
		auto x = *this;
		this->operator++( );
		return x;
	}

	bool operator== ( const hex_ring_iterator<T>& right ) const {
		return i == right.i && j == right.j;
	}

	bool operator!= ( const hex_ring_iterator<T>& right ) const {
		return i != right.i || j != right.j;
	}
};

class HexGrid {
private:
	const static Furrovine::Vector2z Neighbors[ 6 ];
	std::ptrdiff_t radius;
	std::vector<Hex> hexes;
	Furrovine::buffer_view<Hex, 2> hexesview;
	Furrovine::Graphics::Nymphgon shape;

public:


	struct hex_grid_iterator {
		HexGrid* grid;
		hex_iterator<std::ptrdiff_t> it;

		hex_grid_iterator( HexGrid& grid, hex_iterator<std::ptrdiff_t> iterator ) : grid( std::addressof( grid ) ), it( std::move( iterator ) ) {

		}

		Hex& operator* ( ) {
			return ( *grid )[ *it ];
		}

		const Hex& operator* ( ) const {
			return ( *grid )[ *it ];
		}

		hex_grid_iterator& operator++ ( ) {
			++it;
			return *this;
		}

		hex_grid_iterator operator++ ( Furrovine::op::postfix_overload_t ) {
			auto x = *this;
			this->operator++( );
			return x;
		}

		bool operator== ( const hex_grid_iterator& right ) const {
			return grid == right.grid && it == right.it;
		}

		bool operator!= ( const hex_grid_iterator& right ) const {
			return grid != right.grid || it != right.it;
		}

	};

	struct hex_grid_ring_iterator {
		HexGrid* grid;
		hex_ring_iterator<std::ptrdiff_t> it;

		hex_grid_ring_iterator( HexGrid& grid, hex_ring_iterator<std::ptrdiff_t> iterator ) : grid( std::addressof( grid ) ), it( std::move( iterator ) ) {

		}

		Hex& operator* ( ) {
			return ( *grid )[ *it ];
		}

		const Hex& operator* ( ) const {
			return ( *grid )[ *it ];
		}

		hex_grid_ring_iterator& operator++ ( ) {
			++it;
			return *this;
		}

		hex_grid_ring_iterator operator++ ( Furrovine::op::postfix_overload_t ) {
			auto x = *this;
			this->operator++( );
			return x;
		}

		bool operator== ( const hex_grid_ring_iterator& right ) const {
			return grid == right.grid && it == right.it;
		}

		bool operator!= ( const hex_grid_ring_iterator& right ) const {
			return grid != right.grid || it != right.it;
		}

	};

	HexGrid( std::ptrdiff_t r );

	Hex& operator[] ( const HexAxialz& ax );

	const Hex& operator[] ( const HexAxialz& ax ) const;

	Hex& Neighbor( const Hex& hex, HexDirection direction );

	const Hex& Neighbor( const Hex& hex, HexDirection direction ) const;

	hex_grid_iterator begin( ) {
		return hex_grid_iterator( *this, hex_iterator<std::ptrdiff_t>( radius ) );
	}

	hex_grid_iterator end( ) {
		return hex_grid_iterator( *this, hex_iterator<std::ptrdiff_t>( radius, hex_count( radius ) ) );
	}

	template <typename TFx>
	void for_each( TFx&& fx, HexDirection start = HexDirection::Four ) const {
		HexCubez minimum{ -radius, -radius, -radius };
		HexCubez maximum{ radius, radius, radius };
		for ( std::ptrdiff_t x = minimum.x; x <= maximum.x; ++x ) {
			auto yfirst = std::max( minimum.y, -x - maximum.z );
			auto ylast = std::min( maximum.y, -x - minimum.z );
			for ( std::ptrdiff_t y = yfirst; y <= ylast; ++y ) {
				fx( ( *this )[ { x, y } ] );
			}
		}
	}

	template <typename TFx>
	void for_each( TFx&& fx, HexDirection start = HexDirection::Four ) {
		HexCubez minimum{ -radius, -radius, -radius };
		HexCubez maximum{ radius, radius, radius };
		for ( std::ptrdiff_t x = minimum.x; x <= maximum.x; ++x ) {
			auto yfirst = std::max( minimum.y, -x - maximum.z );
			auto ylast = std::min( maximum.y, -x - minimum.z );
			for ( std::ptrdiff_t y = yfirst; y <= ylast; ++y ) {
				fx( ( *this )[ { x, y } ] );
			}
		}
	}

	void Render( Furrovine::Vector2 offset, Furrovine::Vector2 mouse, Furrovine::Graphics::NymphBatch& batch );

};
