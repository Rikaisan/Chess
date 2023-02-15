#include "Piece.h"

std::map<Piece::Type, std::string> Piece::STRING_MAPPINGS = {
	   {Piece::Type::King, "king"},
	   {Piece::Type::Queen, "queen"},
	   {Piece::Type::Bishop, "bishop"},
	   {Piece::Type::Knight, "knight"},
	   {Piece::Type::Rook, "rook"},
	   {Piece::Type::Pawn, "pawn"}
};

std::map<char, Piece::Type> Piece::FEN_MAPPINGS = {
	   {'k', Piece::Type::King },
	   {'q', Piece::Type::Queen },
	   {'b', Piece::Type::Bishop },
	   {'n', Piece::Type::Knight },
	   {'r', Piece::Type::Rook },
	   {'p', Piece::Type::Pawn }
};

Piece::Piece(Type type, Color color) : type(type), color(color) {}