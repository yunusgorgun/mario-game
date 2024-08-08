#pragma once
#include "Common.h"



class ScoreBoard {
	
	RenderWindow* window;
	

protected:
	string score; //stoi("string");
	int num ;
	int lives;
	sf::Font font;
	sf::Text text;
	size_t n;
	int zero_length;
	Texture hcTexture;// Headcount Texture
	Sprite hcSprite;
	
public:
	ScoreBoard(RenderWindow* window);
	void setScore(int score);
	void getScore();
	void setLives(int lives);
	int getLives(void);
	void draw(RenderWindow& window);
};
