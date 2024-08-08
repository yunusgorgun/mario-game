#pragma once
#include "Mario.h"
#include "Common.h"


Mario::Mario(RenderWindow* window):Object(window) {

	for (int i = 0; i < 7; i++) {
		std::string filename = "../assets/mario" + to_string(i + 1) + ".png";
		textures[i].loadFromFile(filename);
	}
	
	sprite.setTexture(textures[0]);
    //Set the sprite's origin to its center bottom
	sprite.setOrigin(Vector2f(float(boundingBox().width / 2), float(boundingBox().height)));
	vx = 0;
	vy = 0;
	jumpStart=false;
	state = 0;
    heading = 5;
    setPosition(Vector2f(700.f, 860.f));
};

void Mario::move()  {
   
    //Switch statement to check the current state of Mario

    switch (state) {
    case 0: {
        if (heading == 1) {    //Mario moving left
            vx = -10;
            vy = 0;
            sprite.setScale(1.f, 1.f);
            sprite.move(Vector2f(float(vx), 0.f));
            state = 1;
        }
        else if (heading == -1) {  //Mario moving right
            vx = 10;
            vy = 0;
            sprite.setScale(-1.f, 1.f);
            sprite.move(Vector2f(float(vx), 0.f));
            state = 1;
        }
        else if (heading == 2) {
            state = 4;
            heading = 5;  //assigning an arbitrary heading value so that it does not enter again when it stops.
        }
        else if (heading == 0) {
            state = 6;  //died
            move();  // if mario died go state=6 in this loop
          
        }
    }
    break;

    case 1: {
        if (heading == 1) {
            vx = -10;
            sprite.setScale(1.f, 1.f);
            sprite.move(Vector2f(float(vx), 0.f));
            state = 2;
        }
        else if (heading == -1) {
            vx = 10;
            sprite.setScale(-1.f, 1.f);
            sprite.move(Vector2f(float(vx), 0.f));
            sprite.setScale(-1.f, 1.f);
            state = 2;
        }
        else if (heading == 2) {
            state = 4;
            heading = 5;
        }
        else if (heading == 0) {
            state = 6;
            move();

        }
        else {
            state = 0;
            vx = 0;
        }
    }
    break;

    case 2: {
        if (heading == 1) {
            vx = -10;
            sprite.setScale(1.f, 1.f);
            sprite.move(Vector2f(float(vx), 0.f));
            state = 3;
        }
        else if (heading == -1) {
            vx = 10;
            sprite.setScale(-1.f, 1.f);
            sprite.move(Vector2f(float(vx), 0.f));
            sprite.setScale(-1.f, 1.f);
            state = 3;
        }
        else if (heading == 2) {
            state = 4;
            heading = 5;
        }
        else if (heading == 0) {
            state = 6;
            move();

        }
        else {
            state = 0;
            vx = 0;
        }
    }
    break;

    case 3: {
        if (heading == 1) {
            vx = -10;
            sprite.setScale(1.f, 1.f);
            sprite.move(Vector2f(float(vx), 0.f));
            state = 1;
        }
        else if (heading == -1) {
            vx = 10;
            sprite.setScale(-1.f, 1.f);
            sprite.move(Vector2f(float(vx), 0.f));
            sprite.setScale(-1.f, 1.f);
            state = 1;
        }
        else if (heading == 2) {
            state = 4;
            heading = 5;
        }
        else if (heading == 0) {
            state = 6;
            move();

        }
        else {
            state = 0;
            vx = 0;
        }
    }
          break;

    case 4: {
        static int i = 0;
       if(i<5){
       
           i++;           //to stay in this position more time
       
       
       }
       else if (heading == 0) {
           state = 6;
           move();
       }
       else {
           state = 0;
           vx = 0;
            i = 0;
       }
    }
    break;
    case 6: {
        

            state = 6;
            fall();
            died = true;                                  //died
            if (getPosition().y > Window_HEIGHT ) {
                setPosition(Vector2f(540.f,580.f));
                state = 0;
                heading = 5; //assigning an arbitrary heading value
                died = false;
            }
        }
    
          break;
    }
    check_wall(); // Check if Mario hits the wall
    sprite.setTexture(textures[state]);
    
}



void Mario::jump(bool down)
{   
    if (down) {
        //As long as vertical speed is less than 20, keep moving Mario downwards
        if ((this->vy <20)) {
            setPosition(Vector2f(getPosition().x+vx, getPosition().y + vy));
            this->vy += 1;
            sprite.setTexture(textures[5]);
            
        }
        else if ((this->vy == 20)) {
             setPosition(Vector2f(getPosition().x+vx, getPosition().y + vy));
            sprite.setTexture(textures[5]);
           

        }
    }
    //If Mario is not going down, he must be going up (upwards part of the jump)

	if (!down) {
        this->vy = -20;
        setPosition(Vector2f(getPosition().x + vx, getPosition().y + vy));
		sprite.setTexture(textures[5]);
	}
}

void Mario::reverse_vy() {


   this->vy =20;
}

bool Mario::up() {

    if (this->vy < 0) {
        return true;

    }
    else
        return false;
    

}

void Mario::check_wall() {    //function prevents the Mario character from going beyond the left or right edges of the screen.

    if (getPosition().x >= (Window_WIDTH)-(sprite.getTextureRect().width) / 2)
    {

        setPosition(Vector2f(((Window_WIDTH)-(sprite.getTextureRect().width) / 2), getPosition().y));

    } 
    else if (getPosition().x <= (sprite.getTextureRect().width / 2)) {

        setPosition(Vector2f(((sprite.getTextureRect().width) / 2), getPosition().y));

    }
}

void Mario::fall(void) {


    vx = 0;          //when died
    vy = 2;
    sprite.move(Vector2f(0.f, float(vy)));




}
