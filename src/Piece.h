#pragma once

#include <map>
#include <string>
#include <tuple>

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
	static std::map<char, Type> FEN_MAPPINGS;

	Type type;
	Color color;

	Piece(Type type = Piece::Type::None, Color color = Piece::Color::White);
	bool isNone() const;
	void clear();
};