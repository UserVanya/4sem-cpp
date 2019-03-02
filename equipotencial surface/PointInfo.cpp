#pragma once
#include "PointInfo.h"
#include <string>
#include <iostream>

PointInfo::PointInfo()
{
}


PointInfo::~PointInfo()
{
}

PointInfo::PointInfo(const Vector2f& point)
{
	coords_ = point;
}
void  PointInfo::calculatePotential(std::vector <PointCharge>& charge, const RenderWindow& window)
{
	if (charge.size() != 0)
	{
		for (int i = 0; i < charge.size(); i++)
		{
			float r = size_(coords_ - charge[i].getCenter(window));
			if (r != 0)
				potential_ += charge[i].getCharge() / r ;
			else potential_ = std::string::npos;
		}
	}
}
float PointInfo::getPotential()
{
	return potential_;
}
float PointInfo::size_(const Vector2f& toCalculate)
{
	return sqrt((toCalculate.x * toCalculate.x) + (toCalculate.y * toCalculate.y));
}
