#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
const bool positive = 1, negative = 0;
class PointCharge
{
private:
	CircleShape pointCharge_;
	const float radius_ = 10;
	bool charge_;
public:
	PointCharge();
	PointCharge(const Vector2f& position, const bool& charge, const RenderWindow& window);
	~PointCharge();
	Vector2f getCenter(const RenderWindow& window);
	CircleShape& getCircle();
	float getCharge();
};

