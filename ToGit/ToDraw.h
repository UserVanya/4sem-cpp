#pragma once
#include <SFML/Graphics.hpp>
class ToDraw
{
private:
	sf::Image _image;
	sf::Texture _texture;
	sf::Sprite _sprite;
public:
	ToDraw();
	ToDraw(const std::string& pathToFile, const sf::Color& toMask);
	ToDraw(const std::string& pathToFile, const sf::Color& toMask, ToDraw& tmp);
	const sf::Sprite getSprite() const { return _sprite; };
	const sf::Texture getTexture() const { return _texture; };
	~ToDraw();
	sf::Image getImage() const { return _image; };
};

