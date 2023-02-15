#pragma once

#include <map>
#include <string>

struct Piece {
	enum class Type {
		None,
		King,
		Queen,
		Bishop,
		Knight,
		Rook,
		Pawn
	};

	enum class Color {
		White,
		Black
	};

	static std::map<Type, std::string> STRING_MAPPINGS;

	Type type;
	Color color;

	Piece(Color color, Type type);
};