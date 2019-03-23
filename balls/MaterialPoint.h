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
	void setImpulse(std::vector<MaterialPoint>& points, int i, int j, float dt);
	MaterialPoint();
	~MaterialPoint();
	void updatePosition(float dt, std::vector<MaterialPoint>& points, const sf::RenderWindow& window);
	sf::Vector2f position;
	sf::Vector2f velocity;
	float mass;
	float radius;
	bool isCreated;
	sf::CircleShape shape;
	MaterialPoint(const std::vector<MaterialPoint>& pointsAlreadyInWindow, const sf::RenderWindow& window);
	bool oneOfPointsInThisOne(const std::vector<MaterialPoint>& pointsAlreadyInWindow);
	void checkForCollisionsAndsetImpulse(std::vector<MaterialPoint>& points, float dt);
};
