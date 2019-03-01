#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
using namespace sf;
class toDisplay
{
public:
	toDisplay();
	toDisplay(const std::string& path, const Color& toMask, const float& xScale, const float& yScale);
	toDisplay(const std::string& path, const float& xScale, const float& yScale);
	toDisplay(const std::string& path, const float& xScale, const float& yScale, const Vector2i& from,
																				 const Vector2i& size);
	toDisplay(const std::string& path, const Color& toMask, const float& xScale, const float& yScale, 
				const Vector2i& from, const Vector2i& size);
	bool isTextureOnMap(const Vector2f& from, const Vector2f& size);
	Sprite& getSprite();
	void cut(const Vector2i& from, const Vector2i& size);
	void setSpritePosition(const Vector2f& tmp);
	void go(const int& direction, const float& time, const float& speed, float& frame, View& view, Sprite& tmp2);
private:
	int direction;
	Image image_;
	Texture texture_;
	Sprite sprite_;
	bool initialized_;
};
const int down = 0, right = 1, left = 3, up = 2;
