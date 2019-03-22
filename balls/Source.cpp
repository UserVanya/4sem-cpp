#include <iostream>
#include <SFML/Graphics.hpp>
#include "MaterialPoint.h"

int main(){
	sf::RenderWindow window(sf::VideoMode(800, 400), "MyWindow");
	
	sf::Clock clock;
	std::vector<MaterialPoint> mass;
	while (window.isOpen()) {
		float time = clock.getElapsedTime().asMicroseconds();
		time /= 800;
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
		}
		
		window.clear(sf::Color::Red);
		for (int i = 0; i < (int)mass.size(); i++) {
			mass[i].updatePosition(time, mass);
			window.draw(mass[i].shape);
		}
		window.display();
	}
}