#include "BoardEngine.h"
#include "Utils.h"

BoardEngine::BoardEngine() {
	this->reset();
}

BoardEngine::BoardEngine(std::string fenString) {
	loadFenString(fenString);
}

const std::array<Piece, 64>& BoardEngine::getRawBoard() const {
	return m_pieces;
}

Piece BoardEngine::getPiece(uint8_t index) const
{
	return m_pieces.at(index);
}

void BoardEngine::placePiece(Piece piece, uint8_t index) {
	if (index < 0 || index >= 64) return;
	m_pieces.at(index) = piece;
}

bool BoardEngine::removePiece(uint8_t index) {
	if (index < 0 || index >= 64) return false;
	if (m_pieces.at(index).isNone()) return false;
	m_pieces.at(index).clear();
	return true;
}

void BoardEngine::loadFenString(std::string fenString) {
	this->reset();
	auto fields = Utils::splitString(fenString, " ");

	// Field 1: Piece positions
	auto ranks = Utils::splitString(fields.at(0), "/");

	int8_t pos = 0;
	for (auto& rank : ranks) {
		for (auto& piece : rank) {
			if (isdigit(piece)) {
				pos += int(piece) - 48; // Numbers start at 48 in the ascii table
			}
			if (Piece::FEN_MAPPINGS.contains(std::tolower(piece))) {
				m_pieces.at(pos).type = Piece::FEN_MAPPINGS.at(std::tolower(piece));
				if (std::islower(piece)) m_pieces.at(pos).color = Piece::Color::Black;
				pos += 1;
			}
		}
	}

	// Field 2: Player to move
	m_playerToMove = std::tolower(fields.at(1).at(0)) == 'b' ? 1 : 0;

	// Field 3: Castling ability
	if (fields.at(2).length() == 1 && fields.at(2).at(0) == '-') {
		for (auto& [color, sides] : m_castlingRights) {
			for (auto& side : sides) {
				side = false;
			}
		}
	}

	for (auto& letter : fields.at(2)) {
		Piece::Color color = Piece::Color::White;
		Piece::Type side = Piece::Type::None;
		if (islower(letter)) color = Piece::Color::Black;
		if (tolower(letter) == 'q') side = Piece::Type::Queen;
		if (tolower(letter) == 'k') side = Piece::Type::King;

		if (side == Piece::Type::King || side == Piece::Type::Queen)
			m_castlingRights[color][side == Piece::Type::Queen] = true;
	}

	// Field 4: En passant target square
	if (!(fields.at(3).length() == 1 && fields.at(3).at(0) == '-')) {
		uint8_t file = int(fields.at(3).at(0)) - 'a';
		uint8_t rank = int(fields.at(3).at(1)) == '3' ? 4 : 3;
		uint8_t targetCell = rank * 8 + file;
		m_enPassantPawn = targetCell;
	}

	// Field 5: Halfmove clock
	m_halfmoveClock = std::stoi(fields.at(4));

	// Field 6: Fullmove counter
	m_fullmoveCounter = std::stoi(fields.at(5));

	Utils::Debug::printBoard(*this);
	Utils::Debug::print("Loaded board with FEN string '", false);
	Utils::Debug::print(fenString, false);
	Utils::Debug::print("'");
}

void BoardEngine::reset() {
	for (int8_t i{ 0 }; i < 64; ++i) m_pieces.at(i).clear();
	for (auto& [color, sides] : m_castlingRights) {
		for (auto& side : sides) {
			side = false;
		}
	}
	m_playerToMove = 0;
	m_halfmoveClock = 0;
}

int8_t BoardEngine::getEnPassantPawn() const {
	return m_enPassantPawn;
}

const std::array<bool, 2>& BoardEngine::getCastlingRights(Piece::Color color) const {
	return m_castlingRights.at(color);
}
