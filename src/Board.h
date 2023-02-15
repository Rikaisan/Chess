#pragma once

#include "SFML/Graphics.hpp"
#include <array>

class Board
{
public:
	Board();
	void draw(sf::RenderWindow &window);
private:
	// Light, Dark
	std::array<sf::Color, 2> m_boardColors = { sf::Color(0xF0D9B5FF), sf::Color(0xB58863FF) };
	sf::Texture m_boardTexture;
	sf::Sprite m_boardSprite;

	void setupSprite();
};

