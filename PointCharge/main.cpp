#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <map>
#include <time.h>
#include "PointCharge.h"
using namespace sf;

inline Vector2f getElectricField(const Vector2f& pos, std::vector<PointCharge> & charge, const RenderWindow& window, 
	float inverse)
{
	Vector2f tmp(0, 0);
	for (int i = 0; i < charge.size(); i++)
	{
		Vector2f c = charge[i].getCenter(window);
		float r = (sqrt((pos.x - c.x)*(pos.x - c.x) + (pos.y - c.y)*(pos.y - c.y)));
		tmp += (pos - c) / r / r / r / charge[i].getCharge() / inverse;
	}
	return tmp;
}
bool PositionNotInCurcle(std::vector<PointCharge>& charge, const Vector2f& pos, const RenderWindow& window)
{
	float r;
	for (int i = 0; i < charge.size(); i++)
	{
		float x = charge[i].getCenter(window).x, y = charge[i].getCenter(window).y;
		r = sqrt((pos.x - x)*(pos.x - x) + (pos.y - y)*(pos.y - y));
		if (r < charge[i].getCircle().getRadius()) return false;
	}
	return true;
}
std::vector<RectangleShape> GetPowerLine(std::vector<PointCharge> & charge, const Vector2f& pos, 
	const RenderWindow& window)
{
	Vector2f currentPos = pos;
	Vector2f field(0, 0);
	float inverse = 1;
	std::vector<RectangleShape> curve;
	for (int i = 0; i < 2; i++)
	{
		while ((currentPos.x > 0) && (currentPos.y > 0) && (currentPos.x < window.getSize().x) &&
			(currentPos.y < window.getSize().y) && PositionNotInCurcle(charge, currentPos, window))
		{
			currentPos += field;
			field = getElectricField(currentPos, charge, window, inverse);
			field /= (sqrt(field.x * field.x + field.y * field.y));
			curve.push_back(RectangleShape(Vector2f(1, 1)));
			curve[curve.size() - 1].setFillColor(Color::White);
			curve[curve.size() - 1].setRotation(atan2f(field.x, field.y));
			curve[curve.size() - 1].setPosition(currentPos);
		}
		inverse = -1;
		field.x = 0;
		field.y = 0;
		currentPos = pos;
	}
	currentPos = pos;
	return curve;
}

int main()
{
	RenderWindow window(VideoMode(1350, 600), "SFMLworks");
	std::vector<PointCharge> charge;
	std::vector<RectangleShape> curve;
	int amount = 0;
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) window.close();
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				charge.push_back(PointCharge((Vector2f)Mouse::getPosition(window), positive, window));
			}
			if (Mouse::isButtonPressed(Mouse::Right))
			{
				charge.push_back(PointCharge((Vector2f)Mouse::getPosition(window), negative, window));
			}
			std::cout << "positive:" << amount << std::endl;
			std::cout << "negative:" << charge.size() - amount << std::endl << std::endl;
		}
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			curve = GetPowerLine(charge, (Vector2f)Mouse::getPosition(window), window);
		}
		for (int i = 0; i < charge.size(); i++)
			window.draw(charge[i].getCircle());
		for (int i = 0; i < curve.size(); i++)
			window.draw(curve[i]);
		window.display();
	}
}