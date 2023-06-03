#pragma once
#include <SFML/Graphics.hpp>


class SpriteObject
{
public:
	SpriteObject();

	virtual void Update(sf::Time _FrameTime);
	virtual void Draw(sf::RenderTarget& _target);

	sf::Vector2f GetPosition();
	virtual void SetPosition(sf::Vector2f _newPos);
	void SetPosition(float m_newX, float m_newY);

protected:
	sf::Sprite m_sprite;
	bool m_isAliveInternal;
	sf::Vector2f m_position;
};

