#pragma once
#include "BoardEngine.h"
#include "BoardRenderer.h"

class BoardInterface {
public:
	BoardInterface(uint32_t containerWidth = 640, bool useDefaultLayout = true);
	void setContainerWidth(uint32_t width);
	void loadPosition(std::string fenString);
	bool grabPieceAt(int x, int y);
	bool dropPieceAt(int x, int y);
	const sf::Sprite& getSprite(int mouseX = 0, int mouseY = 0);
	void loadDefaultPosition();
private:
	const std::string DEFAULT_POSITION = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
	BoardEngine m_engine;
	BoardRenderer m_renderer;
	uint32_t m_containerWidth;
	uint32_t m_cellWidth;

	Piece m_holdedPiece;
	uint8_t m_holdedPieceSourceCell = 0;

	bool resetHoldingPiece();
};

