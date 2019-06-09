#include "Draw.hpp"

	Draw::Draw() {}
	Draw::~Draw() {}

	void Draw::setFont(sf::Text&sc, sf::Text& scores, sf::Font& font) {
		sc.setFillColor(sf::Color::White);
		scores.setFillColor(sf::Color::White);
		sc.Bold;
		sc.setPosition(230, 30);
		scores.setPosition(260, 60);
		sc.setCharacterSize(20);
		scores.setCharacterSize(20);
		font.loadFromFile(FONT_NAME);
		sc.setFont(font);
		sc.setString("Scores");
		scores.setFont(font);
	}

	void Draw::drawing(Logic& gameLogic, sf::RenderWindow& window, sf::Sprite& s, sf::Text& sc, sf::Text& score, int scores) {
		window.draw(sc);
		score.setString(std::to_string(scores));
		window.draw(score);
		//Fallen Tetrominos
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++) {
				if (gameLogic.matrix[i][j]) {
					s.setTextureRect(sf::IntRect(gameLogic.matrix[i][j] * 18, 0, 18, 18));
					s.setPosition(j * 18, i * 18);
					s.move(20, 30);
					window.draw(s);

				}
			}
		}
		//Moving Tetromino
		for (int i = 0; i < 4; i++) {
			s.setTextureRect(sf::IntRect(gameLogic.colorNumber * 18, 0, 18, 18));
			s.setPosition(gameLogic.a[i].x * 18, gameLogic.a[i].y * 18);
			s.move(20, 30);
			window.draw(s);
		}
	}
