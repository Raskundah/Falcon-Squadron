#include "LevelScreen.h"
#include "AssetManager.h"
#include "Asteroid.h"
#include "Game.h"
#include "EnemyShip.h"
#include "Player.h"
#include <iostream>
#include <SFML/Audio.hpp>

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
	, currentLevel(0)
	, maxEasy()
	, currentEasy()
	, maxMedium()
	, currentMedium()
	, maxChallenging()
	, currentChallenging()
	, asteroidTime(sf::seconds(10.f))
	, levelTime(sf::seconds(180.0f))
	, waveTimer(sf::seconds(5.0f))
	, firstWave(true)
	, MaxPickups(3) // never set this to an even number, it allows the vector of pickups to go out of defined bounds. what the fuck.
	, isBroken(false)
	, gameMusic()
	, MaxTime(6.0f)
	, remainingTime(0)
	, healthText()
	, shieldText()
	, scoreText()
	, timeText()
	, MaxEnemies(13) 

{

	//default positions for non dynamically allocated and test objects.

	gameFont = AssetManager::RequestFont("Assets/cool.otf");

	gameMusic.openFromFile("Assets/Music/suez crisis remade.ogg");
	gameMusic.setLoop(true);
	gameMusic.setVolume(10);
	gameMusic.play();


	background.setTexture(AssetManager::RequestTexture("Assets/Background.png"));
	background.setPosition(0, 0);
	background.setScale(bounds.x / background.getGlobalBounds().width , bounds.y / background.getGlobalBounds().height);
	

	player.SetPosition(80, bounds.y/2);

}


void LevelScreen::Update(sf::Time frameTime)
{
	if (remainingTime <= 0)
	{
		reset = true;
	}

	if (gameRunning /*||player.GetHealth() <= 0*/)
	{

		if (waveClock.getElapsedTime().asSeconds() >= waveTimer.asSeconds() || firstWave)
		{
			MakeAsteroids(frameTime);
			PickUps(frameTime);
			WhichShips();

			firstWave = false;
			waveClock.restart();
		}



		//update moving positions

		player.Update(frameTime, bounds);
		TextHud();


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

		for (int i = 0; i < pickups.size(); ++i)
		{
			
			pickups[i]->Update(frameTime, bounds);

		}
		//default colllision states

		Collision();

	}
		// endPanel.Update(frameTime);

	NewCleanUp();
	ResetVectors();


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

	for (int i = 0; i < pickups.size(); ++i)
	{
		pickups[i]->Draw(_target);
	}

	_target.draw(healthText);
	_target.draw(shieldText);
	_target.draw(timeText);
	_target.draw(scoreText);



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
		maxEasy = 9;
		maxMedium = 2;
		maxChallenging = 0;

		if (enemies.size() >= maxEasy + maxMedium)
			return;

		if (enemies.size() < maxEasy + maxMedium)
		{
			for (int i = 0; i < maxEasy - currentEasy; ++i)
			{
				if (enemies.size() >= maxEasy + maxMedium + maxChallenging)
					break;

				EasyShip* newEasy = new EasyShip();
				enemies.push_back(newEasy);
			}

			for (int i = 0; i < maxMedium - currentMedium; ++i)
			{
				if (enemies.size() >= maxEasy + maxMedium + maxChallenging)
					break;

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
				if (enemies.size() >= maxEasy + maxMedium + maxChallenging)
					break;

				EasyShip* newEasy = new EasyShip();
				enemies.push_back(newEasy);

			}

			for (int i = 0; i < maxMedium - currentMedium; ++i)
			{
				if (enemies.size() >= maxEasy + maxMedium + maxChallenging)
					break;

				MediumShip* newMedium = new MediumShip();
				enemies.push_back(newMedium);
			}

			for (int i = 0; i < maxChallenging - currentChallenging; ++i)
			{
				if (enemies.size() >= maxEasy + maxMedium + maxChallenging)
					break;

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
				if (enemies.size() >= maxEasy + maxMedium + maxChallenging)
					break;

				EasyShip* newEasy = new EasyShip();
				enemies.push_back(newEasy);
			}

			for (int i = 0; i < maxMedium - currentMedium; ++i)
			{
				if (enemies.size() >= maxEasy + maxMedium + maxChallenging)
					break;

				MediumShip* newMedium = new MediumShip();
				enemies.push_back(newMedium);
			}

			for (int i = 0; i < maxChallenging - currentChallenging; ++i)
			{
				if (enemies.size() >= maxEasy + maxMedium + maxChallenging)
					break;

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

	/*
	for (int i = enemies.size() - 1; i >= 0; --i)
	{
		for (int b = 0; b < enemies[i]->GetBullets().size(); ++b)
		{
			if (enemies[i]->GetBullets()[b]->IsMarkedForDeletion())
			{
				delete enemies[i]->GetBullets()[b];
				enemies[i]->GetBullets().erase(enemies[i]->GetBullets().begin + b);
			}
		}
		// If anything else is to be done, do it before the delete call
		if (enemies[i]->IsMarkedForDeletion())
		{
			delete enemies[i];
			enemies.erase(enemies.begin() + i);
		}// Do NOT do anything else in the loop after this as it will break!
	}
		*/
	

	for (int i = pickups.size() - 1; i >= 0; --i)
	{
		// If anything else is to be done, do it before the delete call
		if (pickups[i]->IsMarkedForDeletion())
		{
			delete pickups[i];
			pickups.erase(pickups.begin() + i);
		}// Do NOT do anything else in the loop after this as it will break!
	}

	
}

void LevelScreen::PickUps(sf::Time frameTime)
{

	if (pickups.size() < MaxPickups)
	{
		for (int i = 0; i < MaxPickups - pickups.size(); ++i)
		{
			if (WhichPickup() > 0)
			{
				HealthPickup* newHealth = new HealthPickup{};
				newHealth->UpdatePosition(frameTime, bounds);
				pickups.push_back(newHealth);
			}
			else
			{
				ShieldPickup* newShield = new ShieldPickup();
				newShield->UpdatePosition(frameTime, bounds);
				pickups.push_back(newShield);
			}
		}

	}
}

int LevelScreen::WhichPickup()
{
	// Create a random number generator engine
	std::random_device rd;
	std::mt19937 gen(rd());

	// Create a distribution to generate either 1 or -1
	std::uniform_int_distribution<int> distribution(0, 1);

	// Generate and return a random number (either 1 or -1)
	return (distribution(gen) == 0) ? -1 : 1;
}

void LevelScreen::TextHud()
{
#pragma region health
	healthString = ("Health: ");
	healthString += std::to_string(player.GetHealth());

	healthText .setString(healthString);
	healthText.setFillColor(sf::Color::White);
	healthText.setOutlineThickness(2.0f);
	healthText.setOutlineColor(sf::Color::Black);
	healthText.setCharacterSize(30);
	healthText.setPosition(1, 20);
	healthText.setFont(gameFont);
#pragma endregion

#pragma region  shields

	shieldString = ("Shields: ");
	shieldString += std::to_string(player.GetShields());

	shieldText.setString(shieldString);
	shieldText.setFillColor(sf::Color::White);
	shieldText.setOutlineThickness(2.0f);
	shieldText.setOutlineColor(sf::Color::Black);
	shieldText.setCharacterSize(30);
	shieldText.setPosition(bounds.x * 0.25f, 20);
	shieldText.setFont(gameFont);
#pragma endregion

#pragma region Timer
	remainingTime = MaxTime - levelClock.getElapsedTime().asSeconds();
	int timeToDisplay = trunc(remainingTime);

	

	timerString = ("Time Remaining: ");
	timerString += std::to_string((int)ceil(timeToDisplay));

	timeText.setString(timerString);
	timeText.setFillColor(sf::Color::White);
	timeText.setOutlineThickness(2.0f);
	timeText.setOutlineColor(sf::Color::Black);
	timeText.setCharacterSize(30);
	timeText.setPosition(bounds.x * 0.5f, 20);
	timeText.setFont(gameFont);
#pragma endregion

	scoreString = ("Score: ");
	scoreString += std::to_string(player.GetScore());

	scoreText.setString(scoreString);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setOutlineThickness(2.0f);
	scoreText.setOutlineColor(sf::Color::Black);
	scoreText.setCharacterSize(30);
	scoreText.setPosition(bounds.x * 0.75f, 20);
	scoreText.setFont(gameFont);

#pragma region  Score


#pragma endregion




}

void LevelScreen::Collision()
{
#pragma region Defaults



	player.SetColliding(false); // player is not colliding by default. 


	for (int i = 0; i < player.GetBullets().size(); ++i)
	{
		player.GetBullets()[i]->SetColliding(false); // players bulets are not colliding by default.
	}

	for (int i = 0; i < pickups.size(); ++i)
	{
		pickups[i]->SetColliding(false); //set pickup collision to false by default.
	}


	for (int i = 0; i < enemies.size(); ++i)
	{
		enemies[i]->SetColliding(false); 
		for (int s = 0; s < enemies[i]->GetBullets().size(); ++s)
		{
			enemies[i]->GetBullets()[s]->SetColliding(false);

			// enemies and their bullets are not colliding by default.
		}
	}

#pragma endregion
	//check collision

	for (int i = 0; i < pickups.size(); ++i)
	{
		if (pickups[i]->CheckCollision(player))
		{
			player.SetColliding(true);
			pickups[i]->SetColliding(true);
			
			if (pickups[i]->GetPickupID()) // pickup ID of shield is 1 so we hit a shield.
			{
				player.SetShields(pickups[i]->Modify());
				pickups[i]->SetMarkedForDeletion(true);
			}
			else
			{
				player.SetHealth(pickups[i]->Modify()); // if it's not a shield, it must be a health pickup.
				pickups[i]->SetMarkedForDeletion(true);

			}
		}
	}

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

	//check if the player's shot an enemy.

	for (int i = 0; i < player.GetBullets().size(); ++i)
	{
		for (int s = 0; s < enemies.size(); ++s)
		{
			if (player.GetBullets()[i]->CheckCollision(*enemies[s]))
			{
				player.GetBullets()[i]->SetColliding(true);
				player.GetBullets()[i]->SetMarkedForDeletion(true);

				enemies[s]->SetColliding(true);
				enemies[s]->SetHealth(player.GetDamage());

			}
		}

		// check if a asteroid collided with a player's bullet

		for (int a = 0; a < asteroids.size(); ++a)
		{
			if (player.GetBullets()[i]->CheckCollision(*asteroids[a]))
			{
    				asteroids[a]->TakeDamage();
				player.GetBullets()[i]->SetMarkedForDeletion(true);
			}
		}
	}

	// check if the enemy bullet collided with a player.

	for (int i = 0; i < enemies.size(); ++i)
	{
		for (int s = 0; s < enemies[i]->GetBullets().size(); ++s)
		{
			if (enemies[i]->GetBullets()[s]->CheckCollision(player))
			{
				player.SetColliding(true);
				enemies[i]->GetBullets()[s]->SetMarkedForDeletion(true);
				
				if(player.GetShields() >0)
					player.SetShields(-enemies[i]->GetDamage());

				else
					player.SetHealth (- enemies[i]->GetDamage() );
			}
		}
	}
}

void LevelScreen::ResetVectors()
{

	if (remainingTime <= 0.f &&  reset == true)
	{

		player.SetPosition(80, bounds.y / 2);

		// clean up between levels
		for (int i = enemies.size() - 1; i >= 0; --i)
		{
			delete enemies[i];
		}
		enemies.clear();

		for (int i = pickups.size() - 1; i >= 0; --i)
		{
			delete pickups[i];
		}
		pickups.clear();


		for (int i = asteroids.size() - 1; i >= 0; --i)
		{
			delete asteroids[i];
		}
		asteroids.clear();

		player.DestroyAllBullets();

		currentLevel++;

		remainingTime = MaxTime;

		firstWave = true;

		waveClock.restart();
		levelClock.restart();

	}
	
}
