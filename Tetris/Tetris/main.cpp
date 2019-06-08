#include "Definitions.hpp"

int main() {
	srand(time(NULL));
	float time;
	int score;

	Draw draw;
	Logic gameLogic;
	sf::Clock clock;
	sf::Font font;

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), APPLICATION_NAME);
	sf::Texture t1, t2, t3, t4;

	sf::Text sc, scores;
	draw.setFont(sc, scores, font);

	//Loading textures
	t1.loadFromFile(TETROMINO_FILEPATH);
	t2.loadFromFile(BACKGROUND_FILEPATH);
	t3.loadFromFile(START_FILEPATH);
	t4.loadFromFile(END_FILEPATH);
	//Work with Sprite
	sf::Sprite s(t1);
	sf::Sprite background(t2);
	sf::Sprite start_screen(t3);
	sf::Sprite end_screen(t4);

	//Splash state
	window.draw(start_screen);
	window.display();
	gameLogic.waiting();

	//Game Loop
	while (window.isOpen()) {
		gameLogic.getEvent(window);
		time = clock.getElapsedTime().asSeconds();
		clock.restart();
		gameLogic.setElapsedTime(time);
		gameLogic.move();
		gameLogic.setTetrominos();
		score = gameLogic.rowBlasting();
		gameLogic.resetParameters();
		window.draw(background);
		draw.drawing(gameLogic, window, s, sc, scores, score);
		window.display();
		gameLogic.end(end_screen, window);
	}
	return EXIT_SUCCESS;
}
