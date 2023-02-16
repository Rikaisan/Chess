#include "BoardRenderer.h"

BoardRenderer::BoardRenderer(bool drawCoordinates) {
	m_renderCoordinates = drawCoordinates;
	setupBoardSprite();
	m_font.loadFromFile(m_fontFile);
}

void BoardRenderer::setRenderSize(int containerHeight) {
	m_containerSize = containerHeight;
	m_cellSize = containerHeight / 8.0f;
	m_fontSize = m_cellSize / 5.0f;

	m_emptyBoardSprite.setScale(m_cellSize, m_cellSize);

	if (m_pieceSprites.empty())
		setupPieceSprites();

	float targetPieceHeight = m_cellSize * m_pieceScale;
	for (auto& [_, sprites] : m_pieceSprites) {
		for (auto& sprite : sprites) {
			auto textureHeight = sprite.getTexture()->getSize().y;
			sprite.setScale(targetPieceHeight / textureHeight, targetPieceHeight / textureHeight);
		}
	}
}

const sf::Sprite& BoardRenderer::getCurrentPositionSprite(Piece piece, int hoveringX, int hoveringY) {
	if (!piece.isNone()) {
		sf::RenderTexture boardRenderer;
		boardRenderer.create(m_containerSize, m_containerSize);
		boardRenderer.draw(m_lastPositionSprite);
		auto& sprite = getSpriteFromPiece(piece);
		sprite.setPosition(hoveringX, hoveringY);
		boardRenderer.draw(sprite);
		boardRenderer.display();

		TexturePtr hoveringPositionTexture = std::make_shared<sf::Texture>(boardRenderer.getTexture());
		m_textureCache["hoveringPosition"] = hoveringPositionTexture;
		m_hoveringPositionSprite = sf::Sprite(*hoveringPositionTexture);
	}
	else if (!m_textureCache.contains("hoveringPosition")) {
		sf::RenderTexture boardRenderer;
		boardRenderer.create(m_containerSize, m_containerSize);
		boardRenderer.draw(m_lastPositionSprite);
		boardRenderer.display();

		TexturePtr hoveringPositionTexture = std::make_shared<sf::Texture>(boardRenderer.getTexture());
		m_textureCache["hoveringPosition"] = hoveringPositionTexture;
		m_hoveringPositionSprite = sf::Sprite(*hoveringPositionTexture);
	}

	return m_hoveringPositionSprite;
}

void BoardRenderer::updatePosition(const std::array<Piece, 64>& pieces) {
	sf::RenderTexture boardRenderer;
	boardRenderer.create(m_containerSize, m_containerSize);
	boardRenderer.draw(m_emptyBoardSprite);
	drawCellNumbers(boardRenderer);
	for (int8_t i{ 0 }; i < 64; ++i) {
		if (m_renderCoordinates) {
			if (i % 8 == 0) {
				char rank = '1' + i / 8;
				drawText(std::string(1, rank), i, boardRenderer, 1);
			}
			if (i / 8 == 7) {
				char file = 'a' + i % 8;
				drawText(std::string(1, file), i, boardRenderer, 4);
			}
		}
		if (!pieces.at(i).isNone())
			drawPiece(pieces.at(i), i, boardRenderer);
	}

	boardRenderer.display();

	TexturePtr lastPositionTexture = std::make_shared<sf::Texture>(boardRenderer.getTexture());
	m_textureCache["lastPosition"] = lastPositionTexture;
	m_lastPositionSprite = sf::Sprite(*lastPositionTexture); // Create new sprite in case container size changes
	m_hoveringPositionSprite = sf::Sprite(*lastPositionTexture); // Reset sprite after releasing a hovering piece
}

void BoardRenderer::setupBoardSprite() {
	// Setup board texture as an 8x8 Texture which is expected to be scaled up later
	sf::RenderTexture boardTexture;
	boardTexture.create(8, 8);
	boardTexture.clear(m_boardColors.at(1));

	sf::RectangleShape lightSquare(sf::Vector2f(1, 1));
	lightSquare.setFillColor(m_boardColors.at(0));
	for (uint8_t i{ 0 }; i < 8; ++i) {
		for (uint8_t j{ 0 }; j < 8; ++j) {
			if ((i + j) % 2 == 0) {
				lightSquare.setPosition(i, j);
				boardTexture.draw(lightSquare);
			}
		}
	}
	boardTexture.display();

	TexturePtr emptyBoard = std::make_shared<sf::Texture>(boardTexture.getTexture());
	m_textureCache.insert({ "emptyBoard", emptyBoard });
	m_emptyBoardSprite = sf::Sprite(*emptyBoard);
}

void BoardRenderer::setupPieceSprites() {
	// Cache piece sprites to only have 1 per piece loaded at all times
	sf::Image spriteSheet;
	spriteSheet.loadFromFile(m_spritesDirectory + m_selectedPiecePack + ".png");
	sf::Vector2u pieceSize = { spriteSheet.getSize().x / 6, spriteSheet.getSize().y / 2};
	int currentX = 0;

	for (auto& [type, name] : Piece::STRING_MAPPINGS) {
		std::array<sf::Sprite, 2> sprites;
		for (size_t i{ 0 }; i < 2; ++i) {
			TexturePtr texture = std::make_shared<sf::Texture>();
			m_textureCache.insert({ name + '_' + std::to_string(i), texture });
			texture->loadFromImage(spriteSheet, sf::IntRect(currentX, pieceSize.y * i, pieceSize.x, pieceSize.y));
			texture->setSmooth(true);
			auto sprite = sf::Sprite(*texture);
			sprite.setOrigin(pieceSize.x / 2.0f, pieceSize.y / 2.0f);
			sprites.at(i) = sprite;
		}
		currentX += pieceSize.x;
		m_pieceSprites.insert({ type, sprites });
	}

}

sf::Sprite& BoardRenderer::getSpriteFromPiece(Piece piece)
{
	return m_pieceSprites.at(piece.type).at(piece.color == Piece::Color::White ? 0 : 1);
}

void BoardRenderer::drawPiece(Piece piece, int8_t square, sf::RenderTarget& target) {
	if (square < 0 || square >= 64 || piece.type == Piece::Type::None) return;
	drawSprite(getSpriteFromPiece(piece), square, target);
}

void BoardRenderer::drawSprite(sf::Sprite& sprite, int8_t square, sf::RenderTarget& target) {
	if (square < 0 || square >= 64) return;
	sprite.setPosition(square % 8 * m_cellSize + m_cellSize / 2.0f, square / 8 * m_cellSize + m_cellSize / 2.0f);
	target.draw(sprite);
}

void BoardRenderer::drawText(std::string string, int8_t square, sf::RenderTarget& target, uint8_t position, sf::Color customColor, bool useLargeFont) {
	if (square < 0 || square >= 64) return;

	sf::Text text;
	text.setFont(m_font);
	if (useLargeFont)
		text.setCharacterSize(m_fontSize * 2);
	else
		text.setCharacterSize(m_fontSize);
	if (customColor == sf::Color::Transparent)
		text.setFillColor(m_boardColors.at((square - (square / 8 % 2 == 0)) % 2 != 0)); // Use swapped board colors
	else
		text.setFillColor(customColor);
	text.setString(string);

	// Center origin
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);

	sf::Vector2f pos;

	if (position == 0) {
		pos = sf::Vector2f(square % 8 * m_cellSize + m_cellSize / 2.0f, square / 8 * m_cellSize + m_cellSize / 2.0f);
	}
	else {
		if (position % 2 == 0)
			pos.x = (1 + square % 8) * m_cellSize - m_cellSize / m_coordinatesPadding; // Right Positions
		else
			pos.x = square % 8 * m_cellSize + m_cellSize / m_coordinatesPadding; // Left Positions

		if (position > 2)
			pos.y = (1 + square / 8) * m_cellSize - m_cellSize / m_coordinatesPadding; // Bottom positions
		else
			pos.y = square / 8 * m_cellSize + m_cellSize / m_coordinatesPadding; // Upper positions
	}

	text.setPosition(pos);
	target.draw(text);
}

void BoardRenderer::drawCurrentPiecePack(sf::RenderTarget& target) {
	int8_t currentPosition = 0;
	for (auto& [type, sprites] : m_pieceSprites) {
		for (auto& sprite : sprites) {
			drawSprite(sprite, currentPosition, target);
			++currentPosition;
		}
	}
	drawSprite(m_pieceSprites.at(Piece::Type::Pawn).at(0), 43, target);
	drawSprite(m_pieceSprites.at(Piece::Type::Pawn).at(1), 44, target);
}

void BoardRenderer::drawCellNumbers(sf::RenderTarget& target) {
	for (int8_t i{ 0 }; i < 64; ++i) drawText(std::to_string(i), i, target, 0, sf::Color(0x00000020), true);
}
