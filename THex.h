#pragma once

#include "THexCoord.h"

template <typename T>
struct THex {
	THexAxial<T> axial;
	
	THex( ) : axial( ) {

	}

	THex( const THexCube<T>& cube ) : axial( cube ) {
		
	}

	THex( const THexAxial<T>& ax ) : axial( ax ) {
		
	}

	double distance_to( const THex<T>& target ) const {
		return ( std::abs( axial.x - target.axial.Q ) + std::abs( axial.R - target.axial.R )
				 + std::abs( axial.Q + axial.R - target.axial.Q - target.axial.R ) ) / 2.0;
	}

	THex neighbor( HexDirection hexdirection ) {
		return THex<T>( axial.neighbor( hexdirection ) );
	}
};


