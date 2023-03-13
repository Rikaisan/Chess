#include "BoardEngine.h"
#include "Utils.h"

BoardEngine::BoardEngine() {
	for (int row = 0; row < 8; ++row) {
		for (int rank = 0; rank < 8; ++rank) {
			this->m_board.at(row).at(rank) = &m_pieces.at(row * 8 + rank);
		}
	}
	this->reset();
}

BoardEngine::BoardEngine(std::string fenString) {
	loadFenString(fenString);
}

const std::array<Piece, 64>& BoardEngine::getRawBoard() const {
	return m_pieces;
}

Piece BoardEngine::getPiece(int8_t index) const {
	if (index < 0 || index >= 64) return Piece();
	return m_pieces.at(index);
}

void BoardEngine::placePiece(Piece piece, int8_t index) {
	if (index < 0 || index >= 64) return;
	m_pieces.at(index) = piece;
}

bool BoardEngine::removePiece(int8_t index) {
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
	m_fullmoveCounter = 0;
	m_enPassantPawn = -1;
}

int8_t BoardEngine::getEnPassantPawn() const {
	return m_enPassantPawn;
}

const std::array<bool, 2>& BoardEngine::getCastlingRights(Piece::Color color) const {
	return m_castlingRights.at(color);
}

bool BoardEngine::movePiece(int8_t sourceIndex, int8_t targetIndex, bool allowGlobalMovement, bool bypassLegalCheck) {
	if (sourceIndex >= 64 || targetIndex >= 64) return false;

	Piece piece = getPiece(sourceIndex);
	if (piece.isNone()) return false;
	if (!getPiece(targetIndex).isNone() && piece.color == getPiece(targetIndex).color) return false;
	Coordinates sourceCell { sourceIndex / 8, sourceIndex % 8 };
	Piece& targetPiece = m_pieces.at(targetIndex);

	bool validMove = false;

	if (!allowGlobalMovement) {
		int8_t startingIndex = 0;
		int8_t endingIndex = 0;
		bool applyOffsetOnce = false;

		if (piece.type == Piece::Type::Pawn) {
			if (piece.color == Piece::Color::White) {
				startingIndex = 0;
				endingIndex = sourceCell.row == 6 ? 4 : 3;
			}
			else {
				startingIndex = 4;
				endingIndex = sourceCell.row == 1 ? 8 : 7;
			}

			Coordinates offsetCell = { sourceCell.y, sourceCell.x };
			for (int i = startingIndex; i < endingIndex; ++i) {
				Coordinates offset = m_pawnOffsets.at(i);
				offsetCell.y = sourceCell.y + offset.y;
				offsetCell.x = sourceCell.x + offset.x;
				if (offsetCell.x < 0 || offsetCell.y < 0 || offsetCell.x >= 8 || offsetCell.y >= 8) // Out of bounds
					continue;

				if (m_board.at(offsetCell.row).at(offsetCell.rank) == &targetPiece) {
					if (offset.rank == 0 && !targetPiece.isNone()) // Moving forward when a piece is blocking
						return false;
					if (offset.rank != 0 && targetPiece.isNone()) // Moving diagonally to an empty space
						return false;
					m_pieces.at(targetIndex) = piece;
					m_pieces.at(sourceIndex).clear();
					return true;
				}
			}
			return false;
		}

		if (piece.type == Piece::Type::Queen) {
			startingIndex = 0;
			endingIndex = 8;
		}

		if (piece.type == Piece::Type::King) {
			startingIndex = 0;
			endingIndex = 8;
			applyOffsetOnce = true;
		}

		if (piece.type == Piece::Type::Bishop) {
			startingIndex = 0;
			endingIndex = 4;
		}

		if (piece.type == Piece::Type::Rook) {
			startingIndex = 4;
			endingIndex = 8;
		}

		if (piece.type == Piece::Type::Knight) {
			startingIndex = 8;
			endingIndex = 16;
			applyOffsetOnce = true;
		}

		for (int8_t i{ startingIndex }; i < endingIndex; ++i) {
			auto& offset = m_movementOffsets.at(i);
			Coordinates offsetCell = { sourceCell.y + offset.y, sourceCell.x + offset.x };
			if (applyOffsetOnce) {
				if (offsetCell.x >= 0 && offsetCell.x < 8 && offsetCell.y >=0 && offsetCell.y < 8) {
					if (m_board.at(offsetCell.row).at(offsetCell.rank) == &targetPiece) {
						validMove = true;
						break;
					}
				}
			}
			else {
				while (offsetCell.x >= 0 && offsetCell.x < 8 && offsetCell.y >= 0 && offsetCell.y < 8) {
					if (m_board.at(offsetCell.row).at(offsetCell.rank) == &targetPiece) {
						validMove = true;
						break;
					}
					offsetCell.row += offset.row;
					offsetCell.rank += offset.rank;
				}
				if (validMove) break;
			}
		}
		if (!validMove) return false;
	}
	m_pieces.at(targetIndex) = piece;
	m_pieces.at(sourceIndex).clear();
	return true;
}
