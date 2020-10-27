#pragma once
#include <string>
class KC
{
public:
	int id;
	std::string Name = " ";
	int workshopCount = 0;
	int workingWorkshopCount = 0;
	double efficiency = 0;

	friend std::istream& operator >> (std::istream& in, KC& newKC);
	friend std::ostream& operator<<(std::ostream& out, const KC& kc);
};

