#include "pipe.h"
#include "utils.h"
#include <fstream>

using namespace std;

int pipe::maxId = -1;

ostream& operator << (ostream& out, const pipe& p) {
	cout << "id �����: " << p.id << endl
		<< "����� �����: " << p.length << endl
		<< "������� �����: " << p.diameter << endl
		<< "������: �����" << (p.repairStatus == true ? " � �������" : " ��������") << endl
		<< "������������ ������������������: " << p.maxPerformance << endl;
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
	id = ++maxId;
}

int pipe::getId()
{
	return id;
}

void pipe::changePipeRepairStatus()
{
	repairStatus = !repairStatus;
	maxPerf();
}

void pipe::maxPerf()
{
	maxPerformance = (int) ((repairStatus) ? 0 : 10000*( sqrt(pow(diameter, 5) / (length) / pow(1000, 5)) ));
}

void pipe::readPipeFile(ifstream& fin)
{
	fin >> id >> length >> diameter >> repairStatus;
	maxPerf();
}

void pipe::printPipeFile(std::ofstream& fout)
{
	fout << id << "\t" << length << "\t" << diameter << "\t" << repairStatus << endl;
}


