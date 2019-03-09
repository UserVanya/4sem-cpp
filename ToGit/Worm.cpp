#include "Worm.h"



void Worm::_maskFromWhite()
{
	int CodesOfColorsNearWhite = 20;
	for (int i = 0; i < CodesOfColorsNearWhite; i++)
		for (int j = 0; j < CodesOfColorsNearWhite; j++)
			for (int k = 0; k < CodesOfColorsNearWhite; k++)
				_image.createMaskFromColor(sf::Color(255 - i, 255 - j, 255 - k));
}

void Worm::_jumpBack(sf::RenderWindow & window, const float& time, const sf::Image& map)
{
	
	/*
	
	*/
}

void Worm::_jumpForward(sf::RenderWindow & window, const float& time, const sf::Image& map)
{

}

void Worm::_goOneSide(sf::RenderWindow & window, const float& time, const sf::Image& map, const int& reverse)
{
	_setVariantsToGo();
	int angelToFinish, angelToStart;
	if (reverse == 1) //go left(pictures ate oriented to the left)
	{
		angelToStart = 0;
		angelToFinish = MAX_ANGEL;
	}
	else //go right
	{
		angelToStart = 359;
		angelToFinish = 359 - MAX_ANGEL;
	}

	_dir = sf::Vector2f(0, 0);
	_fall = false;
	int i = 0;
	for (i = angelToStart; i < angelToFinish && _dir != _variantsToGo[i] && !_fall; i++)
	{
		if (map.getPixel(_variantsToGo[0].x, _variantsToGo[0].y) == sf::Color::White) //isFalling(const sf::Image& map);
			_fall = true;
		if (map.getPixel(_variantsToGo[i].x, _variantsToGo[i].y) == sf::Color::White) //freeDirectionIsFound(const sf::Image& map, int & i);
			_dir = _variantsToGo[i];
	}

	_readyToGo = true;
	
	for (i; i < angelToFinish && !_fall; i++)
	{
		if (map.getPixel(_variantsToGo[i].x, _variantsToGo[i].y) != sf::Color::White) // remainingPathIsFree(const sf::Image& map);
			_readyToGo == false;                                                      // vector<>, start, finish;
	}
	float norm = sqrt(_dir.x * _dir.x + _dir.y *_dir.y); // norm(vector2f);
	_dir /= norm;
	if (_readyToGo)
	{
		sf::Vector2f tmp = _toRecognize.getPosition();
		if (!_fall)
		{
			if (_lastDirection == Left || _lastDirection == Right)
				_runningFrame += time / 800;
			else
				_runningFrame = 0;
			if (_runningFrame > AMOUNT_OF_FRAMES_IN_LINE)
				_runningFrame = 0;
			_sprite[(int)_runningFrame].setPosition((tmp - SHIFT) + _dir * (time/TIME_K));
			_sprite[(int)_runningFrame].setScale(reverse, 1);
			window.draw(_sprite[(int)_runningFrame]);
			if (reverse == 1)
				_lastDirection = Left;
			else
				_lastDirection = Right;
		}
		else
		{
			_sprite[7].setPosition((tmp - SHIFT) + _dir * (time / TIME_K));
			window.draw(_sprite[(int)_runningFrame]);
			_lastDirection = fall;
		}
	}
}

void Worm::_stay(sf::RenderWindow & window, const float & time, const sf::Image & map)
{
	_setVariantsToGo();
	if (map.getPixel(_variantsToGo[0].x, _variantsToGo[0].y) != sf::Color::White)
	{
		_stayingFrame += time / 800;
	if(_stayingFrame > 6)
		_stayingFrame = 3;
	_sprite[(int)_stayingFrame].setPosition((tmp - SHIFT) + _dir * (time / TIME_K));
	_sprite[(int)_stayingFrame].setScale(reverse, 1);
	window.draw(_sprite[(int)_stayingFrame]);
		_sprite[(int)_runningFrame].setPosition((tmp - SHIFT) + _dir * (time / TIME_K));
	}
}



void Worm::_setVariantsToGo()
{
	for (int i = 0; i < 360; i++)
	{
		sf::Vector2f center = _toRecognize.getPosition() + sf::Vector2f(RADIUS, RADIUS);
		_variantsToGo[i] = center + RADIUS * sf::Vector2f(cos(90 + i), sin(90 + i));
	}
}

Worm::Worm()
{
}

Worm::Worm(std::string pathToImage, sf::Vector2f size)
{
	_image.loadFromFile(pathToImage);
	_maskFromWhite();
	_texture.loadFromImage(_image);
	_texture.setSmooth(true);
	_sprite.resize(AMOUNT_OF_LINES_ON_PICTURE * AMOUNT_OF_FRAMES_IN_LINE);
	for (int i = 0; i < AMOUNT_OF_LINES_ON_PICTURE; i++)
		for (int j = 0; j < AMOUNT_OF_FRAMES_IN_LINE; j++)
		{
	
			_sprite[i * AMOUNT_OF_LINES_ON_PICTURE + j].setTexture(_texture);
			
			sf::IntRect tmp(sf::Vector2i(size.x * i, size.y * j), sf::Vector2i(size.x, size.y));
			_sprite[i * AMOUNT_OF_LINES_ON_PICTURE + j].setTextureRect(tmp);
		}
	
	_toRecognize.setPosition(_sprite[0].getPosition() + SHIFT);
	_toRecognize.setRadius(RADIUS);
	_toRecognize.setFillColor(sf::Color::Transparent);
	_dir = sf::Vector2f(0, 0);
	_stayingFrame = 0;
	_runningFrame = 0;
	_lastDirection = 0;
	_variantsToGo.resize(360);
}



Worm::~Worm()
{
}

void Worm::update(sf::RenderWindow & window, int direction, const float& time, const sf::Image& map)
{
	if (_isJumping) 
	{
		switch (direction)
		{
		case LeapBack:
			_jumpBack(window, time, map);
		case LeapForward:
			_jumpForward(window, time, map);
		} 
	}
	else
	{
		switch (direction)
		{
		case Stay:
			_stay(window, time, map, 1);
			break;
		case Left:
			_goOneSide(window, time, map, 1);
			break;
		case Right:
			_goOneSide(window, time, map, 1);
			break;
		case LeapForward:
			_jumpForward(window, time, map);
			break;
		case LeapBack:
			_jumpBack(window, time, map);
			break;
		}
	}
}

void Worm::draw(sf::RenderWindow & window, sf::Sprite & toDraw)
{
	toDraw = _sprite[0];
	window.draw(toDraw);
	window.draw(_toRecognize);
}

void Worm::draw(sf::RenderWindow & window)
{
	window.draw(_sprite[1]);
	window.draw(_toRecognize);
}


