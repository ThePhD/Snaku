#pragma once

#include "HexTop.h"
#include <Furrovine++/TVector2.h>

template <typename T>
struct THexAxial : public Furrovine::TVector2 < T > {
	typedef Furrovine::TVector2<T> base_t;

	THexAxial( T q, T r ) : Furrovine::TVector2<T>( q, r ) {}

	template <typename Arith, HexTop top>
	THexAxial( Furrovine::TVector2<T> pixel, Arith size, std::integral_constant<HexTop, top> = default_hextop_constant ) {
		double q, r;
		switch ( top ) {
		case HexTop::Pointy:
			q = ( 1.0 / 3.0 * Furrovine::three_root_two<T>( ) * pixel.x - 1.0 / 3.0 * pixel.Y ) / size;
			r = 2.0 / 3.0 * pixel.y / size;
			break;
		case HexTop::Flat:
		default:
			q = 2.0 / 3.0 * pixel.x / size;
			r = ( 1.0 / 3.0 * Furrovine::three_root_two<T>( ) * pixel.y - 1.0 / 3.0 * pixel.X ) / size;
			break;
		}
		x = static_cast<T>( q );
		y = static_cast<T>( r );
	}

	T s( ) const {
		return -x - y;
	}

	template <HexTop top = default_hextop>
	Furrovine::TVector2<T> pixel( double size ) {
		double px, py;
		switch ( top ) {
		case HexTop::Pointy:
			px = size * Furrovine::three_root_two<T>( ) * ( x + y / 2.0 );
			py = size * 3 / 2 * y;
			break;
		case HexTop::Flat:
		default:
			px = size * 3 / 2 * x;
			py = size * Furrovine::three_root_two<T>( ) * ( y + x / 2.0 );
			break;
		}
		return{ static_cast<T>( px ), static_cast<T>( py ) };
	}

	bool operator == ( const THexAxial<T>& right ) const {
		return static_cast<const base_t&>( *this ) == static_cast<const base_t&>( right );
	}

	bool operator != ( const THexAxial<T>& right ) {
		return static_cast<const base_t&>( *this ) == static_cast<const base_t&>( right );
	}
};
