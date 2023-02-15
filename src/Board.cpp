#include "Board.h"

Board::Board() {
	setupBoardSprite();
}

void Board::setRenderSize(uint32_t containerHeight) {
	m_containerSize = containerHeight;
	m_cellSize = containerHeight / 8.0f;

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

const sf::Sprite& Board::getSprite()
{
	sf::RenderTexture boardRenderer;
	boardRenderer.create(m_containerSize, m_containerSize);
	boardRenderer.draw(m_emptyBoardSprite);
	drawCurrentPiecePack(boardRenderer);
	boardRenderer.display();

	TexturePtr lastPositionTexture = std::make_shared<sf::Texture>(boardRenderer.getTexture());
	m_textureCache["lastPosition"] = lastPositionTexture;
	m_lastPositionSprite = sf::Sprite(*lastPositionTexture);

	return m_lastPositionSprite;
}

void Board::setupBoardSprite() {
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

	TexturePtr emptyBoard = std::make_shared<sf::Texture>(boardTexture.getTexture());
	m_textureCache.insert({ "emptyBoard", emptyBoard });
	m_emptyBoardSprite = sf::Sprite(*emptyBoard);
}

void Board::setupPieceSprites() {
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

void Board::drawPiece(Piece piece, int8_t square, sf::RenderTarget& target) {
	if (square < 0 || square >= 64 || piece.type == Piece::Type::None) return;
	auto& sprite = m_pieceSprites.at(piece.type).at(piece.color == Piece::Color::White ? 0 : 1);
	drawSprite(sprite, square, target);
}

void Board::drawSprite(sf::Sprite& sprite, int8_t square, sf::RenderTarget& target) {
	if (square < 0 || square >= 64) return;
	sprite.setPosition(square % 8 * m_cellSize + m_cellSize / 2.0f, square / 8 * m_cellSize + m_cellSize / 2.0f);
	target.draw(sprite);
}

void Board::drawCurrentPiecePack(sf::RenderTarget& target) {
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