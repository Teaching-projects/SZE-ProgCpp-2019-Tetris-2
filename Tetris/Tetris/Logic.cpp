#include "Logic.hpp"

Logic::Logic() :direction(0), colorNumber(1), elapsedTime(0), delay(0.5), a{ 1,1,1,0,2,0,0,0 }, b{0}, scores(0){}
Logic::~Logic(){}

void Logic::getEvent(sf::RenderWindow& window){
	if (window.pollEvent(e)) {
		if (e.type == sf::Event::Closed)window.close();
		else if (e.type == sf::Event::KeyPressed) {
			switch (e.key.code) {
			case sf::Keyboard::Down:
				delay = 0.03f;
				break;
			case sf::Keyboard::Up:
				rotate();
				break;
			case sf::Keyboard::Left:
				direction = -1;
				break;
			case sf::Keyboard::Right:
				direction = 1;
				break;
			}
		}
	}
}

void Logic::waiting(){
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void Logic::setElapsedTime(float time) {
	elapsedTime += time;
}

void Logic::check(){
	bool orderly = true;
	orderly = isRegular();
	if (!orderly) {
		for (int i = 0; i < 4; i++)a[i] = b[i];
	}
}

bool  Logic::isRegular() {
	bool orderly = true;
	for (int i = 0; i < 4; i++) {
		if (a[i].x < 0 || a[i].x >= N || a[i].y >= M) orderly = false;
		else if (matrix[a[i].y][a[i].x]) orderly = false;
	}
	return orderly;
}

void Logic::move(){
	for (int i = 0; i < 4; i++) {
		b[i] = a[i];
		a[i].x += direction;
	}
	check();
}

void Logic::rotate(){
	Point p = a[1];
	for (int i = 0; i < 4; i++){
		int x = a[i].y - p.y;
		int y = a[i].x - p.x;
		a[i].x = p.x - x;
		a[i].y = p.y + y;
	}
	check();
}

void Logic::setTetrominos(){
	if (elapsedTime > delay) {
		for (int i = 0; i < 4; i++) {
			b[i] = a[i];
			a[i].y += 1;
		}

		bool isNotGround = true;
		isNotGround = isRegular();

		if (!isNotGround) {
			for (int i = 0; i < 4; i++) {
				matrix[b[i].y][b[i].x] = colorNumber;
			}

			colorNumber = rand() % 7 + 1;
			int n = rand() % 7;
			for (int i = 0; i < 4; i++) {
				a[i].x = tetriminos[n][i] % 2;
				a[i].y = tetriminos[n][i] / 2;
			}
		}
		elapsedTime = 0;
	}
}

int Logic::rowBlasting(){
	int k = M - 1;
	for (int i = k; i > 0; i--) {
		int count = 0;
		for (int j = 0; j < N; j++) {
			if (matrix[i][j]) count++;
			matrix[k][j] = matrix[i][j];
		}
		if (count < N)k--;
		else scores += 10;
	}
	return scores;
}

void Logic::end(sf::Sprite& s,sf::RenderWindow& window) {
	for (int i = 0; i < N; i++) {
		if (matrix[0][i]) {
			window.draw(s);
			window.display();
			waiting();
			window.close();
		}
	}
}
