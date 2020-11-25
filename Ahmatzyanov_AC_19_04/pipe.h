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
	
	void changePipeRepairStatus();

	void readPipeFile(std::ifstream& fin);
	void printPipeFile(std::ofstream& fout);

	friend std::ostream& operator << (std::ostream& out, const pipe& p);
	friend std::istream& operator >> (std::istream& in, pipe& p);
};

