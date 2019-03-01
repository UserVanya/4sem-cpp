#pragma once
#include "toDisplay.h"
//#include "map.h"
toDisplay::toDisplay()
{
	initialized_ = false;
}
toDisplay::toDisplay(const std::string& path, const Color& toMask, const float& xScale, const float& yScale)
{
	if (!image_.loadFromFile(path))
	{
		std::cerr << "can`t load file" << std::endl;
		return;
	}
	initialized_ = true;
	image_.createMaskFromColor(toMask);
	texture_.loadFromImage(image_);
	sprite_.setTexture(texture_);
	sprite_.setScale(xScale, yScale);
}
toDisplay::toDisplay(const std::string& path, const float& xScale, const float& yScale, const Vector2i& from,
																						const Vector2i& size)
{
	if (!image_.loadFromFile(path))
	{
		std::cerr << "can`t load file" << std::endl;
		return;
	}
	initialized_ = true; 
	texture_.loadFromImage(image_);
	sprite_.setTexture(texture_);
	sprite_.setScale(xScale, yScale);
	IntRect toRect(from, size);
	sprite_.setTextureRect(toRect);
}
toDisplay::toDisplay(const std::string& path, const Color& toMask, const float& xScale, const float& yScale,
	const Vector2i& from, const Vector2i& size)
{
	if (!image_.loadFromFile(path))
	{
		std::cerr << "can`t load file" << std::endl;
		return;
	}
	initialized_ = true;
	image_.createMaskFromColor(toMask);
	texture_.loadFromImage(image_);
	sprite_.setTexture(texture_);
	sprite_.setScale(xScale, yScale);
	IntRect toRect(from, size);
	sprite_.setTextureRect(toRect);
}
toDisplay::toDisplay(const std::string& path, const float& xScale, const float& yScale)
{
	if (!image_.loadFromFile(path))
	{
		std::cerr << "can`t load file" << std::endl;
		return;
	}
	initialized_ = true; 
	texture_.loadFromImage(image_);
	sprite_.setTexture(texture_);
	sprite_.setScale(xScale, yScale);
}
bool toDisplay::isTextureOnMap(const Vector2f& from, const Vector2f& size)
{
	const float Pi = 3.14159f;
	Vector2f s = sprite_.getPosition();
	Vector2u t (16, 32);
	std::cout << t.x << std::endl;
	t.x *= sprite_.getScale().x;
	t.y *= sprite_.getScale().y;
	std::cout << t.x << std::endl;
	float angle = sprite_.getRotation() / 180 * Pi;
	Vector2f ul = s, ur(s.x + t.x * cos(angle), s.y + t.x * sin(angle));
	Vector2f dl(s.x - t.y * sin(angle), s.y + t.y * cos(angle)), dr(dl.x + t.x * cos(angle), dl.y + t.y * sin(angle));
	std::cout << from.y + size.y << "  " << dr.y << std::endl;
	bool tmpLeft = (dl.x < from.x) || (ul.x < from.x) || (ur.x < from.x) || (dr.x < from.x);
	bool tmpUp = (dl.y < from.y) || (ul.y < from.y) || (ur.y < from.y) || (dr.y < from.y);
	bool tmpRight = (dl.x > (from.x + size.x)) || (ul.x > (from.x + size.x)) || (ur.x > (from.x + size.x)) || (dr.x > (from.x + size.x));
	bool tmpDown = (dl.y > (from.y + size.y)) || (ul.y > (from.y + size.y)) || (ur.y > (from.y + size.y)) || (dr.y > (from.y + size.y));
	std::cout << "left:" << tmpLeft << std::endl << "right:" << tmpRight << std::endl << "up:" << tmpUp << std::endl << "down" << tmpDown << std::endl;
	if (tmpLeft || tmpRight || tmpUp || tmpDown) return false;
	else return true;
}
Sprite& toDisplay::getSprite()
{
	if (initialized_) return sprite_;
	else
	{
		std::cerr << "object didn't initialized" << std::endl;
		exit(0);
	}
}
void toDisplay::cut(const Vector2i& from, const Vector2i& size)
{
	if (initialized_) sprite_.setTextureRect(IntRect(from,size));
	else return;
}
void toDisplay::setSpritePosition(const Vector2f& tmp)
{
	if (initialized_) sprite_.setPosition(tmp);
	else return;
}
void toDisplay::go(const int& direction, const float& time, const float& speed, float& frame, View& view, Sprite& tmp2)
{
	frame += 0.03 * time;
	if (frame > 4) frame -= 4;
	bool a = isTextureOnMap(Vector2f(32, 16), Vector2f(32 * 38, 32 * 24 - 10));
	if (a)
	{
		tmp2 = sprite_;
		switch (direction)
		{
		case down:
		{
			sprite_.move(0, speed * time);
			sprite_.setTextureRect(IntRect(Vector2i((int)frame * 16, down * 32), Vector2i(16, 32)));
			break;
		}
		case up:
		{
			sprite_.move(0, (-1) * speed * time);
			sprite_.setTextureRect(IntRect(Vector2i((int)frame * 16, up * 32), Vector2i(16, 32)));
			break;
		}
		case left:
		{
			sprite_.move((-1) * speed * time, 0);
			sprite_.setTextureRect(IntRect(Vector2i((int)frame * 16, left * 32), Vector2i(16, 32)));
			break;
		}
		case right:
		{
			sprite_.move(speed * time, 0);
			sprite_.setTextureRect(IntRect(Vector2i((int)frame * 16, right * 32), Vector2i(16, 32)));
			break;
		}
		}
	}
	else sprite_ = tmp2;
	Vector2f tmp = sprite_.getPosition();
	//std::cout << tmp.x << " " << tmp.y << std::endl;
	if ((tmp.x < 320 || tmp.x > 960) && (tmp.y > 240) && (tmp.y < 560)) view.setCenter(view.getCenter().x, tmp.y);
	else if ((tmp.y < 240 || tmp.y > 560) && (tmp.x > 320) && (tmp.x < 960)) view.setCenter(tmp.x, view.getCenter().y);
	else if ((tmp.y < 240 || tmp.y > 560) || (tmp.x < 320 || tmp.x > 960)) view.setCenter(view.getCenter());
	else view.setCenter(tmp);
	 
}