#pragma once
#include "Object.h"
#include "Common.h"


class Mario: public Object {
	float vx; //Horizontal speed 
	float vy; //Vertical speed 
	
    
public:
	bool jumpStart;
	void check_wall();
	Mario(RenderWindow* window); //Constructor 
	void move()override; //Moves Mario left or right 
	void jump(bool down)override; //Makes Mario jump (if down is true, Mario jumps down off the edge of a floor, otherwise he jumps	up)
	void fall(void)override; //Makes Mario fall straight down when he dies 
	void reverse_vy();
	bool up();
	/*void check_wall(void);*/
};
