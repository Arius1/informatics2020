#include "pipe.h"
#include "utils.h"
#include <fstream>

using namespace std;

int pipe::maxId = 0;

ostream& operator << (ostream& out, const pipe& p) {
	cout << "id �����: " << p.id << endl
		<< "����� �����: " << p.length << endl
		<< "������� �����: " << p.diameter << endl
		<< "������: �����" << (p.repairStatus == true ? " � �������" : " ��������") << endl;
	return out;
}

istream& operator >> (istream& in, pipe& p) {

	cout << "���������� ������ ��� �����:" << endl;
	p.length = getDoubleValue("\n������� ����� �����: ", 0, 10000);
	p.diameter = getIntValue("\n������� ������� ����� : ", 0, 5000);

	return in;
}

pipe::pipe()
{
	id = maxId++;
	cout << "+ \n";
}

void pipe::changePipeRepairStatus()
{
	repairStatus = !repairStatus;
}

void pipe::readPipeFile(ifstream& fin)
{
	fin >> id >> length >> diameter >> repairStatus;
}

void pipe::printPipeFile(std::ofstream& fout)
{
	fout << id << "\t" << length << "\t" << diameter << repairStatus << endl;
}

void pipe::printMaxId(std::ofstream& fout)
{
	fout << maxId - 1 << std::endl;
}

