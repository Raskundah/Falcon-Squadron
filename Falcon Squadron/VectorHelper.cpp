#include "VectorHelper.h"

float VectorHelper::SquareMagnitude(sf::Vector2f vec)
{
	return vec.x * vec.x + vec.y * vec.y;  //takes a vector and returns the square of each component
}

sf::Vector2f VectorHelper::Normalise(sf::Vector2f vec)
{
	float mag = Magnitude(vec);

	vec.x = vec.x / mag;
	vec.y = vec.y / mag;


	//takes a vector and returns it's normal.
	return(vec);
}

float VectorHelper::Magnitude(sf::Vector2f vec)
{
	return sqrt(SquareMagnitude(vec)); // If needed, we use this to work with the square root of a magnitude.\
	// This is inefficient, as square root is computationally expensive.
}
