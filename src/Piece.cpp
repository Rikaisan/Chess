#include "Piece.h"

std::map<Piece::Type, std::string> Piece::STRING_MAPPINGS = {
	   {Piece::Type::King, "king"},
	   {Piece::Type::Queen, "queen"},
	   {Piece::Type::Bishop, "bishop"},
	   {Piece::Type::Knight, "knight"},
	   {Piece::Type::Rook, "rook"},
	   {Piece::Type::Pawn, "pawn"}
};

Piece::Piece(Color color, Type type) : color(color), type(type) {}