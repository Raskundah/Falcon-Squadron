#pragma once
#include "Screen.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <fstream>


class Game;

class HighScore :
    public Screen
{
public:
    HighScore(Game* newGamePointer);

    void Update(sf::Time frameTime);
    void Draw(sf::RenderTarget& target);
    void loopScore(bool _value);

protected:

private:
    std::string highScoreString, fileReadLine, line;
    int highScoreNumerical;
    std::fstream highScoreFile;
    sf::Sprite background;
    sf::Text highScoreText;
    sf::Font highScoreFont;

    sf::Time waitTime;
    sf::Clock waitClock;


    int currentScore, count, maxHighScores;
    bool didPlayerComplete, hasRun, breakLoop;
    std::vector<int> scoreHolder;
    
};

