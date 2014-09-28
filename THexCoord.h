#pragma once

#include "THexAxial.h"
#include "THexCube.h"

template <typename T>
THexAxial<T> to_hexaxial( const THexCube<T>& cube ) {
	return THexAxial<T>( cube.x, cube.z );
}

template <typename T>
THexCube<T> to_hexcube( const THexAxial<T>& axial ) {
	return THexCube<T>( axial.x, -axial.x - axial.y, axial.y );
}

template <HexTop top = default_hextop, typename T>
auto to_pixel( T&& coord, double size ) {
	return coord.pixel( size );
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
	return to_hexaxial( round( to_hexcube( ax ) ) );
}
