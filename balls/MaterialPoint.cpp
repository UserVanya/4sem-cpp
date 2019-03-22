#include "MaterialPoint.h"
#include <pthread.h>
#include <iostream>

float MaterialPoint::size(const sf::Vector2f&& v) {
	return sqrt(v.x* v.x + v.y * v.y);
}
float MaterialPoint::size(const sf::Vector2f& v) {
	return sqrt(v.x* v.x + v.y * v.y);
}
float MaterialPoint::product(const sf::Vector2f& first, const sf::Vector2f second)
{
	return (first.x * second.x, first.y * second.y);
}
sf::Vector2f MaterialPoint::norm(const sf::Vector2f&& v) {
	return v / size(v);
}
sf::Vector2f MaterialPoint::norm(const sf::Vector2f& v) {
	return v / size(v);
}
void MaterialPoint::setImpulse(std::vector<MaterialPoint>& points, int i, int j) {
	float reducedMass = 1 / points[i].mass + 1 / points[j].mass;
	sf::Vector2f n = norm(points[i].position - points[j].position);
	float imp = product((points[i].velocity - points[j].velocity), n) / reducedMass;
	points[i].velocity += n * (imp / points[i].mass);
	points[j].velocity -= n * (imp / points[j].mass);
	return;
}
MaterialPoint::MaterialPoint()
{
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

void MaterialPoint::updatePosition(float dt, std::vector<MaterialPoint>& points)
{
	velocity = acceleration;
	getAcceleration(points);
	shape.setPosition(shape.getPosition() + velocity + acceleration * dt);
	position = position + velocity + acceleration * dt;
}
void MaterialPoint::getAcceleration(std::vector <MaterialPoint>& points) {
	for (int i = 0; i < (int)points.size(); i++) {
		for (int j = 0; j < (int)points.size(); j++) {
			if (j != i) {
				if (MaterialPoint().size(points[i].position - points[j].position) < (points[i].radius + points[j].radius)) {
					//std::cout << "before" << points[i].velocity.x << " " << points[i].velocity.x << std::endl;
					MaterialPoint().setImpulse(points, i, j);
					//std::cout << "after" << points[i].velocity.x << " " << points[i].velocity.x << std::endl;
				}
			}
		}
	}
	acceleration = sf::Vector2f(0, 0);
	for (int i = 0; i < points.size(); i++) {
		if ((position - points[i].position) != sf::Vector2f(0, 0)){
			float d = size(position - points[i].position);
			acceleration -= (position - points[i].position) * points[i].mass / pow(d, 3);
		}
	}
}

