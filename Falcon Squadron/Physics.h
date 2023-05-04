#pragma once
#include <SFML/Graphics.hpp>

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

	//calling this function on an instance will draw it to the display window.
	virtual void Draw(sf::RenderTarget _target);

	sf::Vector2f GetPosition(); // this function gets the position of the object that calls it.

	virtual void SetPosition(sf::Vector2f _newPosition); // this funvction sets a position of an object that calls it.

	bool CheckCollision(Physics other); //checks the collision with an object.
	void SetColliding(bool newColliding); // sets the collision flag of a called object.

	sf::Vector2f GetCOllisionDepth(Physics other); //checks how much collision overlap there is, to smoothly collide.

	void SetAlive(bool _alive); // sets the flag of if an object is living or dead.

protected:



};

