#include "Game.h"
#include "Screen.h"
#include "LevelScreen.h"
#include "MainMenu.h";
#include "HighScore.h"


Game::Game()
	: window(sf::VideoMode::getDesktopMode(), "Falcon Squadron", sf::Style::Titlebar | sf::Style::Fullscreen)
	, gameClock()
	, currentScreen(nullptr)
	, gameLevel(0)
{
	// Window setup
	window.setMouseCursorVisible(false);

	// TODO: Setup screens


	//currentScreen = new LevelScreen(this);
	screens.insert({ "Main menu", new MainMenu(this) });
	screens.insert({ "Level Screen", new LevelScreen(this) });
	screens.insert({ "HighScore", new HighScore(this) });

	currentScreen = screens["Main menu"];



}

void Game::RunGameLoop()
{
	// Repeat as long as the window is open
	while (window.isOpen())
	{
		Update();
		Draw();
		EventHandling();
	}

}

void Game::EventHandling()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();

		// Close the game if escape is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7))
		{
			window.close();
		}
	}
}

void Game::Update()
{
	sf::Time frameTime = gameClock.restart();

	// Update current screen
	if (currentScreen != nullptr)
		currentScreen->Update(frameTime);

	// TODO: Handle changes to other screens

}

void Game::Draw()
{
	window.clear();
	
	// Draw current screen
	if (currentScreen != nullptr)
		currentScreen->Draw(window);

	window.display();
}

sf::RenderWindow* Game::GetWindow()
{
	return &window;
}

void Game::SetScreen(std::string levelToLoad)
{
	currentScreen = screens[levelToLoad];
}

void Game::SetPlayerAlive(bool _death)
{
	living = _death;
}

bool Game::GetPlayerAlive()
{
	return living;
}

void Game::SetPlayerScore(int _score)
{
	score = _score;
}

int Game::GetPlayerScore()
{
	return score;
}

int Game::GetGameLevel()
{
	return gameLevel;
}

void Game::SetGameLevel(int _level)
{
	gameLevel = _level;
}

void Game::Resetlevel()
{
	dynamic_cast<LevelScreen*>(screens["Level Screen"])->setReset(true);
}

void Game::ResetHighScore()
{
	dynamic_cast<HighScore*>(screens["HighScore"])->loopScore(true);
}


