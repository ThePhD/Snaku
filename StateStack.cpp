#include "StateStack.h"
#include <algorithm>

void StateStack::Render( ) {
	std::size_t i = states.size( );
	// Find the bottom...
	// Hah, "i goes to 0"
	for ( ; i --> 0; ) {
		State& state = states[ i ];
		if ( state.StopsRender )
			break;
	}
	// Painters algorithm: bottom first, then to the top.
	for ( ; i < states.size(); ++i ) {
		State& state = states[ i ];
		state.Render( );
	}
}

void StateStack::Update( ) {
	for ( std::size_t i = states.size( ); i-- > 0; ) {
		State& state = states[ i ];
		state.Update( );
		if ( state.StopsUpdate )
			break;
	}
}

bool StateStack::is_empty( ) const {
	return states.empty( );
}

bool StateStack::contains( const State& state ) const {
	using std::begin;
	using std::end;
	return std::find_if( begin( states ), end( states ), [ &state ] ( auto&& s ) -> bool { return std::addressof( s.get( ) ) == &state; } ) != states.end( );
}

void StateStack::pop( ) {
	states.pop_back( );
}

State& StateStack::top( ) {
	return states.back( );
}

void StateStack::push( State& state ) {
	states.push_back( state );
}

StateStack::StateStack( ) {

}
