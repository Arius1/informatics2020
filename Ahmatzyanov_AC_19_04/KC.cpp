#include "KC.h"
#include "utils.h"

using namespace std;

int KC::maxId = 0;

istream& operator >> (istream& in, KC& newKC) {

	cout << "Считывание данных для КС: " << endl;

	cout << "\nВведите название КС: ";
	cin.get();
	getline(cin, newKC.Name);

	newKC.workshopCount = getValue("\nВведите кол-во станций: ", 0, 1000);
	newKC.workingWorkshopCount = getValue("\nВведите кол-во работающих станций: ", 0, newKC.workshopCount);
	newKC.efficiency = getValue("\nВведите эффективность станции: ", 0, 100);

	return in;
}

ostream& operator<<(ostream& out, const KC& kc)
{
	cout << "\nid КС: " << kc.id << endl
		<< "Название КС: " << kc.Name << endl
		<< "Кол-во цехов: " << kc.workingWorkshopCount << " / " << kc.workshopCount << endl
		<< "Эффективность КС: " << kc.efficiency << endl;

	return out;
}

KC::KC()
{
	id = maxId++;
}
