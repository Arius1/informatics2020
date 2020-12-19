#pragma once
#include <string>
#include <cmath>

class pipe
{
	int id;
	
public:

	static int maxId;
	double length = 0;
	int diameter = 0;
	bool repairStatus = false;
	int maxPerformance = 0 ;

	pipe();
	
	int getId();

	void changePipeRepairStatus();
	void maxPerf();

	void readPipeFile(std::ifstream& fin);
	void printPipeFile(std::ofstream& fout);

	friend std::ostream& operator << (std::ostream& out, const pipe& p);
	friend std::istream& operator >> (std::istream& in, pipe& p);

};

