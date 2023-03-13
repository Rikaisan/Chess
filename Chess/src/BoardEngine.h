#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <array>
#include "Piece.h"

struct Coordinates {
	union {
		int8_t row = 0;
		int8_t y;
	};
	union {
		int8_t rank = 0;
		int8_t x;
	};
};

class BoardEngine {
public:
	BoardEngine();
	BoardEngine(std::string fenString);

	const std::array<Piece, 64>& getRawBoard() const;
	Piece getPiece(int8_t index) const;
	void placePiece(Piece piece, int8_t index);
	bool removePiece(int8_t index);
	void loadFenString(std::string fenString);
	void reset();
	int8_t getEnPassantPawn() const;
	const std::array<bool, 2>& getCastlingRights(Piece::Color color) const;
	bool movePiece(int8_t sourceIndex, int8_t targetIndex, bool allowGlobalMovement = false, bool bypassLegalCheck = false);
private:
	std::array<Piece, 64> m_pieces;
	std::array<std::array<Piece*, 8>, 8> m_board;
	int8_t m_playerToMove = 0; // 0 for white, 1 for black
	int8_t m_enPassantPawn = -1; // -1 for none
	uint8_t m_halfmoveClock = 0;
	uint8_t m_fullmoveCounter = 0;
	std::unordered_map<Piece::Color, std::array<bool, 2>> m_castlingRights; // King - Queen
	//const std::array<int8_t, 16> m_movementOffsets = {
	//	-9, -7, 9, 7, // Diagonals
	//	-8, 1, 8, -1, // Straight lines
	//	-10, -17, -15, -6, 10, 17, 15, 6 // Knight (L's)
	//};

	const std::array<Coordinates, 16> m_movementOffsets = {
		Coordinates{-1, -1}, // Diagonals
		Coordinates{-1,  1},
		Coordinates{ 1, -1},
		Coordinates{ 1,  1},
		Coordinates{ 0, -1}, // Straight lines
		Coordinates{ 0,  1},
		Coordinates{-1,  0},
		Coordinates{ 1,  0},
		Coordinates{-1, -2}, // Knight (L's)
		Coordinates{-1,  2},
		Coordinates{-2, -1},
		Coordinates{-2,  1},
		Coordinates{ 1, -2},
		Coordinates{ 1,  2},
		Coordinates{ 2, -1},
		Coordinates{ 2,  1}
	};
	const std::array<Coordinates, 8> m_pawnOffsets = {
		Coordinates{-1, -1}, // White
		Coordinates{-1,  1},
		Coordinates{-1,  0},
		Coordinates{-2,  0},
		Coordinates{ 1, -1}, // Black
		Coordinates{ 1,  1},
		Coordinates{ 1,  0},
		Coordinates{ 2,  0}
	};
};

