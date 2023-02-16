#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <array>
#include <memory>
#include "Piece.h"

using TexturePtr = std::shared_ptr<sf::Texture>;

class BoardRenderer
{
public:
	BoardRenderer(bool drawCoordinates = true);
	void setRenderSize(uint32_t containerHeight);
	const sf::Sprite& getCurrentPositionSprite(Piece piece = Piece(), int hoveringX = 0, int hoveringY = 0);
	void updatePosition(const std::array<Piece, 64>& pieces);
private:
	std::array<sf::Color, 2> m_boardColors = { sf::Color(0xF0D9B5FF), sf::Color(0xB58863FF) }; // Light, Dark
	std::unordered_map<std::string, TexturePtr> m_textureCache;

	sf::Sprite m_emptyBoardSprite;
	sf::Sprite m_lastPositionSprite;
	sf::Sprite m_hoveringPositionSprite;

	uint32_t m_containerSize;
	float m_cellSize;
	float m_pieceScale = 1;

	std::string m_spritesDirectory = "assets/piece_packs/";
	std::string m_selectedPiecePack = "clean";
	std::unordered_map<Piece::Type, std::array<sf::Sprite, 2>> m_pieceSprites;

	bool m_renderCoordinates = true;
	std::string m_fontFile = "assets/fonts/Poppins-Medium.ttf";
	sf::Font m_font;
	uint32_t m_fontSize;
	float m_coordinatesPadding = 7.0f;

	void setupBoardSprite();
	void setupPieceSprites();

	sf::Sprite& getSpriteFromPiece(Piece piece);
	void drawPiece(Piece piece, int8_t square, sf::RenderTarget& target);
	void drawSprite(sf::Sprite& sprite, int8_t square, sf::RenderTarget& target);
	void drawText(std::string string, int8_t square, sf::RenderTarget& target, uint8_t position = 0);
	void drawCurrentPiecePack(sf::RenderTarget& target);
	void drawCellNumbers(sf::RenderTarget& target);
};
