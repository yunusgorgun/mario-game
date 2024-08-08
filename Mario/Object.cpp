#pragma once
#include "Object.h"

void Object::setPosition(Vector2f pos)
{
    // Set the position of the object
    this->pos = pos;
    sprite.setPosition(pos);
};

void Object::draw(RenderWindow& window)
{
    // Draw the sprite on the specified window
    window.draw(sprite);
};

Object::Object(RenderWindow* window)
{
    // Initialize object properties
    collusionTurtle = false;
    state = 0;
    heading = 1;
    died = false;
    next = NULL;
};

IntRect Object::boundingBox(void) {
    // Return the bounding box of the sprite
    return sprite.getTextureRect();
}

Vector2f Object::getPosition(void) {
    // Get the current position of the object
    return sprite.getPosition();
}

void Object::setOrigin(Vector2f origin) {
    // Set the origin of the object
    this->origin = origin;
    sprite.setOrigin(origin);
}
