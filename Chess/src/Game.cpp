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
		sf::Vector2i mousePos;
	while (m_window.isOpen()) {
		sf::Event event;


		while (m_window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) m_window.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) m_board.loadPosition("r1bqk2r/p2n1ppp/1p1bpn2/2pp4/3P2P1/1P1BPN1P/PBP2P2/RN1QK2R b Kq g3 0 8");
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) m_board.loadDefaultPosition();
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Left) m_board.grabPieceAt(event.mouseButton.x, event.mouseButton.y);
			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Button::Left) m_board.dropPieceAt(event.mouseButton.x, event.mouseButton.y);
			if (event.type == sf::Event::MouseMoved) mousePos = sf::Vector2i(event.mouseMove.x, event.mouseMove.y);
		}

		m_window.clear(sf::Color::Black);

		m_window.draw(m_board.getSprite(mousePos.x, mousePos.y));

		m_window.display();
	}
}