#include "HighScore.h"
#include "AssetManager.h"
#include "Game.h"
#include "Player.h"
#include  <algorithm>
#include <iostream>
#include <fstream>



HighScore::HighScore(Game* newGamePointer)
	: Screen(newGamePointer)
	, currentScore(newGamePointer->GetPlayerScore())
	, didPlayerComplete(newGamePointer->GetPlayerAlive())
	, count()
	, maxHighScores(10)
	, waitTime(sf::seconds(1.0f))
	, breakLoop(false)
	, hasLoopRun(false)
	, highScoreFile()
	, doFileRead(true)
	, doFileWrite(true)

{
	highScoreFont = AssetManager::RequestFont("Assets/cool.otf");

	//std::string highScoreString = ("Here we've reached the end of the simulation. \nIf you're reading this, the high scores are broken. \nPress S to go back to main menu.\n");

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
{
	const std::string HIGH_SCORE_NAME = "Assets/HighScores/highscore.txt";

	scoreHolder.clear();
	
	currentScore = gamePointer->GetPlayerScore();
	didPlayerComplete = gamePointer->GetPlayerAlive();
	waitClock.restart();

	if(doFileRead)
	{
		highScoreFile.open(HIGH_SCORE_NAME, std::fstream::in);


		while ((highScoreFile >> line))
		{
			scoreHolder.push_back(stoi(line));
		}

		doFileRead = false;

		highScoreFile.close();

	}

	bool found = false;

	if (!hasLoopRun)
	{
		for (int i = 0; i < scoreHolder.size(); ++i) // here we loop through the current session's high scores.
		{

			if (currentScore > scoreHolder[i]) //checks if the recent score is greater than the current entry in the score holder for the session.
			{			
				if (i == 0 && didPlayerComplete) // bonus for finishing first.
					currentScore + 5000;
				if (i == 1 && didPlayerComplete)
					currentScore + 3000;
				if (i == 2 && didPlayerComplete)
					currentScore + 1000;

				scoreHolder.insert(scoreHolder.begin(), currentScore);
				found = true;
				break;
			}
		}

		if (!found)
			scoreHolder.push_back(currentScore);

		/*for (int i = 0; i < scoreHolder.size() || !breakLoop; ++i)
		{
			while (std::getline(highScoreFile, line));

			//while (highScoreFile.peek() != EOF)
			{
				if (stoi(line) < scoreHolder[i])
				{
					line = std::to_string(scoreHolder[i]);
					highScoreFile << line;

					break;
					breakLoop = true;
				}
			}
		}
		*/

		/*while (waitClock.getElapsedTime() < waitTime)
		{
			if (waitClock.getElapsedTime() > waitTime)
				waitClock.restart();
		}
		*/



		highScoreString.clear();
		std::sort(scoreHolder.rbegin(), scoreHolder.rend());
		highScoreString = ("The Current High scores are:  ");

		for (int i = 0; i < scoreHolder.size() && i < maxHighScores; ++i)
		{
			highScoreString += std::to_string(scoreHolder[i]);
			highScoreString += " , ";

		}

		highScoreString += "\n Press Front Left to return to main menu";

		highScoreText.setString(highScoreString);

		hasLoopRun = true;
	
	}
	/*
	sf::Event event;
	while (gamePointer->GetWindow()->pollEvent(event))
	{
		if (event.type == sf::Event::KeyReleased)
		{


			hasLoopRun = false;
			gamePointer->Resetlevel();
			gamePointer->SetScreen("Main menu");
		}

		// Close the game if escape is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			hasLoopRun = false;
			gamePointer->Resetlevel();
			gamePointer->SetScreen("Main menu");
		}
	}
	*/


	if (doFileWrite)
	{
		highScoreFile.open(HIGH_SCORE_NAME, std::fstream::out);


		for (int i = 0; i < scoreHolder.size(); i++)
		{
			highScoreFile << std::to_string(scoreHolder[i]) << std::endl;
		}

		highScoreFile.close();

		doFileWrite = false;
	}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))
		{
			hasLoopRun = false;
			doFileRead = true;
			doFileWrite = true;

			gamePointer->Resetlevel();	
			highScoreFile.close();
			gamePointer->SetScreen("Main menu");
	
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

void HighScore::passToFile(int i)
{
	highScoreFile << std::to_string(i) << std::endl;
}
