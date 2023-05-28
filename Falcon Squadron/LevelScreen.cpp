#include "LevelScreen.h"
#include "AssetManager.h"
#include "Platform.h"
#include "Game.h"


LevelScreen::LevelScreen(Game* newGamePointer)
	: Screen(newGamePointer)
	, player()
	, platforms()
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
	
		for (auto& bullet : player.GetBullets())
		{
			bullet.Update(frameTime);
		}
		
		/*
		for (int i = 0; i < player.GetBullets().size(); ++i)
		{
			player.GetBullets()[i].Update(frameTime);
		}
		*/

		for (int i = 0; i < platforms.size(); ++i)
		{
			platforms[i]->Update(frameTime);
		}

		//default colllisiuon states

		player.SetColliding(false);

		for (int i = 0; i < platforms.size(); ++i)
		{
			platforms[i]->SetColliding(false);

			if (platforms[i]->CheckCollision(player))
			{
				player.SetColliding(true);
				platforms[i]->SetColliding(true);
				player.HandleCollision(*platforms[i]);
				platforms[i]->HandleCollision(player);
			}
		}		
	}
		// endPanel.Update(frameTime);

}

//draw all objects to game window

void LevelScreen::Draw(sf::RenderTarget& _target)
{
	player.Draw(_target);
	player.DrawBullets(_target);


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
