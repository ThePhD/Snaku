#include "StateStack.h"

void StateStack::Render( ) {
	for ( std::size_t i = 0; i < states.size( ); ++i ) {
		State& state = *states[ i ];
		state.Render( );
		if ( state.StopsRender )
			break;
	}
}

void StateStack::Update( ) {
	for ( std::size_t i = 0; i < states.size( ); ++i ) {
		State& state = *states[ i ];
		state.Update( );
		if ( state.StopsUpdate )
			break;
	}
}

void StateStack::Pop( ) {
	states.pop_back( );
}

void StateStack::Push( State* state ) {
	states.push_back( state );
}

StateStack::StateStack( ) {

}
