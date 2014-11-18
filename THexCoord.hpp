#pragma once

#include "HexTop.hpp"
#include "HexDirection.hpp"
#include <Furrovine++/bounds.hpp>
#include <Furrovine++/Vector2.hpp>
#include <Furrovine++/Vector3.hpp>

template <typename T>
struct THexAxial;

template <typename T>
struct THexCube;

template <typename T>
struct THexAxial : public Furrovine::TVector2<T> {
	const static Furrovine::Vector2z Neighbors[ 6 ];
	typedef Furrovine::TVector2<T> base_t;

	template <typename... Tn>
	THexAxial( Tn&&... argn ) : base_t( std::forward<Tn>( argn )... ) {

	}

	THexAxial( std::initializer_list<T> l ) : base_t( std::move( l ) ) {

	}

	template <typename Tv, typename Arith, HexTop top>
	THexAxial( Furrovine::TVector2<Tv> pixel, Arith size, std::integral_constant<HexTop, top> = default_hextop_constant ) {
		double px, py;
		switch ( top ) {
		case HexTop::Pointy:
			px = ( 1.0 / 3.0 * Furrovine::three_root_two<T>( ) * pixel.x - 1.0 / 3.0 * pixel.y ) / size;
			py = 2.0 / 3.0 * pixel.y / size;
			break;
		case HexTop::Flat:
		default:
			px = 2.0 / 3.0 * pixel.x / size;
			py = ( 1.0 / 3.0 * Furrovine::three_root_two<T>( ) * pixel.y - 1.0 / 3.0 * pixel.x ) / size;
			break;
		}
		this->x = static_cast<T>( px );
		this->y = static_cast<T>( py );
	}

	THexAxial( const THexCube<T>& );

	THexAxial( THexCube<T>&& );

	T s( ) const {
		return -x - y;
	}

	THexAxial neighbor( HexDirection direction ) const {
		const auto& entry = Neighbors[ static_cast<std::ptrdiff_t>( direction ) ];
		return THexAxial<T>( *this + entry );
	}

	THexAxial shift( HexDirection direction, std::ptrdiff_t magnitude = 1 ) const {
		THexAxial<T> ax = *this;
		std::ptrdiff_t magsign = Furrovine::sign( magnitude );
		for ( std::ptrdiff_t i = 0; i != magnitude; i += magsign ) {
			ax = ax.neighbor( direction );
		}
		return ax;
	}

	template <HexTop top = default_hextop>
	Furrovine::TVector2<T> to_pixel( double size ) const {
		double px, py;
		switch ( top ) {
		case HexTop::Pointy:
			px = size * Furrovine::three_root_two<T>( ) * ( this->x + this->y / 2.0 );
			py = size * 3.0 / 2.0 * this->y;
			break;
		case HexTop::Flat:
		default:
			px = size * 3.0 / 2.0 * this->x;
			py = size * Furrovine::three_root_two<T>( ) * ( this->y + this->x / 2.0 );
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
	const static Furrovine::Vector3z Neighbors[ 6 ];
	typedef Furrovine::TVector3<T> base_t;

	template <typename... Tn>
	THexCube( Tn&&... argn ) : base_t( std::forward<Tn>( argn )... ) {

	}

	THexCube( const THexAxial<T>& );
	THexCube( THexAxial<T>&& );

	template <typename Tv, typename Arith, HexTop top>
	THexCube( Furrovine::TVector2<Tv> pixel, Arith size, std::integral_constant<HexTop, top> = default_hextop_constant ) {
		double px, py;
		switch ( top ) {
		case HexTop::Pointy:
			px = ( 1.0 / 3.0 * Furrovine::three_root_two<T>( ) * pixel.x - 1.0 / 3.0 * pixel.Y ) / size;
			py = 2.0 / 3.0 * pixel.y / size;
			break;
		case HexTop::Flat:
		default:
			px = 2.0 / 3.0 * pixel.x / size;
			py = ( 1.0 / 3.0 * Furrovine::three_root_two<T>( ) * pixel.y - 1.0 / 3.0 * pixel.X ) / size;
			break;
		}
		this->x = static_cast<T>( px );
		this->y = static_cast<T>( py );
		this->z = static_cast<T>( -px - py );
	}

	T sum( ) const {
		return x + y + z;
	}

	THexCube neighbor( HexDirection direction ) const {
		const auto& entry = Neighbors[ static_cast<std::ptrdiff_t>( direction ) ];
		return THexCube<T>( *this + entry );
	}

	THexCube shift( HexDirection direction, std::ptrdiff_t magnitude = 1 ) const {
		THexCube<T> ax = *this;
		std::ptrdiff_t magsign = Furrovine::sign( magnitude );
		for ( std::ptrdiff_t i = 0; i != magnitude; i += magsign ) {
			ax = ax.neighbor( direction );
		}
		return ax;
	}

	template <HexTop top = default_hextop>
	Furrovine::TVector2<T> to_pixel( double size ) const {
		double px, py;
		switch ( top ) {
		case HexTop.Pointy:
			px = size * Furrovine::three_root_two( ) * ( this->x + this->z / 2.0 );
			py = size * 3.0 / 2.0 * this->z;
			break;
		case HexTop.Flat:
		default:
			px = size * 3.0 / 2.0 * this->x;
			py = size * Furrovine::three_root_two( ) * ( this->z + this->x / 2.0 );
			break;
		}
		return Furrovine::TVector2<T>( static_cast<T>( px ), static_cast<T>( py ) );
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

template <typename T>
const Furrovine::Vector2z THexAxial<T>::Neighbors[ 6 ] = {
		{ +1, 0 }, { +1, -1 }, { 0, -1 },
		{ -1, 0 }, { -1, +1 }, { 0, +1 }
};

template <typename T>
const Furrovine::Vector3z THexCube<T>::Neighbors[ 6 ] = {
	{ +1, -1, 0 }, { +1, 0, -1 }, { 0, +1, -1 },
	{ -1, +1, 0 }, { -1, 0, +1 }, { 0, -1, +1 }
};

template <HexTop top = default_hextop, typename T>
auto to_pixel( T&& coord, double size ) -> decltype( coord.to_pixel( size ) ) {
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
	return THexAxial<T>( round( THexCube<T>( ax ) ) );
}

inline std::ptrdiff_t hex_count( std::ptrdiff_t r ) {
	return 1 + ( 3 * r ) + ( 3 * r *r );
}

template <typename T>
T hex_distance( const THexCube<T>& h1, const THexCube<T>& h2 ) {
	return std::max( std::abs( h1.x - h2.x ), std::abs( h1.y - h2.y ), Std::abs( h1.z - h2.z ) );
}

template <typename T>
T hex_distance( const THexAxial<T>& h1, const THexAxial<T>& h2 ) {
	return ( std::abs( h1.x - h2.x ) + abs( h1.y - h2.y )
		+ std::abs( h1.x + h1.y - h2.x - h2.y ) ) / static_cast<T>( 2 );
}

inline Furrovine::bounds<2> hex_storage_bounds( std::ptrdiff_t r ) {
	std::ptrdiff_t dim = r * 2 + 1;
	return{ dim, dim };
}

inline std::size_t hex_storage_size( std::ptrdiff_t r ) {
	std::ptrdiff_t dim = r * 2 + 1;
	return dim * dim;
}
