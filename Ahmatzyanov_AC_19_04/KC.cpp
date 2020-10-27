#include "KC.h"
#include "utils.h"

using namespace std;

int KC::maxId = 0;

istream& operator >> (istream& in, KC& newKC) {

	cout << "���������� ������ ��� ��: " << endl;

	cout << "\n������� �������� ��: ";
	cin.get();
	getline(cin, newKC.Name);

	newKC.workshopCount = getValue("\n������� ���-�� �������: ", 0, 1000);
	newKC.workingWorkshopCount = getValue("\n������� ���-�� ���������� �������: ", 0, newKC.workshopCount);
	newKC.efficiency = getValue("\n������� ������������� �������: ", 0, 100);

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
	id = maxId++;
}
