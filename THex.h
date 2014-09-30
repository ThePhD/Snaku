#pragma once

#include "THexCoord.h"

template <typename T>
struct THex {
	const static Furrovine::TVector2<std::ptrdiff_t> Neighbors[ 6 ];
	THexAxial<T> axial;
	
	THex( const THexCube<T>& cube ) : axial( cube ) {
		
	}

	THex( const THexAxial<T>& ax ) : axial( ax ) {
		
	}

	double distance_to( const THex<T>& target ) const {
		return ( std::abs( axial.x - target.axial.Q ) + std::abs( axial.R - target.axial.R )
				 + std::abs( axial.Q + axial.R - target.axial.Q - target.axial.R ) ) / 2.0;
	}
};

template <typename T>
const Furrovine::TVector2<std::ptrdiff_t> THex<T>::Neighbors[ 6 ] = {
		{ +1, 0 }, { +1, -1 }, { 0, -1 },
		{ -1, 0 }, { -1, +1 }, { 0, +1 }
};
