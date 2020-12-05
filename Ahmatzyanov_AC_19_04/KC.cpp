#include "KC.h"
#include "utils.h"
#include <fstream>

using namespace std;

int KC::maxId = -1;

istream& operator >> (istream& in, KC& newKC) {

	cout << "Считывание данных для КС: " << endl;

	cout << "\nВведите название КС: ";
	cin.get();
	getline(cin, newKC.Name);

	newKC.workshopCount = getIntValue("\nВведите кол-во станций: ", 0, 1000);
	newKC.workingWorkshopCount = getIntValue("\nВведите кол-во работающих станций: ", 0, newKC.workshopCount);
	newKC.efficiency = getDoubleValue("\nВведите эффективность станции: ", 0, 100);
	bool act = true;
	while (act) {
		newKC.input.push_back(getIntValue("\nВведите входной маркер: ", 0, 1000000));
		check(act);
	}
	act = true;
	while (act) {
		newKC.output.push_back(getIntValue("\nВведите выходной маркер: ", 0, 1000000));
		check(act);
	}
	return in;
}

ostream& operator<<(ostream& out, const KC& kc)
{
	cout << "\nid КС: " << kc.id << endl
		<< "Название КС: " << kc.Name << endl
		<< "Кол-во цехов: " << kc.workingWorkshopCount << " / " << kc.workshopCount << endl
		<< "Эффективность КС: " << kc.efficiency << endl
		<< "Входные трубы: ";
	for (auto& p : kc.input) {
		cout << p << '\t';
	}
	cout << "\nВыходные трубы: ";
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
	count = getIntValue("Введите количество работающих цехов: ", 0, workshopCount);
	workingWorkshopCount = count;
}
