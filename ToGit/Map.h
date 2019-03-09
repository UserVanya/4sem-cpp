#pragma once
#include <SFML/Graphics.hpp>
class Map
{
private:
	sf::Image _image;
	sf::Texture _texture;
	sf::Sprite _sprite;
	std::vector<sf::Vector2f> _bound;
public:
	Map();
	~Map();
	sf::Image getImage() const { return _image; };
};

