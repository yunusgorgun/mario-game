#pragma once
#include "ScoreBoard.h"
#include "Common.h"

ScoreBoard::ScoreBoard(RenderWindow* window){
    //stoi("string");
    lives = 3;
    n = 8;
    score = "000000";
    font.loadFromFile("../assets/Super Mario Bros. 2.ttf");
    text.setFont(font);
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    text.setPosition(sf::Vector2f(Window_WIDTH / 10, 0));
    hcTexture.loadFromFile("../assets/mario1.png");
    hcTexture.setRepeated(true);
    hcSprite.setTexture(hcTexture);
    hcSprite.setPosition(Vector2f(200.f, 40));
};

void ScoreBoard::draw(RenderWindow& window)
{
    zero_length = n - std::min(n, (score.size()));
    score = std::string(zero_length, '0').append(score);
    text.setString(this->score);
    window.draw(text);
    hcSprite.setTextureRect(IntRect(0, 0, 66 * (this->lives), 42));
    window.draw(hcSprite);
}

void ScoreBoard::setScore(int score)
{
    int score_int = stoi(this->score);
    score_int += score;
    this->score = to_string(score_int);
}

void ScoreBoard::setLives(int lives)
{
    this->lives = lives;
}

int ScoreBoard::getLives(void)
{
    return this->lives;
}

void ScoreBoard::getScore()
{
    
    return ;
}