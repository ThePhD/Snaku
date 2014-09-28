#pragma once

#include "HexGrid.h"

struct World {
	float speed = 1.0f;
	float blocksize = 30;
	HexGrid hexgrid;

	World( );

};
