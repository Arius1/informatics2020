#include "pipe.h"
#include "utils.h"

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
	p.length = getValue("\n������� ����� �����: ", 0, 10000);
	p.diameter = getValue("\n������� ������� ����� : ", 0, 5000);

	return in;
}

pipe::pipe()
{
	id = maxId++;
}
