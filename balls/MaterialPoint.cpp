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
	return (first.x * second.x + first.y * second.y);
}
sf::Vector2f MaterialPoint::norm(const sf::Vector2f&& v) {
	return v / size(v);
}
sf::Vector2f MaterialPoint::norm(const sf::Vector2f& v) {
	return v / size(v);
}
void MaterialPoint::setImpulse(std::vector<MaterialPoint>& points, int i, int j, float dt) {
	position -= velocity * dt;
	float reducedMass = 1 / points[i].mass + 1 / points[j].mass;
	sf::Vector2f n = norm(points[i].position - points[j].position);
	//std::cout << n.x << " " << n.y << std::endl;
	float imp = 2 * product((points[i].velocity - points[j].velocity), n) / reducedMass;
	points[i].velocity -= n * (imp / points[i].mass);
	points[j].velocity += n * (imp / points[j].mass);
	position = position + velocity * dt;
	return;
}
MaterialPoint::MaterialPoint()
{
}
MaterialPoint::MaterialPoint(const std::vector<MaterialPoint>& pointsAlreadyInWindow, const sf::RenderWindow& window)
{
	radius = 10;
	mass = 1;
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
void checkForPointsOutOfWindow(MaterialPoint& a, const sf::RenderWindow& window, float& dt)
{
	const float Pi = 3.14159f;
	sf::Vector2f s = a.position;
	sf::Vector2u w = window.getSize();
	sf::Vector2f u = s - sf::Vector2f(0, a.radius);
	sf::Vector2f l = s - sf::Vector2f(a.radius, 0);
	sf::Vector2f r = s + sf::Vector2f(a.radius, 0);
	sf::Vector2f d = s + sf::Vector2f(0, a.radius);
	if (u.y < 0 ){
		a.position = a.position - a.velocity * dt;
		a.velocity += sf::Vector2f(0, 1) * abs((MaterialPoint().product(a.velocity, sf::Vector2f(0, 1)) * 2));
		a.position = a.position + a.velocity * dt;
	}
	if (d.y > w.y) {
		a.position = a.position - a.velocity * dt;
		a.velocity += sf::Vector2f(0, -1) * abs((MaterialPoint().product(a.velocity, sf::Vector2f(0, -1)) * 2));
		a.position = a.position + a.velocity * dt;
	}
	if (r.x > w.x) {
		a.position = a.position - a.velocity * dt;
		a.velocity += sf::Vector2f(-1, 0) * abs((MaterialPoint().product(a.velocity, sf::Vector2f(-1, 0)) * 2));
		a.position = a.position + a.velocity * dt;
	}
	if (r.x < 0) {
		a.position = a.position - a.velocity * dt;
		a.velocity += sf::Vector2f(1, 0) * abs((MaterialPoint().product(a.velocity, sf::Vector2f(1, 0)) * 2));
		a.position = a.position + a.velocity * dt;
	}
	
}
void MaterialPoint::updatePosition(float dt, std::vector<MaterialPoint>& points, const sf::RenderWindow& window)
{
	position = position + velocity * dt;
	for (int i = 0; i < points.size(); i++) {
		checkForPointsOutOfWindow(points[i], window, dt);
	}
	checkForCollisionsAndsetImpulse(points, dt);
	shape.setPosition(shape.getPosition() + velocity * dt);
}
void MaterialPoint::checkForCollisionsAndsetImpulse(std::vector <MaterialPoint>& points, float dt) {
	for (int i = 0; i < (int)points.size(); i++) {
		for (int j = 0; j < (int)points.size(); j++) {
			if (j != i) {
				if(size(points[i].position - points[j].position) < (points[i].radius + points[j].radius)) {
					setImpulse(points, i, j, dt);
				}
			}
		}
	}
}

