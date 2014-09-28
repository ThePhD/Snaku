#pragma once

#include "THexCoord.h"

template <typename T>
struct THex {
	const static std::ptrdiff_t Neighbors[ 2 ][ 3 ];
	THexAxial<T> axial;
	
	THex( const THexCube<T>& cube )
		: THex( to_hexaxial( cube ) ) {}

	THex( const THexAxial<T>& ax ) : axial( ax ) {
		
	}

	double distance_to( THex<T> target ) {
		return ( std::abs( axial.x - target.axial.Q ) + std::abs( axial.R - target.axial.R )
				 + std::abs( axial.Q + axial.R - target.axial.Q - target.axial.R ) ) / 2.0;
	}
};

template <typename T>
const int THex<T>::Neighbors[ 2 ][ 3 ] = {
		{ +1, 0 }, { +1, -1 }, { 0, -1 },
		{ -1, 0 }, { -1, +1 }, { 0, +1 }
};
