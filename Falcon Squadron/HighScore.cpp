#include "HighScore.h"
#include "AssetManager.h"
#include "Game.h"
#include "Player.h"

HighScore::HighScore(Game* newGamePointer)
	: Screen(newGamePointer)
	, highScoreFile("Assets/HighScores/hi_score.txt")
	, currentScore(newGamePointer->GetPlayerScore())
	, didPlayerComplete(newGamePointer->GetPlayerAlive())
{
	highScoreFont = AssetManager::RequestFont("Assets/cool.otf");

	std::string highScoreString = ("Here we've reached the end of the simulation. \n");



	highScoreText.setString(highScoreString);
	highScoreText.setFillColor(sf::Color::White);
	highScoreText.setOutlineThickness(2.0f);
	highScoreText.setOutlineColor(sf::Color::Black);
	highScoreText.setCharacterSize(30);
	highScoreText.setPosition((newGamePointer->GetWindow()->getSize().x - highScoreText.getGlobalBounds().width) * 0.1f, newGamePointer->GetWindow()->getSize().y / 2);
	highScoreText.setFont(highScoreFont);

	background.setTexture(AssetManager::RequestTexture("Assets/background2.png"));
	background.setScale(newGamePointer->GetWindow()->getSize().x / background.getGlobalBounds().width, newGamePointer->GetWindow()->getSize().y / background.getGlobalBounds().height);

}

void HighScore::Update(sf::Time frameTime)
{
	

}

void HighScore::Draw(sf::RenderTarget& target)
{
	target.draw(background);
	
}
