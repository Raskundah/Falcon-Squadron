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
	, gameRunning(false)
	, bounds(newGamePointer->GetWindow()->getSize().x, newGamePointer->GetWindow()->getSize().y)
	, maxAsteroids((currentLevel + 1) * 3)
	, currentLevel(0)
	, maxEasy()
	, currentEasy()
	, maxMedium()
	, currentMedium()
	, maxChallenging()
	, currentChallenging()
	, numberOfEasy()
	, numberOfMedium()
	, numberOfHard()
	, asteroidTime(sf::seconds(10.f))
	, levelTime(sf::seconds(180.0f))
	, waveTimer(sf::seconds(5.0f))
	, firstWave(true)
	, MaxPickups(3) // never set this to an even number, it allows the vector of pickups to go out of defined bounds. what the fuck.
	, isBroken(false)
	, gameMusic()
	, MaxTime(120.0f)
	, remainingTime(0)
	, healthText()
	, shieldText()
	, scoreText()
	, timeText()
	, MaxEnemies(13) 
	, firstLoad(true)



{

	//default positions for non dynamically allocated and test objects.

	gameFont = AssetManager::RequestFont("Assets/cool.otf");

	gameMusic.openFromFile("Assets/Music/suez crisis remade.ogg");
	gameMusic.setLoop(true);
	gameMusic.setVolume(10);
	

	background.setTexture(AssetManager::RequestTexture("Assets/Background.png"));
	background.setPosition(0, 0);
	background.setScale(bounds.x / background.getGlobalBounds().width , bounds.y / background.getGlobalBounds().height);

}

void LevelScreen::Update(sf::Time frameTime)
{
	if (firstLoad)
	{
		player.SetPosition(80, bounds.y / 2);
		player.SetExploitChecker(false);
		player.SetAlive(true);
		gameRunning = true;
		firstLoad = false;
		MaxTime = 120.f;
		levelClock.restart();
		gameMusic.play();
		ResetVectors();
		player.SetHealth(105);
		player.SetShields(0);
		player.ResetScore();
		currentLevel = 0;
		numberOfEasy = 0;
		numberOfMedium = 0;
		numberOfHard = 0;

	}

	if (remainingTime <= 0)
	{
		reset = true;
	}

	if (player.GetHealth() <= 0)
	{
		player.SetAlive(false);

		gameMusic.stop();
		gamePointer->SetPlayerAlive(player.GetAlive());
		gamePointer->SetPlayerScore(player.GetScore());

		gamePointer->SetScreen("HighScore");
		
	}



	if (gameRunning && player.GetHealth() >= 0)
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

	

	for (int i = 0; i < asteroids.size(); ++i)
	{
		asteroids[i]->Draw(_target);
	}

	for (int i = 0; i < pickups.size(); ++i)
	{
		pickups[i]->Draw(_target);
	}

	for (int i = 0; i < enemies.size(); ++i)
	{
		enemies[i]->Draw(_target);
	}

	_target.draw(healthText);
	_target.draw(shieldText);
	_target.draw(timeText);
	_target.draw(scoreText);
	_target.draw(levelText);



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

		if (enemies.size() > maxEasy + maxMedium)
			return;

		if (enemies.size() < maxEasy + maxMedium && numberOfEasy < maxEasy)
		{
			for (int i = 0; i < maxEasy - numberOfEasy; ++i)
			{
				if (enemies.size() >= maxEasy + maxMedium + maxChallenging)
					break;

				EasyShip* newEasy = new EasyShip();
				enemies.push_back(newEasy);
				numberOfEasy++;
			}

			for (int i = 0; i < maxMedium - numberOfMedium; ++i)
			{
				if (enemies.size() >= maxEasy + maxMedium + maxChallenging && numberOfMedium < maxMedium )
					break;

				MediumShip* newMedium = new MediumShip();
				enemies.push_back(newMedium);
				numberOfMedium++;
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

			for (int i = 0; i < maxEasy - numberOfEasy; ++i)
			{
				if (enemies.size() >= maxEasy + maxMedium + maxChallenging && numberOfEasy < maxEasy)
					break;

				EasyShip* newEasy = new EasyShip();
				enemies.push_back(newEasy);
				numberOfEasy++;

			}

			for (int i = 0; i < maxMedium - numberOfMedium; ++i)
			{
				if (enemies.size() >= maxEasy + maxMedium + maxChallenging && numberOfMedium < maxMedium)
					break;

				MediumShip* newMedium = new MediumShip();
				enemies.push_back(newMedium);
				numberOfMedium++;
			}

			for (int i = 0; i < maxChallenging - numberOfHard; ++i)
			{
				if (enemies.size() >= maxEasy + maxMedium + maxChallenging && numberOfHard < maxChallenging)
					break;

				ChallengingShip* newHard = new ChallengingShip();
				enemies.push_back(newHard);
				numberOfHard++;
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

			for (int i = 0; i < maxEasy - numberOfEasy; ++i)
			{
				if (enemies.size() >= maxEasy + maxMedium + maxChallenging && numberOfEasy < maxEasy)
					break;

				EasyShip* newEasy = new EasyShip();
				enemies.push_back(newEasy);
				numberOfEasy++;
			}

			for (int i = 0; i < maxMedium - numberOfMedium; ++i)
			{
				if (enemies.size() >= maxEasy + maxMedium + maxChallenging && numberOfMedium < maxMedium)
					break;

				MediumShip* newMedium = new MediumShip();
				enemies.push_back(newMedium);
				numberOfMedium++;

			}

			for (int i = 0; i < maxChallenging - numberOfHard; ++i)
			{
				if (enemies.size() >= maxEasy + maxMedium + maxChallenging && numberOfHard < maxChallenging)
					break;

				ChallengingShip* newHard = new ChallengingShip();
				enemies.push_back(newHard);
				numberOfHard++;

			}

		}
	}
#pragma endregion

#pragma region BossShips
	{
		if (currentLevel == 3)
		{
			BossShip* newBoss = new BossShip();
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

			if (dynamic_cast<EasyShip*>(enemies[i]))
			{
				numberOfEasy--;
			}

			if (dynamic_cast<MediumShip*>(enemies[i]))
			{
				numberOfMedium--;
			}

			if (dynamic_cast<ChallengingShip*>(enemies[i]))
			{
				numberOfHard--;
			}

			delete enemies[i];
			enemies.erase(enemies.begin() + i);
		}// Do NOT do anything else in the loop after this as it will break!
	}

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

void LevelScreen::SetLevel(int _valueInt)
{
	currentLevel = _valueInt;
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
	healthText.setCharacterSize(22);
	healthText.setPosition(0, 20);
	healthText.setFont(gameFont);
#pragma endregion

#pragma region  shields

	shieldString = ("Shields: ");
	shieldString += std::to_string(player.GetShields());

	shieldText.setString(shieldString);
	shieldText.setFillColor(sf::Color::White);
	shieldText.setOutlineThickness(2.0f);
	shieldText.setOutlineColor(sf::Color::Black);
	shieldText.setCharacterSize(22);
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
	timeText.setCharacterSize(22);
	timeText.setPosition(bounds.x * 0.5f, 20);
	timeText.setFont(gameFont);
#pragma endregion

	scoreString = ("Score: " );
	scoreString += std::to_string(player.GetScore());

	scoreText.setString(scoreString);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setOutlineThickness(2.0f);
	scoreText.setOutlineColor(sf::Color::Black);
	scoreText.setCharacterSize(22);
	scoreText.setPosition(bounds.x * 0.75f, 20);
	scoreText.setFont(gameFont);

	levelString = ("Level:  " );
	levelString += std::to_string(currentLevel + 1);

	levelText.setString(levelString);
	levelText.setFillColor(sf::Color::White);
	levelText.setOutlineThickness(2.0f);
	levelText.setOutlineColor(sf::Color::Black);
	levelText.setCharacterSize(22);
	levelText.setPosition(bounds.x - levelText.getGlobalBounds().width-10, 20);
	levelText.setFont(gameFont);

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

		
			player.SetColliding(true);
			asteroids[i]->SetColliding(true);
			player.HandleCollision(*asteroids[i]);
			asteroids[i]->HandleCollision(player);

			if (asteroids[i]->CheckCollision(player) && asteroids[i]->GetDamageCheck())
			{
				if (player.GetPosition().x > bounds.x * 0.75)
					player.SetHealth(-10);

				player.SetHealth(-asteroids[i]->GetDamage());
				asteroids[i]->SetDamageCheck(true);
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
				player.SetScore(enemies[s]->GetScore());

			}
		}

		// check if a asteroid collided with a player's bullet

		for (int a = 0; a < asteroids.size(); ++a)
		{
			if (player.GetBullets()[i]->CheckCollision(*asteroids[a]))
			{
    			asteroids[a]->TakeDamage();
				if (asteroids[a]->GetHealth() <= 0)
				{
					player.SetScore(asteroids[a]->GetScore());
				}
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

		MaxTime = 120.0f;

		remainingTime = MaxTime;

		firstWave = true;

		waveClock.restart();
		levelClock.restart();
		numberOfEasy = 0;
		numberOfMedium = 0;
		numberOfHard = 0;

		if (currentLevel > 3)
		{
			gamePointer->SetPlayerScore(player.GetScore());
			gamePointer->SetPlayerAlive(player.GetAlive());
			gameMusic.stop();
			player.SetPosition(20, bounds.y /2);
			gamePointer->SetScreen("HighScore");
			
		}

	}
	
}

void LevelScreen::setReset(bool _reset)
{
	firstLoad = reset;
}

