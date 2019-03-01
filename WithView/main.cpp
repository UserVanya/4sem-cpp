#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <map>
#include "toDisplay.h"
#include <time.h>
#include "map.h"
using namespace sf;


int main()
{
	View view;
	float position = 0;
	toDisplay map("map.png", 1, 1);
	Clock clock;
	toDisplay player("NPC_test.png", Color(255, 255, 255), 3, 3, Vector2i(16, 0), Vector2i(16, 32));
	player.setSpritePosition(Vector2f(320, 240));
	RenderWindow window(VideoMode(640, 480), "SFMLworks");
	view.reset(FloatRect(0, 0, 640, 480));
	float scale = 1.0f;
	float currScale = scale;
	Sprite tmp;
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		currScale = scale + (currScale - scale) * exp(-3e+0f * clock.getElapsedTime().asSeconds());
		clock.restart();
		time /= 800;
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) window.close();
			if (Keyboard::isKeyPressed(Keyboard::Up)) player.go(up, time, 0.5, position, view, tmp);
			if (Keyboard::isKeyPressed(Keyboard::Down)) player.go(down, time, 0.5, position, view, tmp);
			if (Keyboard::isKeyPressed(Keyboard::Left)) player.go(left, time, 0.5, position, view, tmp);
			if (Keyboard::isKeyPressed(Keyboard::Right)) player.go(right, time, 0.5, position, view, tmp);
		}
		view.zoom(currScale);
		window.setView(view);
		window.clear();
		for (int i = 0; i < H; i++)
		{
			for (int j = 0; j < W; j++)
			{
				if (TileMap[i][j] == '0') map.cut(Vector2i(64, 0), Vector2i(32, 32));
				if (TileMap[i][j] == ' ') map.cut(Vector2i(0, 0), Vector2i(32, 32));
				map.setSpritePosition(Vector2f(j * 32, i * 32));
				window.draw(map.getSprite());
			}
		}
		window.draw(player.getSprite());
		window.display();
	}
	return 0;
}