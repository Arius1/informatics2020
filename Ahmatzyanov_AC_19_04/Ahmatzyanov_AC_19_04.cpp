#include <iostream>
#include <string>

using namespace std;

struct pipe {

	string id;
	float length;
	int diameter;
	bool repair_status = false;
};

struct KC {
	
	string id;
	string Name;
	int workshop_count;
	int working_workshop_count;
	float efficiency;

};

pipe createpipe() {
	setlocale(LC_ALL, "Russian");
	pipe p;
	cout << "Считывание данных для трубы: " << endl;
	
	p.id = " ";

	cout << "\nВведите длину трубы: ";
	cin >> p.length;

	cout << "\nВведите диаметр трубы: ";
	cin >> p.diameter;

	return p;
}

pipe createKC() {
	setlocale(LC_ALL, "Russian");
	pipe p;
	cout << "Считывание данных для трубы: " << endl;

	p.id = " ";

	cout << "\nВведите длину трубы: ";
	cin >> p.length;

	cout << "\nВведите диаметр трубы: ";
	cin >> p.diameter;

	return p;
}

void print_pipe(pipe n) {
	cout << "Длина трубы: " << n.length << endl;
	cout << "Диаметр трубы: " << n.diameter << endl;
	cout << "Статус: Труба" << ((n.repair_status == true) ? " в ремонте" : " работает") << endl;
}

int main() {

	setlocale(LC_ALL, "Russian");

	pipe pipe_1;
	pipe_1.id = "1A";
	cout << pipe_1.id << endl;

	pipe pipe1 = createpipe();
	cout << pipe1.diameter << endl;

	print_pipe(pipe1);

	return 0;
}
