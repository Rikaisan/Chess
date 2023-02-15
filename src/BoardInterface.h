#pragma once
#include "BoardEngine.h"
#include "BoardRenderer.h"

class BoardInterface {
public:
	BoardInterface(uint32_t containerWidth = 640, bool useDefaultLayout = true);
	void setContainerWidth(uint32_t width);
	void loadPosition(std::string fenString);
	const sf::Sprite& getSprite();
private:
	BoardEngine m_engine;
	BoardRenderer m_renderer;
	uint32_t m_containerWidth;
};

