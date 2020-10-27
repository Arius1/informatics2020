#include "KC.h"
#include "utils.h"

using namespace std;

istream& operator >> (istream& in, KC& newKC) {

	cout << "���������� ������ ��� ��: " << endl;

	cout << "\n������� �������� ��: ";
	cin.get();
	getline(cin, newKC.Name);

	newKC.workshopCount = getValue("\n������� ���-�� �������: ", 0, 1000);
	newKC.workingWorkshopCount = getValue("\n������� ���-�� ���������� �������: ", 0, 1000);
	newKC.efficiency = getValue("\n������� ������������� �������: ", 0, 100);

	return in;
}

ostream& operator<<(ostream& out, const KC& kc)
{
	cout << "\n�������� ��: " << kc.Name << endl
		<< "���-�� �����: " << kc.workingWorkshopCount << " / " << kc.workshopCount << endl
		<< "������������� ��: " << kc.efficiency << endl;

	return out;
}
