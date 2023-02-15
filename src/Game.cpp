#include "Game.h"

Game::Game() {
	m_window.create(sf::VideoMode(m_windowSize.x, m_windowSize.y), "Chess", sf::Style::Close);
	m_window.setFramerateLimit(60);

	sf::Image icon;
	icon.loadFromFile("assets/icon.png");
	m_window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	m_board.setContainerWidth(m_windowSize.y);
}

void Game::run() {
	while (m_window.isOpen()) {
		sf::Event event;

		while (m_window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) m_window.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) m_board.loadPosition("r1bqk2r/p2n1ppp/1p1bpn2/2pp4/3P2P1/1P1BPN1P/PBP2P2/RN1QK2R b Kq g3 0 8");
		}

		m_window.clear(sf::Color::Black);

		m_window.draw(m_board.getSprite());

		m_window.display();
	}
}