#pragma once

#include "HexTop.h"
#include <Furrovine++/TVector2.h>
#include <Furrovine++/TVector3.h>

template <typename T>
struct THexCube : public Furrovine::TVector3<T> {
	typedef TVector3<T> base_t;

	template <typename Ta, typename Tv>
	THexCube( Ta&& arr, Tv v ) : Furrovine::TVector3<T>( std::forward<Ta>( arr ), v ) {

	}

	template <typename Tx, typename Ty, typename Tz>
	THexCube( Tx x, Ty y, Tz z ) : Furrovine::TVector3<T>( static_cast<T>( x ), static_cast<T>( y ), static_cast<T>( z ) ) {

	}

	THexCube( std::initializer_list<T> l ) : THexCube( l.begin( )[ 0 ], l.begin( )[ 1 ], l.begin( )[ 2 ] ) {

	}

	THexCube( T x, T y, T z ) : Furrovine::TVector3<T>( x, y, z ) {

	}

	template <typename Arith, HexTop top>
	THexCube( Furrovine::TVector2<T> p, Arith size, std::integral_constant<HexTop, top> = default_hextop_constant ) {
		double q, r;
		switch ( top ) {
		case HexTop::Pointy:
			q = ( 1.0 / 3.0 * Furrovine::three_root_two<T>( ) * p.x - 1.0 / 3.0 * p.Y ) / size;
			r = 2.0 / 3.0 * p.y / size;
			break;
		case HexTop::Flat:
		default:
			q = 2.0 / 3.0 * p.x / size;
			r = ( 1.0 / 3.0 * Furrovine::three_root_two<T>( ) * p.y - 1.0 / 3.0 * p.X ) / size;
			break;
		}
		x = static_cast<T>( q );
		y = static_cast<T>( r );
		z = static_cast<T>( -q - r );
	}

	T sum( ) const {
		return x + y + z;
	}

	template <HexTop top = default_hextop>
	Furrovine::TVector2<T> pixel( double size ) {
		double x, y;
		switch ( top ) {
		case HexTop.Pointy:
			x = size * Furrovine::three_root_two( ) * ( x + z / 2.0 );
			y = size * 3.0 / 2.0 * z;
			break;
		case HexTop.Flat:
		default:
			x = size * 3.0 / 2.0 * x;
			y = size * Furrovine::three_root_two( ) * ( z + x / 2.0 );
			break;
		}
		return Furrovine::TVector2<T>( static_cast<T>( x ), static_cast<T>( y ) );
	}

	bool operator == ( const THexCube& right ) const {
		return static_cast<const base_t&>( left ) == static_cast<const base_t&>( right );
	}

	bool operator != ( const THexCube& right ) const {
		return static_cast<const base_t&>( left ) != static_cast<const base_t&>( right );
	}
};
