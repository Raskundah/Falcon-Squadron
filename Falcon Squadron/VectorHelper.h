#pragma once
#include <SFML/System.hpp>
namespace VectorHelper
{
	float Magnitude(sf::Vector2f vec); // get a vector's magnitude.

	float SquareMagnitude(sf::Vector2f vec); // get the square of the magnitude.

	sf::Vector2f Normalise(sf::Vector2f vec); // find the normal of the vector.
}