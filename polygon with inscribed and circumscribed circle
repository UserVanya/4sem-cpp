#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
using namespace sf;

int main()
{
	int n;
	std::cin >> n;
	float radius = 100 * cos(3.1415926535/n);
	std::cout << radius << std::endl;
	RenderWindow window(VideoMode(400, 400), "SFMLworks");
	

	CircleShape circle1(100, n);
	circle1.setOutlineThickness(2);
	circle1.setFillColor(sf::Color::Transparent);
	circle1.setOutlineColor(sf::Color(250, 150, 100));
	circle1.setPosition(100, 100);
	CircleShape circle2(100, 300);
	circle2.setFillColor(sf::Color::Transparent);
	circle2.setOutlineThickness(2);
	circle2.setOutlineColor(sf::Color(250, 150, 100));
	circle2.setPosition(100, 100);
	CircleShape circle3(radius, 300);
	circle3.setFillColor(sf::Color::Transparent);
	circle3.setOutlineThickness(3);
	circle3.setOutlineColor(sf::Color(250, 150, 100));
	circle3.setPosition(100 + 100 - radius, 100 + 100 - radius);


	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(circle1);
		window.draw(circle2);
		window.draw(circle3);
		window.display();
	}

	return 0;
}
