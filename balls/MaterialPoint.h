#pragma once
#include "SFML/Graphics.hpp"
#include <pthread.h>

class MaterialPoint
{
public:
	MaterialPoint();
	
	~MaterialPoint();
	void updatePosition(float dt, const std::vector<MaterialPoint>& points);
	sf::Vector2f setImpulse() const;
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	float mass;
	float radius;
	bool isCreated;
	sf::CircleShape shape;
	float size(const sf::Vector2f& v);
	MaterialPoint(const std::vector<MaterialPoint>& pointsAlreadyInWindow, const sf::RenderWindow& window);
	bool oneOfPointsInThisOne(const std::vector<MaterialPoint>& pointsAlreadyInWindow);
	float size(const sf::Vector2f&& v);
	void getAcceleration(const std::vector<MaterialPoint>& points);

};
