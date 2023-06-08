#include "MainMenu.h"
#include "Game.h"
#include "AssetManager.h"
#include "LevelScreen.h"
#include <SFML/Graphics.hpp>

MainMenu::MainMenu(Game* newGamePointer)
	: Screen(newGamePointer)
	, mainMenuText()
	
{
	menuFont = AssetManager::RequestFont("Assets/cool.otf");

	std::string mainMenuString = ("Greetings Falcon, we're now callibrating your skills in this training simulator. \n						Please report any and all bugs!\n							  Press front left button to continue!");

	mainMenuText.setString(mainMenuString);
	mainMenuText.setFillColor(sf::Color::White);
	mainMenuText.setOutlineThickness(2.0f);
	mainMenuText.setOutlineColor(sf::Color::Black);
	mainMenuText.setCharacterSize(30);
	mainMenuText.setPosition((newGamePointer->GetWindow()->getSize().x - mainMenuText.getGlobalBounds().width) *0.2f, newGamePointer->GetWindow()->getSize().y /2);
	mainMenuText.setFont(menuFont);

	background.setTexture(AssetManager::RequestTexture("Assets/background.png"));
	background.setScale(newGamePointer->GetWindow()->getSize().x / background.getGlobalBounds().width, newGamePointer->GetWindow()->getSize().y / background.getGlobalBounds().height);
	gamePointer->GetWindow()->setMouseCursorVisible(true);

}

void MainMenu::Update(sf::Time frameTime)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y) || sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		gamePointer->SetScreen("Level Screen");
		gamePointer->ResetHighScore();
		
	}
}

void MainMenu::Draw(sf::RenderTarget& target)
{
	target.draw(background);
	target.draw(mainMenuText);
}
