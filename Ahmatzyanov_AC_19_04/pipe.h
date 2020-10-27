#pragma once
#include <string>


class pipe
{
public:
	int id;
	double length = 0;
	int diameter = 0;
	bool repairStatus = false;

	friend std::ostream& operator << (std::ostream& out, const pipe& p);
	friend std::istream& operator >> (std::istream& in, pipe& p);
};

