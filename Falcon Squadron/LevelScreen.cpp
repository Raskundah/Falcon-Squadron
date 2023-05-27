#include "LevelScreen.h"
#include "AssetManager.h"
#include "Platform.h"
#include "Game.h"

LevelScreen::LevelScreen(Game* newGamePointer)
	: Screen(newGamePointer)
	, player()
	, platforms()

	, endPanel(newGamePointer->GetWindow())
	, gameRunning(true)
{
	//default positions for non dynamically allocated and test objects.

	//TODO: add vectors of object positions.

	int maxWidth = newGamePointer->GetWindow()->getSize().x;
	int maxHeight = newGamePointer->GetWindow()->getSize().y;

	player.SetPosition(80, maxHeight/2);	
	

}

void LevelScreen::Update(sf::Time frameTime)
{
	if (gameRunning)
	{

		//update moving positions

		player.Update(frameTime);
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
	sf::CircleShape shape(50);
	shape.setFillColor(sf::Color(100, 250, 50));
	shape.setPosition(300, 300);

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
