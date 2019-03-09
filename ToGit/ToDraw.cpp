#include "ToDraw.h"
#include <iostream>


ToDraw::ToDraw()
{
}

ToDraw::ToDraw(const std::string & pathToFile, const sf::Color & toMask)
{
	_image.loadFromFile(pathToFile);
	_image.createMaskFromColor(toMask);
	_texture.loadFromImage(_image);
	_texture.setSmooth(true);
	_sprite.setTexture(_texture);
}

ToDraw::ToDraw(const std::string & pathToFile, const sf::Color & toMask, ToDraw& tmp)
{
	_image.loadFromFile(pathToFile);
	_image.createMaskFromColor(toMask);
	_texture.loadFromImage(_image);
	_texture.setSmooth(true);
	float kx = tmp.getTexture().getSize().x / _texture.getSize().x,
		ky = tmp.getTexture().getSize().y / _texture.getSize().y;
	_sprite.setTexture(_texture);
	_sprite.setScale(kx, ky);
}


ToDraw::~ToDraw()
{
}
