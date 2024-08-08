#pragma once
#include "Common.h"
#include "Mario.h"
#include "Turtle.h"
#include "scoreBoard.h"

class Game
{
	
	RenderWindow *window;

	Texture bgFloorTexture;
	Sprite bgFloorSprite;

	Texture bgBrickTexture;
	Sprite bgBrickSprite[8]; // bir tanesi boyutunu almak için

	Texture bgPipeTexture;
	Sprite bgPipeSprite[2];
	
	Texture bgSPipeTexture;
	Sprite bgSPipeSprite[2];
	
	Mario* mario;
	Turtle* turtle;
	Object* objects;
	ScoreBoard* scoreBoard = new ScoreBoard(window);
	int turtle_sayý;
	int died_turtle;
public:
	float brick_width;
	float brick_height;
	
	Game();
	void drawObject(RenderWindow& window);
	void drawBackground(RenderWindow& window);//Draws the background objects 
	bool onFloor(Object* obj); //Checks if object is touching a floor surface
	bool checkCollusion(Turtle* t, Mario* m, int& side);
	void checkTurtle();
	void removeObject(Object*);
	void gameStarted();
	Turtle* addTurtle(void);
	Mario* addMario(void);
};
