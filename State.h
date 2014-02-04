#pragma once

struct State {
public:
	bool Renderable;
	bool Updatable;
	bool StopsRender;
	bool StopsUpdate;

	State( );

	virtual void Update( );
	virtual void Render( );

	virtual ~State( );

};
