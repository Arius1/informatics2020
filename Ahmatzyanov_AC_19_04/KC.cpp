#include "KC.h"
#include "utils.h"
#include <fstream>

using namespace std;

int KC::maxId = -1;

istream& operator >> (istream& in, KC& newKC) {

	cout << "���������� ������ ��� ��: " << endl;

	cout << "\n������� �������� ��: ";
	cin.get();
	getline(cin, newKC.Name);

	newKC.workshopCount = getIntValue("\n������� ���-�� �������: ", 0, 1000);
	newKC.workingWorkshopCount = getIntValue("\n������� ���-�� ���������� �������: ", 0, newKC.workshopCount);
	newKC.efficiency = getDoubleValue("\n������� ������������� �������: ", 0, 100);
	
	return in;
}

ostream& operator<<(ostream& out, const KC& kc)
{
	cout << "\nid ��: " << kc.id << endl
		<< "�������� ��: " << kc.Name << endl
		<< "���-�� �����: " << kc.workingWorkshopCount << " / " << kc.workshopCount << endl
		<< "������������� ��: " << kc.efficiency << endl;

	return out;
}

KC::KC()
{
	id = ++maxId;
}

int KC::getId()
{
	return id;
}

void KC::readKCFile(std::ifstream& fin)
{
	fin >> id >> Name >> workshopCount >> workingWorkshopCount >> efficiency;

}

void KC::printKCFile(std::ofstream& fout)
{
		fout << id << "\t" << Name << "\t" <<workshopCount << "\t" << workingWorkshopCount << "\t" << efficiency << "\t";
}


void KC::changeKCWorkingWorkshopCount()
{
	int count;
	count = getIntValue("������� ���������� ���������� �����: ", 0, workshopCount);
	workingWorkshopCount = count;
}
