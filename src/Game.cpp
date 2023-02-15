#include "Game.h"

Game::Game() {
	m_window.create(sf::VideoMode(m_windowSize.x, m_windowSize.y), "Chess", sf::Style::Close);
	m_window.setFramerateLimit(60);
	m_windowSize = m_window.getSize(); // Cache window size for operations
}

void Game::run() {
	while (m_window.isOpen()) {
		sf::Event event;

		while (m_window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) m_window.close();
		}

		m_window.clear(sf::Color::Black);
		// Content
		m_board.draw(m_window);
		m_window.display();
	}
}