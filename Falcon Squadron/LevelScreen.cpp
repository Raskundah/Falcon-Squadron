#include "LevelScreen.h"
#include "AssetManager.h"
#include "Asteroid.h"
#include "Game.h"
#include "EnemyShip.h"
#include "Player.h"
#include <iostream>


// make a int variable that holds the number of each ship, then multiply that by the amount for each level and add the result together to get the ful lsize of the ship vector, then fill the vector.
// 

LevelScreen::LevelScreen(Game* newGamePointer)
	: Screen(newGamePointer)
	, player()
	, mediumShip()
	, easyShip()
	, challengingShip()
	, asteroids()
	, background()
	, endPanel(newGamePointer->GetWindow())
	, gameRunning(true)
	, bounds(newGamePointer->GetWindow()->getSize().x, newGamePointer->GetWindow()->getSize().y)
	, maxAsteroids((currentLevel + 1) * 3)
	, currentLevel(1)
	, maxEasy()
	, currentEasy()
	, maxMedium()
	, currentMedium()
	, maxChallenging()
	, currentChallenging()
	, asteroidTime(sf::seconds(10.f))
	, levelTime(sf::seconds(180.0f))
	, waveTimer(sf::seconds(5.0f))
	, firstWave (true)

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
		if (waveClock.getElapsedTime().asSeconds() >= waveTimer.asSeconds() || firstWave)
		{
			MakeAsteroids(frameTime);
			WhichShips();

			firstWave = false;
			waveClock.restart();
			
		}

		//update moving positions

		player.Update(frameTime, bounds);

		for (int i = 0; i < asteroids.size(); ++i)
		{

			if (asteroids[i]->GetAsteroidAliveTime().getElapsedTime() > asteroidTime)
			{
				asteroids[i]->SetMarkedForDeletion(true);
				//CleanUp();
			}

			asteroids[i]->Update(frameTime, bounds);

		}
		for (int i = 0; i < enemies.size(); ++i)
		{
			if (enemies[i]->GetHealth() < 0)
			{
				enemies[i]->SetMarkedForDeletion(true);
				//CleanUp();
			}
			enemies[i]->Update(frameTime, bounds);

		}
		//default colllision states

		Collision();

	}
		// endPanel.Update(frameTime);

	NewCleanUp();
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
		asteroids[i]->Draw(_target);
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
			Asteroid* newAsteroid = new Asteroid;
			newAsteroid->SetPosition(frameTime, bounds);
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

		if (enemies.size() < maxEasy + maxMedium)
		{
			for (int i = 0; i < maxEasy - currentEasy; ++i)
			{
				EasyShip* newEasy = new EasyShip();
				enemies.push_back(newEasy);
			}

			for (int i = 0; i < maxMedium - currentMedium; ++i)
			{
				MediumShip* newMedium = new MediumShip();
				enemies.push_back(newMedium);
			}
		}
	}

#pragma endregion

#pragma region Level Two Ships

	if (currentLevel == 1)
	{
		maxEasy = 5;
		maxMedium = 5;
		maxChallenging = 1;

		if (enemies.size() < maxEasy + maxMedium + maxChallenging)
		{

			for (int i = 0; i < maxEasy - currentEasy; ++i)
			{
				EasyShip* newEasy = new EasyShip();
				enemies.push_back(newEasy);
			}

			for (int i = 0; i < maxMedium - currentMedium; ++i)
			{
				MediumShip* newMedium = new MediumShip();
				enemies.push_back(newMedium);
			}

			for (int i = 0; i < maxChallenging - currentChallenging; ++i)
			{
				ChallengingShip* newHard = new ChallengingShip();
				enemies.push_back(newHard);
			}
		}
	}

#pragma endregion

#pragma region  Level Three Ships

	if (currentLevel == 2)
	{
		maxEasy = 1;
		maxMedium = 10;
		maxChallenging = 2;

		if (enemies.size() < maxEasy + maxMedium + maxChallenging)
		{

			for (int i = 0; i < maxEasy - currentEasy; ++i)
			{
				EasyShip* newEasy = new EasyShip();
				enemies.push_back(newEasy);
			}

			for (int i = 0; i < maxMedium - currentMedium; ++i)
			{
				MediumShip* newMedium = new MediumShip();
				enemies.push_back(newMedium);
			}

			for (int i = 0; i < maxChallenging - currentChallenging; ++i)
			{
				ChallengingShip* newHard = new ChallengingShip();
				enemies.push_back(newHard);
			}
		}
	}
#pragma endregion


}

void LevelScreen::CleanUp()
{
	cleanShips.clear();
	cleanAsteroids.clear();
	toBeDeleted.clear();

	for (auto actor : enemies)
	{
		if (actor->IsMarkedForDeletion())
		{
			toBeDeleted.push_back(actor);
		}
		else
			cleanShips.push_back(actor);
	}
	
	for (auto actor : asteroids)
	{
		if (actor->IsMarkedForDeletion())
		{
			toBeDeleted.push_back(actor);
		}
		else
			cleanAsteroids.push_back(actor);
	}

	asteroids = cleanAsteroids;
	enemies = cleanShips;

	for (int i = 0; i < toBeDeleted.size(); ++i)
	{
		delete toBeDeleted[i];
	}
	toBeDeleted.clear();

}

void LevelScreen::NewCleanUp()
{
	for (int i = asteroids.size() - 1; i >= 0; --i)
	{
		// If anything else is to be done, do it before the delete call
		if (asteroids[i]->IsMarkedForDeletion())
		{
			delete asteroids[i];
			asteroids.erase(asteroids.begin() + i);
		}// Do NOT do anything else in the loop after this as it will break!

	}

	for (int i = enemies.size() - 1; i >= 0; --i)
	{
		// If anything else is to be done, do it before the delete call
		if (enemies[i]->IsMarkedForDeletion())
		{
			delete enemies[i];
			enemies.erase(enemies.begin() + i);
		}// Do NOT do anything else in the loop after this as it will break!
	}
}

void LevelScreen::Collision()
{
	player.SetColliding(false);

	for (int i = 0; i < player.GetBullets().size(); ++i)
	{
		player.GetBullets()[i].SetColliding(false);
	}



	for (int i = 0; i < enemies.size(); ++i)
	{
		enemies[i]->SetColliding(false);
		for (int s = 0; s < enemies[i]->GetBullets().size(); ++s)
		{
			enemies[i]->GetBullets()[s].SetColliding(false);
		}
	}
	//check collision

	for (int i = 0; i < asteroids.size(); ++i)
	{
		asteroids[i]->SetColliding(false);

		if (asteroids[i]->CheckCollision(player))
		{
			player.SetColliding(true);
			asteroids[i]->SetColliding(true);
			player.HandleCollision(*asteroids[i]);
			asteroids[i]->HandleCollision(player);
		}
	}
	for (int i = 0; i < player.GetBullets().size(); ++i)
	{
		for (int s = 0; s < enemies.size(); ++s)
		{
			if (player.GetBullets()[i].CheckCollision(*enemies[s]))
			{
				player.GetBullets()[i].SetColliding(true);
				enemies[s]->SetHealth(enemies[s]->GetHealth() - player.GetDamage());
			}
		}

		for (int a = 0; a < asteroids.size(); ++a)
		{
			if (player.GetBullets()[i].CheckCollision(*asteroids[a]))
			{
				asteroids[a]->TakeDamage();
			}

		}
	}

	for (int i = 0; i < enemies.size(); ++i)
	{
		for (int s = 0; s < enemies[i]->GetBullets().size(); ++s)
		{
			if (enemies[i]->GetBullets()[s].CheckCollision(player))
			{
				player.SetHealth(player.GetHealth() - enemies[i]->GetDamage());
			}
		}


	}
}
