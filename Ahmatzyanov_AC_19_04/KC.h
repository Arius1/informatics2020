#pragma once
#include <string>
class KC
{
public:
	int id;
	static int maxId;
	std::string Name = " ";
	int workshopCount = 0;
	int workingWorkshopCount = 0;
	double efficiency = 0;

	KC();

	friend std::istream& operator >> (std::istream& in, KC& newKC);
	friend std::ostream& operator<<(std::ostream& out, const KC& kc);
};

