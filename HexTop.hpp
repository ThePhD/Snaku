#pragma once

#include <type_traits>

enum class HexTop {
	Flat,
	Pointy
};

const auto default_hextop = HexTop::Flat;
const std::integral_constant<HexTop, default_hextop> default_hextop_constant = {};
