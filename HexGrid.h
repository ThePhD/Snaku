#pragma once

#include "HexDirection.h"
#include "HexCoord.h"
#include "Hex.h"
#include <Furrovine++/Size2.h>
#include <Furrovine++/optional.h>
#include <Furrovine++/Graphics/NymphBatch.h>
#include <Furrovine++/Graphics/Nymphgon.h>
#include <vector>

class HexGrid {
private:
	const static Furrovine::Vector2z Neighbors[ 6 ];
	std::ptrdiff_t radius;
	std::vector<Hex> hexes;
	Furrovine::buffer_view<Hex, 2> hexesview;
	Furrovine::Graphics::Nymphgon shape;

public:

	HexGrid( std::ptrdiff_t r );

	Hex& operator[] ( const HexAxialz& ax );

	const Hex& operator[] ( const HexAxialz& ax ) const;

	Hex& Neighbor( const Hex& hex, HexDirection direction );

	const Hex& Neighbor( const Hex& hex, HexDirection direction ) const;

	template <typename TFx>
	void for_each( TFx&& fx, HexDirection start = HexDirection::Four );

	void Render( Furrovine::Vector2 offset, Furrovine::Vector2 mouse, Furrovine::Graphics::NymphBatch& batch );

	static std::ptrdiff_t hex_count( std::ptrdiff_t r );

	static Furrovine::bounds<2> storage_bounds( std::ptrdiff_t r );

	static std::size_t storage_size( std::ptrdiff_t r );

};
