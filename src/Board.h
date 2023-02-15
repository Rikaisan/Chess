#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <array>
#include <memory>
#include "Piece.h"

using TexturePtr = std::shared_ptr<sf::Texture>;

class Board
{
public:
	Board();
	void setRenderSize(uint32_t containerSize);
	const sf::Sprite& getSprite();
private:
	std::array<sf::Color, 2> m_boardColors = { sf::Color(0xF0D9B5FF), sf::Color(0xB58863FF) }; // Light, Dark
	std::unordered_map<std::string, TexturePtr> m_textureCache;

	sf::Sprite m_emptyBoardSprite;
	sf::Sprite m_lastPositionSprite;

	uint32_t m_containerSize;
	float m_cellSize;
	float m_pieceScale = 1;
	std::string m_spritesDirectory = "assets/piece_packs/";
	std::string m_selectedPiecePack = "clean";
	std::unordered_map<Piece::Type, std::array<sf::Sprite, 2>> m_pieceSprites;

	void setupBoardSprite();
	void setupPieceSprites();

	void drawPiece(Piece piece, int8_t square, sf::RenderTarget& target);
	void drawSprite(sf::Sprite& sprite, int8_t square, sf::RenderTarget& target);
	void drawPiecePack(sf::RenderTarget& target);

};

