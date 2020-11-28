#pragma once
#include <string>
#include <list>
class KC
{
public:
	int id;
	static int maxId;
	std::string Name = " ";
	int workshopCount = 0;
	int workingWorkshopCount = 0;
	double efficiency = 0;
	std::list <int> input;
	std::list <int> output;

	KC();
	void readKCFile(std::ifstream& fin);
	void printKCFile(std::ofstream& fout);
	void changeKCWorkingWorkshopCount();

	friend std::istream& operator >> (std::istream& in, KC& newKC);
	friend std::ostream& operator<<(std::ostream& out, const KC& kc);
};

