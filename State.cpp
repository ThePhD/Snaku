#include "State.h"

void State::Render( ) {

}

void State::Update( ) {

}

State::State( ) : Renderable( true ), Updatable( true ), StopsRender( true ), StopsUpdate( true ) {

}

State::~State( ) {

}
