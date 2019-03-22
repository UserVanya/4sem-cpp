#pragma once
#include "SFML/Graphics.hpp"
#include <pthread.h>

class MaterialPoint
{
public:
	float size(const sf::Vector2f && v);
	float size(const sf::Vector2f & v);
	float product(const sf::Vector2f & first, const sf::Vector2f second);
	sf::Vector2f norm(const sf::Vector2f && v);
	sf::Vector2f norm(const sf::Vector2f & v);
	void setImpulse(std::vector<MaterialPoint>& points, int i, int j);
	MaterialPoint();
	~MaterialPoint();
	void updatePosition(float dt, std::vector<MaterialPoint>& points);
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	float mass;
	float radius;
	bool isCreated;
	sf::CircleShape shape;
	MaterialPoint(const std::vector<MaterialPoint>& pointsAlreadyInWindow, const sf::RenderWindow& window);
	bool oneOfPointsInThisOne(const std::vector<MaterialPoint>& pointsAlreadyInWindow);
	void getAcceleration(std::vector<MaterialPoint>& points);
};
