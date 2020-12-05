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
	bool act = true;
	while (act) {
		newKC.input.push_back(getIntValue("\n������� ������� ������: ", 0, 1000000));
		check(act);
	}
	act = true;
	while (act) {
		newKC.output.push_back(getIntValue("\n������� �������� ������: ", 0, 1000000));
		check(act);
	}
	return in;
}

ostream& operator<<(ostream& out, const KC& kc)
{
	cout << "\nid ��: " << kc.id << endl
		<< "�������� ��: " << kc.Name << endl
		<< "���-�� �����: " << kc.workingWorkshopCount << " / " << kc.workshopCount << endl
		<< "������������� ��: " << kc.efficiency << endl
		<< "������� �����: ";
	for (auto& p : kc.input) {
		cout << p << '\t';
	}
	cout << "\n�������� �����: ";
	for (auto& p : kc.output) {
		cout << p << '\t';
	}
	cout << endl;

	return out;
}

KC::KC()
{
	id = ++maxId;
}

void KC::readKCFile(std::ifstream& fin)
{
	fin >> id >> Name >> workshopCount >> workingWorkshopCount >> efficiency;
	int checkMark;
	fin >> checkMark;
	while (checkMark != -1) {
		input.push_back(checkMark);
		fin >> checkMark;
	}
	fin >> checkMark;
	while (checkMark != -1) {
		output.push_back(checkMark);
		fin >> checkMark;
	}
}

void KC::printKCFile(std::ofstream& fout)
{
		fout << id << "\t" << Name << "\t" <<workshopCount << "\t" << workingWorkshopCount << "\t" << efficiency << "\t";
		for (auto& p : input) {
			fout << p << '\t';
		}
		fout << "-1\t";
		for (auto& p : output) {
			fout << p << '\t';
		}
		fout << "-1\n";
}


void KC::changeKCWorkingWorkshopCount()
{
	int count;
	count = getIntValue("������� ���������� ���������� �����: ", 0, workshopCount);
	workingWorkshopCount = count;
}
