#pragma once
#include "Common.h"



class Object {

	
	RenderWindow* window; //Pointer to render window 
	Object* next;
	
	friend class Game;


protected:
	//Sprite sprite; //Sprite for the object 
	Texture textures[8];
	int state; //Current animation state of the object (one of animation states)
	Vector2f pos;
	Sprite sprite;
	Clock clock;
	Vector2f origin;
	bool died;
public:
	
	bool collusionTurtle;
	void setOrigin(Vector2f origin);
	virtual void check_wall()=0;
	int heading; //Facing direction of object 
	Object(RenderWindow* window); //Constructor 
	void setPosition(Vector2f pos); //Sets position of the object 
	Vector2f getPosition(); //Gets position of the object 
	IntRect boundingBox(void); //Returns the bounding rectangle of the object texture 
	void draw(RenderWindow& window);//Draws current the object texture to screen 
	virtual void move(void) = 0; //Abstract method that will be overridden 
	virtual void fall(void)=0; //Abstract method that will be overridden 
	virtual void jump(bool down)=0; //Abstract method that will be overridden 
	
	



	Object() {

		next = NULL;
	}

};
