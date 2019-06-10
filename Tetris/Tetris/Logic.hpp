#ifndef _LOGIC_
#define _LOGIC_

#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>

namespace Tetris{
	const int M = 20;
	const int N = 10;

	class Logic {
		friend class Draw;
	private:
		sf::Event e;
		int direction;
		int colorNumber;
		int scores;
		float elapsedTime;
		float delay;

		int matrix[M][N] = { 0 };

		struct Point {
			int x;
			int y;
		} a[4], b[4];

		int tetrominos[7][8]{	//0-3 x  4-7 y
			{0,0,0,0,0,1,2,3}, //I
			{0,1,0,0,0,0,1,2}, //J
			{0,0,0,1,0,1,2,2}, //L
			{0,1,0,1,0,0,1,1}, //O
			{0,0,1,1,0,1,1,2}, //S
			{1,0,1,0,0,1,1,2}, //Z
			{0,0,1,0,0,1,1,2}  //T
		};


	public:
		Logic();
		~Logic();
		void getEvent(sf::RenderWindow&);
		void move();
		void rotate();
		void fall();
		int rowBlasting();
		bool check();
		void getTetromino();
		void setElapsedTime(float);
		void end(sf::Sprite& s, sf::RenderWindow&);
		inline void waiting() { std::this_thread::sleep_for(std::chrono::milliseconds(1200));};
		inline void  resetParameters() { direction = 0; delay = 0.5; };
	};
}

#endif
