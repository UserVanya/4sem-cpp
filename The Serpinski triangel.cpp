#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>
using namespace sf;

void Serp(std::vector <CircleShape> &triangle, int depth, int currDepth, float r)
{
	if (depth <= currDepth) return;
	if (currDepth == 1)
	{
		triangle.push_back(CircleShape(r, 3));
		triangle[0].setOutlineThickness(1);
		triangle[0].setOutlineColor(sf::Color::Green);
		triangle[0].setFillColor(sf::Color::Transparent);
		if (depth <= currDepth) return;
		Serp(triangle, depth, 2, (r / 2));
	}
	else
	{
		int lastOfThree = triangle.size() - 1;
		Vector2f pos = triangle[lastOfThree].getPosition();
		for (int i = 0; i < 3; i++)
		{
			triangle.push_back(CircleShape(r, 3));
			Vector2f tmp;
			if (i == 0)
			{
				tmp.x = pos.x + r;
				tmp.y = pos.y;
			}
			if (i == 1)
			{
				tmp.x = pos.x + r - r * sqrt(3) / 2;
				tmp.y = pos.y + 3 * r / 2;
			}
			if (i == 2)
			{
				tmp.x = pos.x + r + r * sqrt(3) / 2;
				tmp.y = pos.y + 3 * r / 2;
			}
			int last = triangle.size() - 1;
			triangle[last].setPosition(tmp);
			triangle[last].setFillColor(sf::Color::Transparent);
			triangle[last].setOutlineThickness(1);
			triangle[last].setOutlineColor(sf::Color::Green);
			Serp(triangle, depth, currDepth + 1, (r / 2));
		}
		return;
	}
	
}

int main()
{	
	std::vector<CircleShape> triangle;
	std::vector<CircleShape> &triangleAddr = triangle;
	int depth;
	float r;
	std::cout << "Enter depth:";
	std::cin >> depth;
	std::cout << "Enter radius:";
	std::cin >> r;

	Serp(triangleAddr, depth + 1, 1, r);
	std::cout << triangle.size() << std::endl;
	RenderWindow window(VideoMode(1000, 800), "SFMLworks");
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		window.clear();
		for (int i = 0; i < triangle.size(); i++) window.draw(triangle[i]);
		window.display();
	}
	return 0;
}
