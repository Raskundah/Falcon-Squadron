#include "HighScore.h"
#include "AssetManager.h"
#include "Game.h"
#include "Player.h"
#include <Windows.h>

HighScore::HighScore(Game* newGamePointer)
	: Screen(newGamePointer)
	, highScoreFile("Assets/HighScores/hi_score.txt")
	, currentScore(newGamePointer->GetPlayerScore())
	, didPlayerComplete(newGamePointer->GetPlayerAlive())
	, count()
	, maxHighScores(10)
	, waitTime(sf::seconds(5.0f))
	
{
	highScoreFont = AssetManager::RequestFont("Assets/cool.otf");

	std::string highScoreString = ("Here we've reached the end of the simulation. \nIf you're reading this, the high scores are broken. \nPress S to go back to main menu.\n");

	highScoreText.setString(highScoreString);
	highScoreText.setFillColor(sf::Color::White);
	highScoreText.setOutlineThickness(2.0f);
	highScoreText.setOutlineColor(sf::Color::Black);
	highScoreText.setCharacterSize(30);
	highScoreText.setPosition((newGamePointer->GetWindow()->getSize().x - highScoreText.getGlobalBounds().width)* 0.1f, newGamePointer->GetWindow()->getSize().y / 2);
	highScoreText.setFont(highScoreFont);

	background.setTexture(AssetManager::RequestTexture("Assets/background2.png"));
	background.setScale(newGamePointer->GetWindow()->getSize().x / background.getGlobalBounds().width, newGamePointer->GetWindow()->getSize().y / background.getGlobalBounds().height);

}

void HighScore::Update(sf::Time frameTime)

#pragma region hell


{
	
	currentScore = gamePointer->GetPlayerScore();
	didPlayerComplete = gamePointer->GetPlayerAlive();
	waitClock.restart();
	/*
	if (!hasRun)
	{

		if (highScoreFile.is_open())
		{
			highScoreString.clear();

			while (highScoreFile.peek() != EOF)
			{
				std::getline(highScoreFile, fileReadLine);
				count++;
			}
		}
		int lineCount = 0;
		for (lineCount = 0; lineCount < count; ++lineCount)
		{

			//while (std::getline(highScoreFile, fileReadLine)) // the player survived and scored a new top score
			//{

			if (currentScore > stoi(fileReadLine) && didPlayerComplete && lineCount == 0)
			{
				currentScore += 5000;
				highScoreString += "You Survived and reached a new high score! Bonus of 5000 granted. \n";
				fileReadLine = std::to_string(currentScore);
				break;
			}


			else if (currentScore > stoi(fileReadLine) && didPlayerComplete && lineCount == 1)
			{
				currentScore += 4000;
				highScoreString += " You Survived and reached second place. Bonus of 4000 granted. \n";
				fileReadLine = std::to_string(currentScore);
				break;
			}



			else if (currentScore > stoi(fileReadLine) && didPlayerComplete && lineCount == 2)
			{
				currentScore += 3000;
				highScoreString += "You Survived and came third! Bonus of 3000 granted. \n";
				fileReadLine = std::to_string(currentScore);

				break;
			}

			else if (!didPlayerComplete && currentScore > stoi(fileReadLine) && lineCount == 0)
			{
				highScoreString += "You died, but still took the high score! \n";
				fileReadLine = std::to_string(currentScore);

				break;
			}

			else if (!didPlayerComplete && currentScore > stoi(fileReadLine) && lineCount == 1)
			{
				highScoreString += "You died, but still took Second Place! \n";
				fileReadLine = std::to_string(currentScore);

				break;


			}
			else if (!didPlayerComplete && currentScore > stoi(fileReadLine) && lineCount == 2)
			{
				highScoreString += "You died, but still took third place. \n";
				fileReadLine = std::to_string(currentScore);

				break;
			}
			else
				highScoreString += "You didn't make it to the high score, but don't worry! This is tough. \n";


		}

		highScoreString += "The current high scores are: ";


		while (std::getline(highScoreFile, fileReadLine))
		{
			highScoreString += " " + fileReadLine + ", ";
		}

		highScoreFile.close();


		highScoreString += "\n Press Y to exit.";
		highScoreText.setString(highScoreString);

		hasRun = true;
	}

	*/

#pragma endregion

	for (int i = 0; i < scoreHolder.size(); ++i) // here we loop through the current session's high scores.
	{
		bool found = false;

		if (currentScore > scoreHolder[i]) //checks if the recent score is greater than the current entry in the score holder for the session.
		{
			if (i == 0 && didPlayerComplete) // bonus for finishing first.
				currentScore + 5000;
			if (i == 1 && didPlayerComplete) 
				currentScore + 3000;
			if (i == 2 && didPlayerComplete)
				currentScore + 1000;

			scoreHolder.insert(scoreHolder.begin() + i, currentScore);
			bool found = true;
			break;
		}

		if (!found)
			scoreHolder.push_back(currentScore);
		
	}

	for (int i = 0; i < scoreHolder.size() && !breakLoop; ++i)
	{
		// while (std::getline(highScoreFile, line));
		while (highScoreFile.peek() != EOF)
		{
			if (stoi(line) < scoreHolder[i])
			{
				line = std::to_string(scoreHolder[i]);
				highScoreFile << line;
				break;
				breakLoop = true;
			}

			++i;
		}
	}

	while (waitClock.getElapsedTime() < waitTime)
	{
		/*if (waitClock.getElapsedTime() > waitTime)
			waitClock.restart();

		*/
	}

	highScoreString.clear();
	highScoreString = ("The Current High scores are: ");

	for (int i = 0; i < scoreHolder.size() && i < maxHighScores; ++i)
	{
		highScoreString += (scoreHolder[i]);
		
		if (i != maxHighScores)
			highScoreString += ", ";
	}

	highScoreString += "\n Press S to return to main menu";

	highScoreText.setString(highScoreString);

	while (!sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			gamePointer->Resetlevel();
			gamePointer->SetScreen("Main menu");
			break;
		}
	}
}

void HighScore::Draw(sf::RenderTarget& target)
{
	target.draw(background);
	target.draw(highScoreText);
	
}

void HighScore::loopScore(bool _value)
{
	hasRun = _value;
}
