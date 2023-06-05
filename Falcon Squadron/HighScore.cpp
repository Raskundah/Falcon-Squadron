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
	int lineCount = 0;
	while (std::getline(highScoreFile, fileReadLine)) // the player survived and scored a new top score
	{

		if (currentScore > stoi(fileReadLine) && didPlayerComplete && lineCount == 0)
		{
			currentScore += 5000;
			highScoreString += "You Survived and reached a new high score! Bonus of 5000 granted.";
			fileReadLine = std::to_string(currentScore);
			break;
		}


		else if (currentScore > stoi(fileReadLine) && didPlayerComplete && lineCount == 1)
		{
			currentScore += 4000;
			highScoreString += " You Survived and reached second place. Bonus of 4000 granted.";
			fileReadLine = std::to_string(currentScore);
		}


		else if (currentScore > stoi(fileReadLine) && didPlayerComplete && lineCount == 2)
		{
			currentScore += 3000;
			highScoreString += "You Survived and came third! Bonus of 3000 granted. \n";
			fileReadLine = std::to_string(currentScore);
		}

	}
	


}

void HighScore::Draw(sf::RenderTarget& target)
{
	target.draw(background);
	
}
