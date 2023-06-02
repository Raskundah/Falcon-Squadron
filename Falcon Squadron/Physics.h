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

class Physics :
	public SpriteObject
{
public:
	Physics();


	//calling this function on an instance of an object will update any positional information.
	virtual void Update(sf::Time _frameTime);
	virtual void Draw(sf::RenderTarget& target);

	virtual void HandleCollision(Physics& other); //parent implimentation of handle collision. 

	bool CheckCollision(Physics other); //checks the collision with an object.
	void SetColliding(bool newColliding); // sets the collision flag of a called object.

	sf::Vector2f GetCOllisionDepth(Physics other); //checks how much collision overlap there is, to smoothly collide.

	void SetAlive(bool _alive); // sets the flag of if an object is living or dead.

protected:

	sf::Vector2f m_CollisionOffset; //collision offset for where to place the collision box. 
	sf::Vector2f m_CollisionScale; //scales the collision box.
	CollisionType collisionType; //determines which collision type to use.
	bool m_IsAlive; //handles if the object is alive.
	// sf::Vector2f m_pos; // if I don't have this things break in the old physics implimentation, this sucks.

private:


	sf::Vector2f GetCollisionCentre(); // determines the centre of the collision object.
	float GetCircleCollisionRadius(); // gets the radius of circle colliders.
	sf::FloatRect GetAABB(); // gets the dimensions for making an AABB collision box.

	bool m_Colliding; // determines if the object is colliding.
};

