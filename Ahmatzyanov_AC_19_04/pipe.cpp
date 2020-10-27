#include "pipe.h"
#include "utils.h"

using namespace std;

int pipe::maxId = 0;

ostream& operator << (ostream& out, const pipe& p) {
	cout << "id трубы: " << p.id << endl
		<< "Длина трубы: " << p.length << endl
		<< "Диаметр трубы: " << p.diameter << endl
		<< "Статус: Труба" << (p.repairStatus == true ? " в ремонте" : " работает") << endl;
	return out;
}

istream& operator >> (istream& in, pipe& p) {

	cout << "Считывание данных для трубы:" << endl;
	p.length = getValue("\nВведите длину трубы: ", 0, 10000);
	p.diameter = getValue("\nВведите диаметр трубы : ", 0, 5000);

	return in;
}

pipe::pipe()
{
	id = maxId++;
}
