#include "PointCharge.h"
#include<iostream>


PointCharge::PointCharge() {}
PointCharge::PointCharge(const Vector2f& position, const bool& charge, const RenderWindow& window)
{
	if ((position.x > radius_) && (position.y > radius_) && (position.x + radius_ < window.getSize().x) &&
		(position.y + radius_ < window.getSize().y))
	{
		pointCharge_.setRadius(radius_);
		pointCharge_.setPosition(position.x - radius_, position.y - radius_);
		charge_ = charge;
		if (charge_ == positive) pointCharge_.setFillColor(Color::Red);
		else pointCharge_.setFillColor(Color::Blue);
	}
}
PointCharge::~PointCharge() {}

Vector2f PointCharge::getCenter(const RenderWindow& window)
{
	//std::cout << "radius = "<< radius_ << std::endl;
	Vector2f center(pointCharge_.getPosition().x + radius_, pointCharge_.getPosition().y + radius_);
	return center;
}
CircleShape& PointCharge::getCircle()
{
	return pointCharge_;
}
float PointCharge::getCharge()
{
	if (charge_ == positive) return 1;
	else return -1;
}