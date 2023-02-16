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

	if (m_holdedPiece.isNone()) {
		Piece clickedPiece = m_engine.getPiece(cell);
		if (clickedPiece.isNone()) return false;

		m_holdedPiece = clickedPiece;
		m_holdedPieceSourceCell = cell;
		m_engine.removePiece(cell);
		m_renderer.updatePosition(m_engine.getRawBoard());
		return true;
	}

	return false;
}

bool BoardInterface::dropPieceAt(int x, int y)
{
	bool invalidPlacement = false;
	if (x < 0 || x >= m_containerWidth || y < 0 || y >= m_containerWidth) return resetHoldingPiece();
	uint8_t file = x / m_cellWidth;
	uint8_t rank = y / m_cellWidth;
	uint8_t cell = rank * 8 + file;

	if (m_holdedPiece.isNone()) return false;


	Piece pieceOnCell = m_engine.getPiece(cell);
	if (!pieceOnCell.isNone() && m_holdedPiece.color == pieceOnCell.color) invalidPlacement = true;

	if (invalidPlacement) return resetHoldingPiece();

	m_engine.placePiece(m_holdedPiece, cell);
	m_renderer.updatePosition(m_engine.getRawBoard());
	m_holdedPiece.clear();
	return true;
}

const sf::Sprite& BoardInterface::getSprite(int mouseX, int mouseY) {
	return m_renderer.getCurrentPositionSprite(m_holdedPiece, mouseX, mouseY);
}

void BoardInterface::loadDefaultPosition() {
	loadPosition(DEFAULT_POSITION);
}

bool BoardInterface::resetHoldingPiece() {
	m_engine.placePiece(m_holdedPiece, m_holdedPieceSourceCell);
	m_renderer.updatePosition(m_engine.getRawBoard());
	m_holdedPiece.clear();
	return false;
}
