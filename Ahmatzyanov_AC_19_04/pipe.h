#pragma once
#include <string>


class pipe
{
public:
	int id;
	static int maxId;
	double length = 0;
	int diameter = 0;
	bool repairStatus = false;

	pipe();

	friend std::ostream& operator << (std::ostream& out, const pipe& p);
	friend std::istream& operator >> (std::istream& in, pipe& p);
};

