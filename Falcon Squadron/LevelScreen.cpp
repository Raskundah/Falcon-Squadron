#include "LevelScreen.h"
#include "AssetManager.h"
#include "Asteroid.h"
#include "Game.h"


// make a int variable that holds the number of each ship, then multiply that by the amount for each level and add the result together to get the ful lsize of the ship vector, then fill the vector.
// 

LevelScreen::LevelScreen(Game* newGamePointer)
	: Screen(newGamePointer)
	, player()
	, mediumShip()
	, asteroids()
	, background()
	, endPanel(newGamePointer->GetWindow())
	, gameRunning(true)
	, bounds(newGamePointer->GetWindow()->getSize().x, newGamePointer->GetWindow()->getSize().y)
	, maxAsteroids((currentLevel + 1) * 3)
	, currentLevel(0)
	, maxEasy()
	, currentEasy()
	, maxMedium()
	, currentMedium()
	, maxChallenging()
	, currentChallenging()
	

{
	//default positions for non dynamically allocated and test objects.

	//TODO: add vectors of object positions.

	
	background.setTexture(AssetManager::RequestTexture("Assets/Background.png"));
	background.setPosition(0, 0);
	background.setScale(bounds.x / background.getGlobalBounds().width , bounds.y / background.getGlobalBounds().height);

	player.SetPosition(80, bounds.y/2);
	

}

void LevelScreen::Update(sf::Time frameTime)
{

	if (gameRunning)
	{
		MakeAsteroids(frameTime);
		WhichShips();

		//update moving positions

		player.Update(frameTime, bounds);

		/*
		mediumShip.Update(frameTime, bounds);
		easyShip.Update(frameTime, bounds);
		challengingShip.Update(frameTime, bounds);

		*/
		
		for (int i = 0; i < asteroids.size(); ++i)
		{
			asteroids[i].Update(frameTime, bounds);
		}

		for (int i = 0; i < enemies.size(); ++i)
		{
			enemies[i]->Update(frameTime, bounds);
		}

		
		//default colllisiuon states

		player.SetColliding(false);
		

		for (int i = 0; i < asteroids.size(); ++i)
		{
			asteroids[i].SetColliding(false);

			if (asteroids[i].CheckCollision(player))
			{
				player.SetColliding(true);
				asteroids[i].SetColliding(true);
				player.HandleCollision(asteroids[i]);
				asteroids[i].HandleCollision(player);
			}
		}

		
	}
		// endPanel.Update(frameTime);

}

//draw all objects to game window

void LevelScreen::Draw(sf::RenderTarget& _target)
{

	_target.draw(background);
	player.Draw(_target);

	for (int i = 0; i < enemies.size(); ++i)
	{
		enemies[i]->Draw(_target);
	}


	for (int i = 0; i < asteroids.size(); ++i)
	{
		asteroids[i].Draw(_target);
	}


	if (!gameRunning)
	{
		endPanel.Draw(_target);
	}
}

void LevelScreen::MakeAsteroids(sf::Time frameTime)
{
	if (asteroids.size() < maxAsteroids)
	{
		for (int i = 0; i < maxAsteroids - asteroids.size(); ++i)
		{
			Asteroid newAsteroid;
			newAsteroid.SetPosition(frameTime, bounds);
			asteroids.push_back(newAsteroid);	
		}
	}
}
void LevelScreen::TriggerEndState(bool _win)
		{
			gameRunning = false;
			endPanel.StartAnimation();
		}

void LevelScreen::WhichShips()
{
#pragma region Level One ships

	if (currentLevel == 0)
	{
		maxEasy = 10;
		maxMedium = 2;

		for (int i = 0; i < maxEasy - currentEasy; ++i)
		{
			EasyShip* newEasy{};
			enemies.push_back(newEasy);
		}

		for (int i = 0; i < maxMedium - currentMedium; ++i)
		{
			MediumShip* newMedium{};
			enemies.push_back(newMedium);
		}

	}

#pragma endregion

#pragma region Level Two Ships

	if (currentLevel == 1)
	{
		maxEasy = 5;
		maxMedium = 5;
		maxChallenging = 1;

		for (int i = 0; i < maxEasy - currentEasy; ++i)
		{
			EasyShip* newEasy{};
			enemies.push_back(newEasy);
		}

		for (int i = 0; i < maxMedium - currentMedium; ++i)
		{
			MediumShip* newMedium{};
			enemies.push_back(newMedium);
		}

		for (int i = 0; i < maxChallenging - currentChallenging; ++i)
		{
			ChallengingShip* newHard{};
			enemies.push_back(newHard);
		}
	}

#pragma endregion

#pragma region  Level Three Ships

	if (currentLevel == 2)
	{
		maxEasy = 1;
		maxMedium = 10;
		maxChallenging = 2;

		for (int i = 0; i < enemies.size() - currentEasy; ++i)
		{
			EasyShip* newEasy{};
			enemies.push_back(newEasy);
		}

		for (int i = 0; i < enemies.size() - currentMedium; ++i)
		{
			MediumShip* newMedium{};
			enemies.push_back(newMedium);
		}

		for (int i = 0; i < enemies.size() - currentChallenging; ++i)
		{
			ChallengingShip* newHard{};
			enemies.push_back(newHard);
		}
	}

#pragma endregion

}