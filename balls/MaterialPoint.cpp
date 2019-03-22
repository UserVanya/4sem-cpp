#include "MaterialPoint.h"
#include <pthread.h>
#include <iostream>
MaterialPoint::MaterialPoint()
{
}

float MaterialPoint::size(const sf::Vector2f&& v) {
	return sqrt(v.x* v.x + v.y * v.y);
}
float MaterialPoint::size(const sf::Vector2f& v) {
	return sqrt(v.x* v.x + v.y * v.y);
}

MaterialPoint::MaterialPoint(const std::vector<MaterialPoint>& pointsAlreadyInWindow, const sf::RenderWindow& window)
{
	radius = 10;
	mass = 10;
	shape.setRadius(radius);
	shape.setFillColor(sf::Color::Green);
	position = (sf::Vector2f)sf::Mouse::getPosition(window);
	if (oneOfPointsInThisOne(pointsAlreadyInWindow)) {
		isCreated = false;
		this->~MaterialPoint();
	}
	else {
		isCreated = true;
		shape.setPosition(position - sf::Vector2f(radius, radius));
	}
}
bool MaterialPoint::oneOfPointsInThisOne(const std::vector<MaterialPoint>& pointsAlreadyInWindow) {
	for (int i = 0; i < (int)pointsAlreadyInWindow.size(); i++) {
		if (size(position - pointsAlreadyInWindow[i].position) < (radius + pointsAlreadyInWindow[i].radius)) {
			return true;
		}
	}
	return false;
}

MaterialPoint::~MaterialPoint()
{
	radius = 0;
	mass = 0;
}

void MaterialPoint::updatePosition(float dt, const std::vector<MaterialPoint>& points)
{
	velocity = acceleration;
	getAcceleration(points);
	shape.setPosition(shape.getPosition() + velocity + acceleration * dt);
	position = position + velocity + acceleration * dt;
}
void MaterialPoint::getAcceleration(const std::vector <MaterialPoint>& points) {

	acceleration = sf::Vector2f(0, 0);
	for (int i = 0; i < points.size(); i++) {
		if ((position - points[i].position) != sf::Vector2f(0, 0)){
			float d = size(position - points[i].position);
			acceleration -= (position - points[i].position) * points[i].mass / pow(d, 3);
		}
	}
}
sf::Vector2f MaterialPoint::GetImpulse() const
{

	return sf::Vector2f();
}

