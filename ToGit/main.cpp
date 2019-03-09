#include <SFML/Graphics.hpp>
#include "Worm.h"
#include "ToDraw.h"
#include <ctime>
#include <iostream>;
using namespace sf;
int main()
{
	std::cout << Stay << std::endl;
	ToDraw map("map.png", Color::Black);
	ToDraw background("background.jpg", Color::Black, map);
	RenderWindow window(VideoMode(800, 400), "My Window");
	std::string pathToDemon = "Demon.jpg";
	Worm player1(pathToDemon, sf::Vector2f(113, 112.5));
	int toMove = 0;
	Clock clock;
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) window.close();
			if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();
			if (Keyboard::isKeyPressed(Keyboard::Left)) toMove = Left;
			else if (Keyboard::isKeyPressed(Keyboard::Right)) toMove = Right;
			else toMove == Stay;
		}
		window.clear(Color::White);
		window.draw(background.getSprite());
		window.draw(map.getSprite());
		player1.update(window, toMove, time, map.getImage());

		window.display();
	}
}