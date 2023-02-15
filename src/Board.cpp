#include "Board.h"

Board::Board() {
	setupSprite();
}

void Board::draw(sf::RenderWindow &window) {
	if (m_boardSprite.getScale() == sf::Vector2f(1, 1)) {
		auto windowSize = window.getSize();
		m_boardSprite.setScale(windowSize.x / 8, windowSize.y / 8);
	}

	window.draw(m_boardSprite);
}

void Board::setupSprite() {
	// Setup board texture as an 8x8 Texture which is expected to be scaled up later
	sf::RenderTexture boardTexture;
	boardTexture.create(8, 8);
	boardTexture.clear(m_boardColors.at(1));

	sf::RectangleShape lightSquare(sf::Vector2f(1, 1));
	lightSquare.setFillColor(m_boardColors.at(0));
	for (size_t i{ 0 }; i < 8; ++i) {
		for (size_t j{ 0 }; j < 8; ++j) {
			if (i % 2 == 0 && j % 2 == 0 || i % 2 != 0 && j % 2 != 0) {
				lightSquare.setPosition(i, j);
				boardTexture.draw(lightSquare);
			}
		}
	}
	boardTexture.display();
	m_boardTexture = boardTexture.getTexture();
	m_boardSprite = sf::Sprite(m_boardTexture);
}
