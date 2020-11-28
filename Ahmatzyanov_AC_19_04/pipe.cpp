#include "pipe.h"
#include "utils.h"
#include <fstream>

using namespace std;

int pipe::maxId = -1;

ostream& operator << (ostream& out, const pipe& p) {
	cout << "id трубы: " << p.id << endl
		<< "Длина трубы: " << p.length << endl
		<< "Диаметр трубы: " << p.diameter << endl
		<< "Статус: Труба" << (p.repairStatus == true ? " в ремонте" : " работает") << endl
		<< "Маркер трубы: " << p.mark << endl;
	return out;
}

istream& operator >> (istream& in, pipe& p) {

	cout << "Считывание данных для трубы:" << endl;
	p.length = getDoubleValue("\nВведите длину трубы: ", 0, 10000);
	p.diameter = getIntValue("\nВведите диаметр трубы : ", 0, 5000);
	p.mark = getIntValue("\nВведите маркер трубы : ", 0, 1000000);

	return in;
}

pipe::pipe()
{
	id = ++maxId;
}

void pipe::changePipeRepairStatus()
{
	repairStatus = !repairStatus;
}

void pipe::readPipeFile(ifstream& fin)
{
	fin >> id >> length >> diameter >> repairStatus >> mark;
}

void pipe::printPipeFile(std::ofstream& fout)
{
	fout << id << "\t" << length << "\t" << diameter << "\t" << repairStatus << "\t" << mark << endl;
}


