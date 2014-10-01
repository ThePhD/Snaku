#pragma once

#include "HexTop.h"
#include <Furrovine++/TVector2.h>
#include <Furrovine++/TVector3.h>

template <typename T>
struct THexAxial;

template <typename T>
struct THexCube;

template <typename T>
struct THexAxial : public Furrovine::TVector2<T> {
	typedef Furrovine::TVector2<T> base_t;

	template <typename... Tn>
	THexAxial( Tn&&... argn ) : base_t( std::forward<Tn>( argn )... ) {

	}

	THexAxial( std::initializer_list<T> l ) : base_t( std::move( l ) ) {

	}

	template <typename Arith, HexTop top>
	THexAxial( Furrovine::TVector2<T> pixel, Arith size, std::integral_constant<HexTop, top> = default_hextop_constant ) {
		double q, r;
		switch ( top ) {
		case HexTop::Pointy:
			q = ( 1.0 / 3.0 * Furrovine::three_root_two<T>( ) * pixel.x - 1.0 / 3.0 * pixel.y ) / size;
			r = 2.0 / 3.0 * pixel.y / size;
			break;
		case HexTop::Flat:
		default:
			q = 2.0 / 3.0 * pixel.x / size;
			r = ( 1.0 / 3.0 * Furrovine::three_root_two<T>( ) * pixel.y - 1.0 / 3.0 * pixel.x ) / size;
			break;
		}
		x = static_cast<T>( q );
		y = static_cast<T>( r );
	}

	THexAxial( const THexCube<T>& );

	THexAxial( THexCube<T>&& );

	T s( ) const {
		return -x - y;
	}

	template <HexTop top = default_hextop>
	Furrovine::TVector2<T> to_pixel( double size ) {
		double px, py;
		switch ( top ) {
		case HexTop::Pointy:
			px = size * Furrovine::three_root_two<T>( ) * ( x + y / 2.0 );
			py = size * 3.0 / 2.0 * y;
			break;
		case HexTop::Flat:
		default:
			px = size * 3.0 / 2.0 * x;
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

template <typename T>
struct THexCube : public Furrovine::TVector3<T> {
	typedef Furrovine::TVector3<T> base_t;

	template <typename... Tn>
	THexCube( Tn&&... argn ) : base_t( std::forward<Tn>( argn )... ) {

	}

	THexCube( const THexAxial<T>& );
	THexCube( THexAxial<T>&& );

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
	Furrovine::TVector2<T> to_pixel( double size ) {
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

template <typename T>
THexAxial<T>::THexAxial( const THexCube<T>& cube )
	: base_t( cube.x, cube.z ) {

}

template <typename T>
THexAxial<T>::THexAxial( THexCube<T>&& cube )
	: base_t( cube.x, cube.z ) {

}

template <typename T>
THexCube<T>::THexCube( const THexAxial<T>& axial )
	: base_t( axial.x, -axial.x - axial.y, axial.y ) {

}

template <typename T>
THexCube<T>::THexCube( THexAxial<T>&& axial )
	: base_t( axial.x, -axial.x - axial.y, axial.y ) {

}

template <HexTop top = default_hextop, typename T>
auto to_pixel( T&& coord, double size ) {
	return coord.to_pixel( size );
}

template <typename T>
THexCube<T> round( const THexCube<T>& cube ) {
	double rx = std::round( cube.x );
	double ry = std::round( cube.y );
	double rz = std::round( cube.z );

	double x_diff = std::abs( rx - cube.x );
	double y_diff = std::abs( ry - cube.y );
	double z_diff = std::abs( rz - cube.z );

	if ( x_diff > y_diff && x_diff > z_diff )
		rx = -ry - rz;
	else if ( y_diff > z_diff )
		ry = -rx - rz;
	else
		rz = -rx - ry;

	return THexCube<T>( static_cast<T>(rx), static_cast<T>(ry), static_cast<T>(rz) );
}

template <typename T>
THexAxial<T> round( const THexAxial<T>& ax ) {
	return THexAxial<T>( round( HexCube( ax ) ) );
}