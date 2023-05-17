#pragma once
#include <SFML/Graphics.hpp>
#include"SpriteObject.h"

enum class CollisionType
{
	CIRCLE,
	AABB
};

enum class PhysicsType
{
	FORWARD_EULER,
	BACKWARD_EULER,
	SYMPLECTIC_EULER,
	INCORRECT_VERLET,
	VELOCITY_VERLET
};

class Physics
{
public:
	Physics();


	//calling this function on an instance of an object will update any positional information.
	virtual void Update(sf::Time _frameTime);

	virtual void HandleCollision(Physics& other);

	bool CheckCollision(Physics other); //checks the collision with an object.
	void SetColliding(bool newColliding); // sets the collision flag of a called object.

	sf::Vector2f GetCOllisionDepth(Physics other); //checks how much collision overlap there is, to smoothly collide.

	void SetAlive(bool _alive); // sets the flag of if an object is living or dead.

protected:

	sf::Vector2f m_CollisionOffset;
	sf::Vector2f m_CollisionScale;
	CollisionType collisionType;
	bool m_IsAlive;
	sf::Sprite m_sprite;

private:

	void UpdateAcceleration();

	sf::Vector2f GetCollisionCentre();
	float GetCircleCollisionRadius();
	sf::FloatRect GetAABB();

	bool m_Colliding;
	sf::Vector2f m_Position;
	sf::Vector2f m_twoFramesOldPos;
	sf::Vector2f m_velocity;
	sf::Vector2f m_acceleration;
};

