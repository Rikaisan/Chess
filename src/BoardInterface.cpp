#include "BoardInterface.h"

#include "Utils.h"

BoardInterface::BoardInterface(int containerWidth, bool useDefaultLayout) {
	if (useDefaultLayout) {
		m_engine.loadFenString(DEFAULT_POSITION);
	}
	setContainerWidth(containerWidth);
}

void BoardInterface::setContainerWidth(uint32_t width) {
	m_containerWidth = width;
	m_cellWidth = width / 8.0f;
	m_renderer.setRenderSize(width);
	m_renderer.updatePosition(m_engine.getRawBoard());
}

void BoardInterface::loadPosition(std::string fenString) {
	m_engine.loadFenString(fenString);
	m_renderer.updatePosition(m_engine.getRawBoard());
}

bool BoardInterface::grabPieceAt(int x, int y) {
	uint8_t file = x / m_cellWidth;
	uint8_t rank = y / m_cellWidth;
	uint8_t cell = rank * 8 + file;

	if (m_holdedPiece == -1) {
		Piece clickedPiece = m_engine.getPiece(cell);
		if (clickedPiece.isNone()) return false;

		m_holdedPiece = cell;
		
		m_renderer.updatePosition(m_engine.getRawBoard(), cell);
		return true;
	}

	return false;
}

bool BoardInterface::dropPieceAt(int x, int y) {
	if (m_holdedPiece == -1) return false;
	if (x < 0 || x >= m_containerWidth || y < 0 || y >= m_containerWidth) {
		resetHoldingPiece();
		return false;
	}

	uint8_t file = x / m_cellWidth;
	uint8_t rank = y / m_cellWidth;
	uint8_t cell = rank * 8 + file;


	Piece holdedPiece = m_engine.getPiece(m_holdedPiece);


	Piece pieceOnCell = m_engine.getPiece(cell);

	bool wasMoved = m_engine.movePiece(m_holdedPiece, cell);
	resetHoldingPiece();
	return wasMoved;
}

const sf::Sprite& BoardInterface::getSprite(int mouseX, int mouseY) {
	return m_renderer.getCurrentPositionSprite(m_engine.getPiece(m_holdedPiece), mouseX, mouseY);
}

void BoardInterface::loadDefaultPosition() {
	loadPosition(DEFAULT_POSITION);
}

void BoardInterface::resetHoldingPiece() {
	m_renderer.updatePosition(m_engine.getRawBoard());
	m_holdedPiece = -1;
}
