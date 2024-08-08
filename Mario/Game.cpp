#pragma once
#include "Game.h"
//Mert Serbes 040180068
//Yunus Görgün  040180221

void Game::drawBackground(RenderWindow& window) {

    // Load and set up the background floor texture
    bgFloorTexture.loadFromFile("../assets/floor.png");
    bgFloorTexture.setRepeated(true);
    bgFloorSprite.setTexture(bgFloorTexture);
    bgFloorSprite.setTextureRect(IntRect(0, 0, Window_WIDTH, 100));
    bgFloorSprite.setPosition(Vector2f(0.f, Window_HEIGHT - 100));

    // Load and set up the background brick texture
    bgBrickTexture.loadFromFile("../assets/brick.png");
    bgBrickTexture.setRepeated(true);

    // Set the background brick texture for each brick sprite
    for (int i = 0; i < 8; i++) {
        bgBrickSprite[i].setTexture(bgBrickTexture);
    }

    brick_width = bgBrickSprite[7].getTextureRect().width; 
    brick_height = bgBrickSprite[7].getTextureRect().height;

    // Set the texture rectangle and position for each brick sprite
    bgBrickSprite[0].setTextureRect(IntRect(0, 0, 12 * brick_width, brick_height));
    bgBrickSprite[0].setPosition(Vector2f(0.f, Window_HEIGHT - 300));
    bgBrickSprite[1].setTextureRect(IntRect(0, 0, 12 * brick_width, 34));
    bgBrickSprite[1].setPosition(Vector2f(Window_WIDTH - (12 * brick_width), Window_HEIGHT - 300));
    bgBrickSprite[2].setTextureRect(IntRect(0, 0, 5 * brick_width, 34));
    bgBrickSprite[2].setPosition(Vector2f(0.f, Window_HEIGHT - 500));
    bgBrickSprite[3].setTextureRect(IntRect(0, 0, 5 * brick_width, 34));
    bgBrickSprite[3].setPosition(Vector2f(Window_WIDTH - (5 * brick_width), Window_HEIGHT - 500));
    bgBrickSprite[4].setTextureRect(IntRect(0, 0, 15 * brick_width, 34));
    bgBrickSprite[4].setPosition(Vector2f((Window_WIDTH - (16 * brick_width)) / 2, Window_HEIGHT - 560));
    bgBrickSprite[5].setTextureRect(IntRect(0, 0, 14 * brick_width, 34));
    bgBrickSprite[5].setPosition(Vector2f(0.f, Window_HEIGHT - 760));
    bgBrickSprite[6].setTextureRect(IntRect(0, 0, 14 * brick_width, 34));
    bgBrickSprite[6].setPosition(Vector2f(Window_WIDTH - (14 * brick_width), Window_HEIGHT - 760));

    // Load and set up the background pipe texture
    bgPipeTexture.loadFromFile("../assets/pipe.png");

    // Set the position for the pipe sprites
    bgPipeSprite[0].setTexture(bgPipeTexture);
    bgPipeSprite[0].setPosition(Vector2f(Window_WIDTH - 125, Window_HEIGHT - 175));

    bgPipeSprite[1].setTexture(bgPipeTexture);
    bgPipeSprite[1].setScale(-1.f, 1.f);
    bgPipeSprite[1].setPosition(Vector2f(125, Window_HEIGHT - 175));
    bgSPipeTexture.loadFromFile("../assets/pipeS.png");
    bgSPipeSprite[0].setTexture(bgSPipeTexture);
    bgSPipeSprite[0].setScale(-1.f, 1.f);
    bgSPipeSprite[0].setPosition(Vector2f(Window_WIDTH, 25));

    bgSPipeSprite[1].setTexture(bgSPipeTexture);
    bgSPipeSprite[1].setPosition(Vector2f(0, 25));

    // Draw the background floor sprite
    window.draw(bgFloorSprite);

    // Draw each brick sprite
    for (int i = 0; i < 7; i++) {
        window.draw(bgBrickSprite[i]);
    }

    // Draw the pipe sprites
    window.draw(bgPipeSprite[0]);
    window.draw(bgPipeSprite[1]);

    // Draw the small pipe sprites
    window.draw(bgSPipeSprite[0]);
    window.draw(bgSPipeSprite[1]);
}

Game::Game()
{
    // Create the game window
    window = new RenderWindow(VideoMode(Window_WIDTH, Window_HEIGHT), "Mario");

    // Set up the initial turtle count
    turtle_sayý = 0;
    died_turtle = 0;
    // Load and set up  the start menu background image
    Texture backgroundTexture;
    backgroundTexture.loadFromFile("../assets/mariostart.jpg");
    Sprite background(backgroundTexture);
    background.setPosition(sf::Vector2f(0, (Window_HEIGHT / 4)));

    // Load the font for text rendering
    sf::Font font;
    font.loadFromFile("../assets/font.ttf");

    // Set up the title text
    sf::Text title("Welcome to Mario Game!", font, 48);
    title.setFillColor(sf::Color::Red);
    title.setPosition(sf::Vector2f(120, 100));

    // Set up the start button text
    sf::Text startButton("New Game", font, 48);
    startButton.setFillColor(sf::Color::Red);
    startButton.setPosition(sf::Vector2f(350, 800));
    startButton.setStyle(sf::Text::Bold);

    // Set up the game over text
    Text gameOver("GAME OVER!", font, 120);
    gameOver.setFillColor(Color::Red);
    gameOver.setPosition(Vector2f(100, Window_HEIGHT / 2));
    gameOver.setStyle(Text::Bold);
    
    Text winMessage("You Win!", font, 120);
    winMessage.setFillColor(sf::Color::Green); // Green color is often associated with success
    winMessage.setPosition(sf::Vector2f(200, Window_HEIGHT / 2)); // Position at the center of the window
    winMessage.setStyle(sf::Text::Bold | sf::Text::Underlined); // Make the text bold and underlined
    // Create and position the Mario character
    Mario* mario = addMario();
    mario->setPosition(Vector2f(700.f, 900.f));

    // Set the game start flag to false
    bool gamestart = false;


    while (window->isOpen())
    {
        if (!gamestart) {
            window->clear();
            window->draw(background);
            window->draw(title);
            window->draw(startButton);
            window->display();

        }
        if (gamestart) {
            // Clear the window
            window->clear();

            // Draw game objects and background
            drawObject(*window);
            drawBackground(*window);

            // Draw the scoreboard
            scoreBoard->draw(*window);

            // Pause for 20 milliseconds
            sleep(milliseconds(20));

            // Display the window
            window->display();

            // Call the gameStarted() function (assuming it contains game logic)
            gameStarted();

           



        if (scoreBoard->getLives() == 0|| died_turtle==5) {
            // Remove all turtles from the game
            Object* cur = objects;
            Object* next = nullptr;

            while (cur) {
                next = cur->next;

                if (dynamic_cast<Turtle*>(cur) != nullptr) {
                    removeObject(cur);                               //delete turtles
                }

                cur = next;
            }

            // Reset turtle count and Mario's position
            turtle_sayý = 0;
            mario->setPosition(Vector2f(700.f, 900.f));
            mario->heading = 0;

            window->clear();
            if(scoreBoard->getLives() == 0)
            window->draw(gameOver);
            
            else if(died_turtle == 5)
            window->draw(winMessage);
            
            window->display();
            sleep(milliseconds(3000));
            scoreBoard->setLives(3);
            scoreBoard->setScore(-(died_turtle * 100));
            died_turtle = 0;
            gamestart = false;


        }


       

       
        
        Object* cur = objects;

            while (cur) {

                if (onFloor(cur)) {
                    
                    cur->move();

                    // Check for turtle collisions
                    checkTurtle();

                }
                cur = cur->next;
            }
        }
        


        sf::Event event;
        while (window->pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window->close(); // Close the window when the close button is pressed
                break;
            case Event::MouseButtonPressed: {
                sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
                if (startButton.getGlobalBounds().contains(mousePos))
                {
                    gamestart = true; // Start the game when the start button is clicked
                    Turtle* turtle = addTurtle(); // Add a first Turtle object and clock start for other turtles
                    turtle_sayý += 1;
                }
            }
                                          break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Left && onFloor(mario)) {
                    mario->heading = 1; // Set Mario's direction to left when the left arrow key is pressed


                }
                else if (event.key.code == sf::Keyboard::Right && onFloor(mario)) {
                    mario->heading = -1; // Set Mario's direction to right when the right arrow key is pressed


                }
                else if (event.key.code == sf::Keyboard::Up && onFloor(mario) && !mario->died) {
                    mario->jump(false); // Make Mario jump when the up arrow key is pressed
                    mario->setOrigin(Vector2f(float(mario->boundingBox().width / 2), 0.0f));
                    mario->setPosition((Vector2f(float(mario->getPosition().x), float(mario->getPosition().y - (mario->boundingBox().height)))));   // Set the origin to the top for collision with the upper obstacle
                    mario->jumpStart = true;

                }
                break;
            case sf::Event::KeyReleased:
                if ((event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right) && onFloor(mario))
                {
                    mario->heading = 2; //use heading 2 for Reset Mario's direction to stop when the left or right arrow key is released

                }
                break;
            default:
                break;
            }
        }



        if (!onFloor(mario)) {
            mario->jump(true); // Make Mario start jumping if not on the floor

            if (onFloor(mario)) {

                if (mario->up()) {
                    mario->reverse_vy(); // Reverse the vertical velocity if Mario hits a brick
                    mario->jump(true);
                }
                else if (!(mario->up())) {
                    // Mario down
                    mario->jumpStart = false; // Set the jump start flag to false
                    mario->heading = 2; // Set Mario's direction to stop for bonus
                    mario->move(); // Move Mario

                   

                }
            }

            if (!(mario->up()) && mario->jumpStart) {
                // Mario starts falling and resets its origin to the normal position
                mario->setOrigin(Vector2f(float(mario->boundingBox().width / 2), float(mario->boundingBox().height)));
                mario->setPosition((Vector2f(float(mario->getPosition().x), float(mario->getPosition().y + (mario->boundingBox().height))))); // Reset the origin to its normal position
                mario->jumpStart = false; // Reset the jump start flag
            }
        }


        Object* cur = objects;   // Start with the first object in a linked list of game objects
        Object* other;
        int side;

        while (cur) {   // Loop through each object in the list
            // Check if current object is of Turtle type
            if (dynamic_cast<Turtle*>(cur) != NULL) {
                other = objects; 
                turtle = static_cast<Turtle*>(cur);  // Cast the current object to Turtle

                // Check if the turtle is not on the floor
                if (!onFloor(cur)) {
                    cur->jump(true);  // Make the turtle down
                    // If turtle lands on the floor after down
                    if (onFloor(cur)) {
                        cur->move();  // Move the turtle
                    }
                }

                while (other) {  // Loop through each other object

                    // Check if 'other' object is of Mario type
                    if (dynamic_cast<Mario*>(other) != NULL) {
                        mario = static_cast<Mario*>(other);  // Cast the 'other' object to Mario

                        // Check for collision between turtle and mario
                        if (checkCollusion(turtle, mario, side)) {
                            // If Mario hits the turtle
                            if (side == 0) {
                                
                                if (!(cur->died))
                                    scoreBoard->setLives((scoreBoard->getLives() - 1));  // Decrease lives by 1
                                other->heading = 0;  // Set Mario's heading direction to 0, indicating Mario is killed
                            }
                            // If Mario hits the turtle from above
                            else if (side == 1) {
                                
                                if (!(cur->died)) {
                                    scoreBoard->setScore(100);  // Increase score by 100
                                    died_turtle += 1;
                                }
                                   
                                cur->heading = 0;  // Set the turtle's heading to 0, indicating turtle is crushed
                            }
                            // If Mario hits the turtle from below
                            else if (side == 2) {
                                // If the turtle is on the floor
                                if (onFloor(cur)) {
                                   
                                        cur->heading = 3;  // Set turtle's heading direction to reverse 
                                }
                            }
                        }
                    }
                    other = other->next;  // Move to the next 'other' object
                }
            }
            cur = cur->next;  // Move to the next object in the list
        }
    }
}


    bool Game::onFloor(Object* obj) {

        if (!(obj->died)) {  //obj does not get caught in obstacles when obj dies

            if (obj->getPosition().y >= Window_HEIGHT - 100) {
                obj->setPosition(Vector2f(float(obj->getPosition().x), float(Window_HEIGHT - 100)));   //We set a certain range because it would not coincide exactly.
                return true;
            }
            else if ((Window_HEIGHT - 320 < obj->getPosition().y && obj->getPosition().y < Window_HEIGHT - 280) && ((obj->getPosition().x <= 12 * brick_width) || (obj->getPosition().x >= Window_WIDTH - (12 * brick_width)))) {
                obj->setPosition(Vector2f(float(obj->getPosition().x), float(Window_HEIGHT - 300)));
                return true;
            }
            else if ((Window_HEIGHT - 520 < obj->getPosition().y && obj->getPosition().y < Window_HEIGHT - 480) && ((obj->getPosition().x <= 5 * brick_width) || (obj->getPosition().x >= Window_WIDTH - (5 * brick_width)))) {
                obj->setPosition(Vector2f(float(obj->getPosition().x), float(Window_HEIGHT - 500)));
                return true;
            }
            else if ((Window_HEIGHT - 580 < obj->getPosition().y && obj->getPosition().y < Window_HEIGHT - 540) && ((obj->getPosition().x <= (Window_WIDTH + (16 * brick_width)) / 2) && (obj->getPosition().x >= (Window_WIDTH - (16 * brick_width)) / 2)))
            {
                obj->setPosition(Vector2f(float(obj->getPosition().x), float(Window_HEIGHT - 560)));
                return true;
            }
            else if ((Window_HEIGHT - 780 < obj->getPosition().y && obj->getPosition().y < Window_HEIGHT - 740) && ((obj->getPosition().x <= 14 * brick_width) || (obj->getPosition().x >= Window_WIDTH - (14*brick_width))))
            {
                obj->setPosition(Vector2f(float(obj->getPosition().x), float(Window_HEIGHT - 760)));
                return true;
            }
            else {
                return false;
            }
        }

    }

    bool Game::checkCollusion(Turtle* t, Mario* m, int& side) {

        // calculate half widths
        float tHalfWidth = t->boundingBox().width / 2;
        float mHalfWidth = m->boundingBox().width / 2;

        // check horizontal collision
        bool isHorizontalCollision = t->getPosition().x - tHalfWidth <= m->getPosition().x + mHalfWidth
            && t->getPosition().x + tHalfWidth >= m->getPosition().x - mHalfWidth;

        // check each case separately
        if (isHorizontalCollision && t->getPosition().y == m->getPosition().y) {
            side = 0; // mario dies
            return true;
        }
        else if (isHorizontalCollision && !m->up() && t->getPosition().y - t->boundingBox().height <= m->getPosition().y && t->getPosition().y > m->getPosition().y) {
            side = 1; // turtle dies
            return true;
        }
        else if (isHorizontalCollision && m->up() && t->getPosition().y + brick_height + 10 >= m->getPosition().y && t->getPosition().y < m->getPosition().y) {
            side = 2; // bonus points
            return true;
        }

        // no collision detected
        return false;
    }



Turtle* Game::addTurtle() {
    Turtle* turtle = new Turtle(window);
    turtle->next = objects;
    objects = turtle;
    return turtle;
   
}


Mario* Game::addMario() {
   
    
        Mario* mario = new Mario(window);
        mario->next = objects;
        objects = mario;
        return mario;
    
}


void Game::removeObject(Object* obj) {

    Object* cur = objects;
    Object* prev = NULL;
    while (cur)
    {
        if (cur == obj)
        {

            if (prev) {
                prev->next = cur->next;
            }

            else {
                objects = cur->next;
            }
            delete cur;
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}


void Game::gameStarted()
{
    
    Object* cur = objects;

    
    Time elapsed = cur->clock.getElapsedTime();

    // Convert the elapsed time to seconds
    int elapsedSeconds = elapsed.asSeconds();

    // Every 10 seconds and if the number of turtles is less than 5
    if ((elapsedSeconds == 10 && turtle_sayý < 5)) {
        // Create a new turtle
        Turtle* turtle = addTurtle();

        // Increment the number of turtles
        turtle_sayý += 1;
    }
}

        

void Game::drawObject(RenderWindow& window) {


    Object* cur = objects;

    while (cur) {

        cur->draw(window);
        cur = cur->next;

    }




}

void Game::checkTurtle() {
    // Get the head of the object list
    Object* cur = objects;
    Object* other;

    // Traverse the object list
    while (cur) {
        // Check if the current object is a Turtle
        if (dynamic_cast<Turtle*>(cur) != NULL) {

            // For each Turtle, check all other objects
            other = objects;
            while (other) {
                // Ensure the other object is a Turtle and it's not the same as the current one
                if ((dynamic_cast<Turtle*>(other) != NULL) && (cur != other)) {

                    // Check if the two turtles' sprites are intersecting
                    if (other->sprite.getGlobalBounds().intersects(cur->sprite.getGlobalBounds())) {

                        // If the turtles are heading towards each other
                        if (((cur->getPosition().x > (other->getPosition().x)) && (cur->heading == -1)) ||
                            ((other->getPosition().x > (cur->getPosition().x)) && (other->heading == -1))) {

                            // Set both turtles to have collided with each other
                            other->collusionTurtle = true;
                            cur->collusionTurtle = true;
                        }
                    }
                }

                // Move to the next object in the list
                other = other->next;
            }
        }

        // Move to the next object in the list
        cur = cur->next;
    }
}

