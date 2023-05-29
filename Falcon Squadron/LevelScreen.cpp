#include "LevelScreen.h"
#include "AssetManager.h"
#include "Asteroid.h"
#include "Game.h"


LevelScreen::LevelScreen(Game* newGamePointer)
	: Screen(newGamePointer)
	, player()
	, mediumShip()
	, asteroids()
	, background()
	, endPanel(newGamePointer->GetWindow())
	, gameRunning(true)
	, bounds (newGamePointer->GetWindow()->getSize().x, newGamePointer->GetWindow()->getSize().y)
{
	//default positions for non dynamically allocated and test objects.

	//TODO: add vectors of object positions.

	
	background.setTexture(AssetManager::RequestTexture("Assets/Background.png"));
	player.SetPosition(80, bounds.y/2);


}

void LevelScreen::Update(sf::Time frameTime)
{

	if (gameRunning)
	{

		//update moving positions

		player.Update(frameTime, bounds);
		mediumShip.Update(frameTime, bounds);

		
	


		for (int i = 0; i < asteroids.size(); ++i)
		{
			asteroids[i]->Update(frameTime, bounds);
		}

		
		//default colllisiuon states

		player.SetColliding(false);


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

		
	}
		// endPanel.Update(frameTime);

}

//draw all objects to game window

void LevelScreen::Draw(sf::RenderTarget& _target)
{
	player.Draw(_target);
	mediumShip.Draw(_target);


	if (!gameRunning)
	{
		endPanel.Draw(_target);
	}
}

void LevelScreen::TriggerEndState(bool _win)
{
	gameRunning = false;
	endPanel.StartAnimation();
}
