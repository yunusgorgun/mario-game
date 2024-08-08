#pragma once
#include "Turtle.h"
#include "Common.h"



Turtle::Turtle(RenderWindow* window) :Object(window) {
	// Load turtle textures for different turtle animations
	for (int i = 0; i < 5; i++) {
		std::string filename = "../assets/turtle" + to_string(i + 1) + ".png";
		textures[i].loadFromFile(filename);
	}
	int randomValue = (rand() % 2 == 0) ? -1 : 1;         // Set initial position and heading of the turtle, randomly to the left or the right
	if (randomValue == -1) {                             
		setPosition(Vector2f(200, Window_HEIGHT - 860));
		
		heading =1;
	}
	if (randomValue ==1) {
		setPosition(Vector2f(Window_WIDTH-200, Window_HEIGHT - 860));

		heading =-1;
	}

	// Set the origin of the sprite to be at its center horizontally and at its bottom vertically
	sprite.setTexture(textures[0]);
	sprite.setOrigin(Vector2f(float(boundingBox().width / 2), float(boundingBox().height)));
	vx = 0;
	vy = 0;
	s = 0;
	
	jumpExecuted = false;
	




};


void Turtle::move() {
	

	switch (state)
	{

	case 0:
		if (collusionTurtle) {
			state = 3;
			clock3.restart();
		}
		
		else if (heading == 1) {
			speed_up_vx();
			vy = 0;
			sprite.setScale(1.f, 1.f);                 //moving right
			sprite.move(Vector2f(float(vx), 0.f));
			state = 1;
		}
		else if (heading == -1)
		{
			speed_up_vx();
			vy = 0;                              // moving left
			sprite.setScale(-1.f, 1.f);
			sprite.move(Vector2f(float(vx), 0.f));
			state = 1;
		}
		
		else if (heading == 0 || heading == 3) { //died or bonus3
			state = 4;
			move(); // if turtle died go state=4 in this loop
		}
		
		

	break;

	case 1:
		
		if (collusionTurtle) {
			state = 3;
			clock3.restart();
		}
		
		if (heading == 1) {
			speed_up_vx();
			vy = 0;
			sprite.setScale(1.f, 1.f);
			sprite.move(Vector2f(float(vx), 0.f));
			state = 2;
		}
		else if (heading == -1)
		{
			speed_up_vx();
			vy = 0;
			sprite.setScale(-1.f, 1.f);
			sprite.move(Vector2f(float(vx), 0.f));
			state = 2;
		}
		
		else if (heading == 0 || heading == 3) {
			state = 4;
			move();
		}

		
		break;
	case 2:
		
		if (collusionTurtle) {
			state = 3;
			clock3.restart();
		}
		
		if (heading == 1) {
			speed_up_vx();
			vy = 0;
			sprite.setScale(1.f, 1.f);
			sprite.move(Vector2f(float(vx), 0.f));
			state = 0;
		}
		else if (heading == -1)
		{
			speed_up_vx();
			vy = 0;
			sprite.setScale(-1.f, 1.f);
			sprite.move(Vector2f(float(vx), 0.f));
			state = 0;
		}
		else if (heading == 0 || heading == 3) {
			state = 4;
			move();
		}
		
		break;
	

	case 3: {


		Time elapsed3 = clock3.getElapsedTime();
		int elapsed3Seconds = elapsed3.asSeconds();

		if (elapsed3Seconds == 1) {
			
			heading = -(heading);                        //bonus2
			vx = -(vx);
			sprite.move(Vector2f(float(5*vx), 0.f));
			state = 0;
			collusionTurtle = false;

			
		}
		else if (heading == 0 || heading == 3) {
			state = 4;
			move();
		}
		
		
	}
	case 4:
		
	     
		if (heading == 3) { 
			
			
			if (!jumpExecuted) { // for execute one time
				jump(false);
				clock2.restart();
				jumpExecuted = true; 
				
			}
			Time elapsed2 = clock2.getElapsedTime();       
			int elapsed2Seconds = elapsed2.asSeconds();         //bonus3
			  

			if (elapsed2Seconds == 8) {
				                                
				heading = 1;
				state = 0;				
				jumpExecuted = false;
				
			}
			
		}

		

		if (heading == 0) {
			
			state = 4;
			fall();   //died
			died = true;
		}
		

	default:
		break;
	}
	check_wall();
	sprite.setTexture(textures[state]);
}


void Turtle::jump(bool down)
{
	if (down) {
		if (this->vy < 20) {
			this->vy += 5;
		}
		                          //move down

		sprite.move(0, float(vy));
		
	}
	else {                       //jump
		vy = -40;
		sprite.move(vx, float(vy)); 
		
	}
}



void Turtle::check_wall(void)
{
	if (heading == 1)                                                                    //function prevents the Mario character from going beyond the left or right edges of the screen.
	{                                                                                    //and when turtles reached bottom edge teleport Spipes randomly
		if (getPosition().x >= (Window_WIDTH) - (sprite.getTextureRect().width) / 2)
		{
			if (getPosition().y == (Window_HEIGHT - 100))
			{
				int random_number = (std::rand() % 2);
					if (random_number == 0) {
						setPosition(Vector2f(194, Window_HEIGHT - 900));
						heading = 1;
					}
					else if (random_number == 1) {

						setPosition(Vector2f(Window_WIDTH-194, Window_HEIGHT - 900));

					}
			}
			else
				heading = -1;
			vx = -vx;

		}

	}
	else if (heading == -1) {

			if (getPosition().x <=(sprite.getTextureRect().width/2))
			{
				if (getPosition().y == (Window_HEIGHT - 100))
				{
					int random_number = (rand() % 2);
					if (random_number == 0) {
						setPosition(Vector2f(194, Window_HEIGHT - 900));
						heading = 1;
					}
					else if (random_number == 1) {

						setPosition(Vector2f(Window_WIDTH - 194, Window_HEIGHT - 900));

					}
				}
				else
				heading = 1;
				vx = -vx;

			}

	}
		
}

void Turtle::fall(void) {


	vx = 0;                      //died
	vy = 20;
	sprite.move(Vector2f(0.f, float(vy)));
}

void Turtle::speed_up_vx(void)
{
	if (heading == 1)
	{
		vx = 4 + (s * 0.005);       // speed up turtles
	}

	else if (heading == -1)
	{
		vx = -4 - (s * 0.005);
	}
	s++;
}

