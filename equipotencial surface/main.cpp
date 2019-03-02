#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <map>
#include <time.h>
#include "PointCharge.h"
#include <set>
#include "PointInfo.h"
using namespace sf;
std::vector<RectangleShape> equipotencialCurve(std::vector<PointCharge>& charge,
const Vector2f& pos, const RenderWindow& window, std::vector<PointInfo>& pointInfo)
{
	PointInfo curr(pos);
	std::vector<RectangleShape> curve;
	curve.push_back(RectangleShape(Vector2f(5, 5)));
	curve[curve.size() - 1].setFillColor(Color::Red);
	curve[curve.size() - 1].setPosition(pos.x, pos.y);
	curr.calculatePotential(charge, window);
	for (float i = 1; i < window.getSize().y; i++)
	{
		for (float j = 1; j < window.getSize().x; j++)
		{
			std::set<float> tmp;
			tmp.insert(pointInfo[i * window.getSize().x + j].getPotential());
			tmp.insert(pointInfo[i * window.getSize().x + (j - 1)].getPotential());
			tmp.insert(pointInfo[(i - 1) * window.getSize().x + j].getPotential());
			tmp.insert(pointInfo[(i - 1) * window.getSize().x + (j - 1)].getPotential());
			auto it1 = tmp.begin();
			auto it2 = --tmp.end();
			if ((*it1 < curr.getPotential()) && (*it2 > curr.getPotential()))
			{
				curve.push_back(RectangleShape(Vector2f(1, 1)));
				curve[curve.size() - 1].setFillColor(Color::White);
				curve[curve.size() - 1].setPosition(j - 1, i - 1);
			}
		}
	}
	return curve;
}
void infoInit(std::vector<PointInfo>& pointInfo, const RenderWindow& window)
{
	for (int i = 0; i < window.getSize().y; i++)
	{
		for (int j = 0; j < window.getSize().x; j++)
		{
			pointInfo.push_back(PointInfo(Vector2f(j, i)));
		}
	}
}
int main()
{
	RenderWindow window(VideoMode(600, 600), "SFMLworks");
	window.setFramerateLimit(300);
	std::vector<PointCharge> charge;
	std::vector<RectangleShape> curve;
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			std::vector<PointInfo> pointInfo;
			infoInit(pointInfo, window);
			if (event.type == Event::Closed) window.close();
			if (Keyboard::isKeyPressed(Keyboard::P))
				charge.push_back(PointCharge((Vector2f)Mouse::getPosition(window), positive, window));
			if (Keyboard::isKeyPressed(Keyboard::N))
				charge.push_back(PointCharge((Vector2f)Mouse::getPosition(window), negative, window));
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				curve.clear();
				for (int i = 0; i < window.getSize().x * window.getSize().y; i++)
					pointInfo[i].calculatePotential(charge, window);
				curve = equipotencialCurve(charge, (Vector2f)Mouse::getPosition(window), window, pointInfo);
			}
		}
		for (int i = 0; i < charge.size(); i++)
			window.draw(charge[i].getCircle());
		for (int i = 0; i < curve.size(); i++)
			window.draw(curve[i]);
		window.display();
	}
}