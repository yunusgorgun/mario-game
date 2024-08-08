#pragma once
#include "Object.h"
#include "Common.h"


class Turtle : public Object {
	
	bool jumpExecuted;
	Clock clock2;
	Clock clock3;
	float vx; //Horizontal speed 
	float vy; //Vertical speed 
	float s;
	
public:
	
	void check_wall()override;
	
	Turtle(RenderWindow* window); //Constructor 
	void move () override; //Moves Mario left or right 
	void jump(bool down)override; //Makes Mario jump (if down is true, Mario jumps down off the edge of a floor, otherwise he jumps	up)
	void fall(void)override; //Makes Mario fall straight down when he dies 
	/*void check_wall(void);*/
	void speed_up_vx(void);
};


