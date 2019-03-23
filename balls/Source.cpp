#include <iostream>
#include <SFML/Graphics.hpp>
#include "MaterialPoint.h"
#include <random>
void setRandom(std::vector<MaterialPoint>& tmp) {
	srand(time(0));
	for (int i = 0; i < tmp.size(); i++) {
		float a = 50 - rand() % 100, b =  50 - rand() % 100;
		tmp[i].velocity = MaterialPoint().norm(sf::Vector2f(a, b));
	}
}

int main(){
	sf::RenderWindow window(sf::VideoMode(800, 400), "MyWindow");
	
	sf::Clock clock;
	std::vector<MaterialPoint> mass;
	while (window.isOpen()) {
		float time = (float)clock.getElapsedTime().asMicroseconds();
		time /= 4000;
		clock.restart();
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				MaterialPoint tmp(mass, window);
				if (tmp.isCreated) {
					mass.push_back(tmp);
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::V)) {
				setRandom(mass);
			}
		}

		for (int i = 0; i < (int)mass.size(); i++) {
			mass[i].updatePosition(time, mass, window);
		}
		window.clear(sf::Color::Red);
		for (int i = 0; i < (int)mass.size(); i++) {
			window.draw(mass[i].shape);
		}
		window.display();
	}
}