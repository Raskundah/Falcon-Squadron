#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Screen;

class Game
{

public:

	Game();

	void RunGameLoop();

	void EventHandling();
	void Update();
	void Draw();

	sf::RenderWindow* GetWindow();
	void SetScreen(std::string levelToLoad);


	private:


	sf::RenderWindow window;
	sf::Clock gameClock;
	std::map<std::string, Screen*> screens;
	Screen* currentScreen;

};

