#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <array>
#include "Piece.h"

class BoardEngine {
public:
	BoardEngine();
	BoardEngine(std::string fenString);

	const std::array<Piece, 64>& getRawBoard() const;
	void placePiece(Piece piece, uint8_t index);
	void removePiece(uint8_t index);
	void loadFenString(std::string fenString);
	void reset();
	int8_t getEnPassantPawn() const;
	const std::array<bool, 2>& getCastlingRights(Piece::Color color) const;
private:
	std::array<Piece, 64> m_pieces;
	int8_t m_playerToMove = 0; // 0 for white, 1 for black
	int8_t m_enPassantPawn = -1; // -1 for none
	uint8_t m_halfmoveClock = 0;
	uint8_t m_fullmoveCounter = 0;
	std::unordered_map<Piece::Color, std::array<bool, 2>> m_castlingRights; // King - Queen
};

