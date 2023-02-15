#include "BoardInterface.h"

BoardInterface::BoardInterface(uint32_t containerWidth, bool useDefaultLayout) {
	if (useDefaultLayout) {
		m_engine.loadFenString("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 0");
		setContainerWidth(containerWidth);
	}
}

void BoardInterface::setContainerWidth(uint32_t width) {
	m_containerWidth = width;
	m_renderer.setRenderSize(width);
	m_renderer.updatePosition(m_engine.getRawBoard());
}

void BoardInterface::loadPosition(std::string fenString) {
	m_engine.loadFenString(fenString);
	m_renderer.updatePosition(m_engine.getRawBoard());
}

const sf::Sprite& BoardInterface::getSprite() {
	return m_renderer.getCurrentPositionSprite();
}
