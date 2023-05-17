#include "Physics.h"
#include"VectorHelper.h"
#include <algorithm>
#include "SpriteObject.h"

Physics::Physics()
    : m_twoFramesOldPos()
    , m_velocity()
    , m_acceleration(100, 100)
    ,  m_Colliding(false)
    , m_CollisionOffset(0, 0)
    , m_CollisionScale(1, 1)
    , m_IsAlive(true)
    , collisionType(CollisionType::AABB)
    , m_Position(0, 0)
    , m_sprite()
{
}

void Physics::Update(sf::Time _frameTime)
{
}

void Physics::HandleCollision(Physics& other)
{

    // parent method for handling collision in child classes.
}


bool Physics::CheckCollision(Physics other)
{
    if(!m_IsAlive || !other.m_IsAlive) //this checks if either object should care abot colliding. if dead, it doesn't collide.

    return false;

    switch (collisionType)
    {
    case CollisionType::CIRCLE:
    {
        if (other.collisionType == CollisionType::CIRCLE)
        {
            //generate a vector representing the displacement between the circles.
            sf::Vector2f displacementVector = GetCollisionCentre() - other.GetCollisionCentre();

            //generate the magnitude of the vector that is the distance between the circle centres.
            float squareDistance = VectorHelper::SquareMagnitude(displacementVector);

            //compare this to the radia of both circles.

            float radiusOfCollision = GetCircleCollisionRadius() + other.GetCircleCollisionRadius();

            return squareDistance <= radiusOfCollision * radiusOfCollision;
        }

        else
        {
            //if previous if statement doesn't run, we're working with circle to AABB
            sf::Vector2f nearestPoint = GetCollisionCentre(); //assign the position of circles centre.

            sf::FloatRect otherAABB = other.GetAABB(); //assign the AABB box of collision target 

            //clamp the circle centre to the min and max of that AABB.
            nearestPoint.x = fmaxf(otherAABB.left, fminf(nearestPoint.x, otherAABB.left + otherAABB.width));
            nearestPoint.y = fmaxf(otherAABB.top, fmin(nearestPoint.y, otherAABB.top + otherAABB.height));

            sf::Vector2f displacement = nearestPoint - GetCollisionCentre(); //generatea displacement vector.

            float squareDistance = VectorHelper::SquareMagnitude(displacement);
            float circleRadius = GetCircleCollisionRadius();

            return squareDistance <= circleRadius * circleRadius;

        }
    }
    break;

    case CollisionType::AABB:
    {
        if (other.collisionType == CollisionType::AABB) //AABB colliding with AABB, very simple in SFML.
        {
            return GetAABB().intersects(other.GetAABB());
        }
        else
            //AABB colliding with circle.
        {
            sf::Vector2f nearestPoint = other.GetCollisionCentre(); //get the collision target's circle collider centre.

            sf::FloatRect thisAABB = GetAABB(); //reducing function calls since clamping requires six.

            nearestPoint.x = fmaxf(thisAABB.left, fminf(nearestPoint.x, thisAABB.left + thisAABB.width));
            nearestPoint.y = fmaxf(thisAABB.top, fmin(nearestPoint.y, thisAABB.top + thisAABB.height));

            sf::Vector2f displacement = nearestPoint - other.GetCollisionCentre();

            float squareDistance = VectorHelper::SquareMagnitude(displacement);
            float circleRadius = other.GetCircleCollisionRadius();

            return squareDistance <= circleRadius * circleRadius;
        }
    }
    break;
    default:
        return false;
        break;
    }
}

void Physics::SetColliding(bool newColliding)
{
    m_Colliding = newColliding; // sets collision flag.
}

sf::Vector2f Physics::GetCOllisionDepth(Physics other)
{
    sf::FloatRect thisAABB = GetAABB();
    sf::FloatRect otherAABB = other.GetAABB(); 

    sf::Vector2f thisCentre = GetCollisionCentre();
    sf::Vector2f otherCentre = GetCollisionCentre();

    sf::Vector2f minDistance;
    minDistance.x = thisAABB.width * 0.5f + otherAABB.width * 0.5f;
    minDistance.y = thisAABB.height * 0.5f + otherAABB.height * 0.5f;

    sf::Vector2f realDistance = otherCentre - thisCentre;

    if (realDistance.x < 0)
        minDistance.x = -minDistance.x; //converts the distance into negative where required.
    if (realDistance.y < 0)
        minDistance.y = -minDistance.y;

    return realDistance - minDistance;
}

void Physics::SetAlive(bool _alive)
{
    m_IsAlive = _alive; //sets the alive flag
}

sf::Vector2f Physics::GetCollisionCentre()
{
    sf::Vector2f centre = m_Position; //gets the object of the child class calling this function.

    sf::FloatRect bounds = m_sprite.getGlobalBounds(); // generates a vector of the top and left bounds of sprite.

    centre.x += bounds.width * 0.5f;
    centre.y += bounds.height * 0.5f;

    centre.x += m_CollisionOffset.x;
    centre.y += m_CollisionOffset.y;

    return centre;
}

float Physics::GetCircleCollisionRadius()
{
    sf::FloatRect bounds = m_sprite.getGlobalBounds();

    bounds.width *= m_CollisionScale.x;
    bounds.height *= m_CollisionScale.y;

    if (bounds.width > bounds.height)
    {
        return bounds.width * 0.5f;
    }
    else
        return bounds.height * 0.5f;
}

sf::FloatRect Physics::GetAABB()
{
    sf::FloatRect bounds = m_sprite.getGlobalBounds();

    bounds.width *= m_CollisionScale.x;
    bounds.height *= m_CollisionScale.y;

    sf::Vector2f centre = GetCollisionCentre();

    bounds.left = centre.x - bounds.width * 0.5f;
    bounds.top = centre.y - bounds.height * 0.5f;

    return bounds;
}
