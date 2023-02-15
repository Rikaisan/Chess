#pragma once

#include <SFML/Graphics.hpp>
#include "Board.h"

class Game {
public:
	Game();
	void run();
private:
	Board m_board;
	sf::RenderWindow m_window;
	sf::Vector2u m_windowSize = { 880, 880 } ;
};