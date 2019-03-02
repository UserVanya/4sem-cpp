#pragma once
#include <SFML/Graphics.hpp>
#include "PointCharge.h"
using namespace sf;
class PointInfo
{
	Vector2f coords_;
	float potential_;
	float size_(const Vector2f& toCalculate);
public:
	PointInfo();
	~PointInfo();
	PointInfo(const Vector2f& point);
	void calculatePotential(std::vector <PointCharge>& charge, const RenderWindow& window);
	float getPotential();

};

