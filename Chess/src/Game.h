#pragma once

#include <SFML/Graphics.hpp>
#include "BoardInterface.h"

class Game {
public:
	Game();
	void run();
private:
	BoardInterface m_board;
	sf::RenderWindow m_window;
	sf::Vector2u m_windowSize = { 880, 880 } ;
};