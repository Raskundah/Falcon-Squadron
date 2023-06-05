#include "MainMenu.h"
#include "Game.h"
#include "AssetManager.h"
#include "LevelScreen.h"

MainMenu::MainMenu(Game* newGamePointer)
	: Screen(newGamePointer)
	, mainMenuText()
	
{
	menuFont = AssetManager::RequestFont("Assets/cool.otf");

	mainMenuText.setString("Greetings Falcon, we're now callibrating your skills in this training simulator. Please report any and all bugs! Press Y to continue! ");
	mainMenuText.setFillColor(sf::Color::White);
	mainMenuText.setOutlineThickness(2.0f);
	mainMenuText.setOutlineColor(sf::Color::White);
	mainMenuText.setCharacterSize(60);
	mainMenuText.setPosition(newGamePointer->GetWindow()->getSize().x, newGamePointer->GetWindow()->getSize().y /2);
	mainMenuText.setFont(menuFont);
}

void MainMenu::Update(sf::Time frameTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
	{
		gamePointer->SetScreen("Level Screen");
	}
}

void MainMenu::Draw(sf::RenderTarget& target)
{
	target.draw(mainMenuText);
}
