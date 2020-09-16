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

int main() {

	setlocale(LC_ALL, "Russian");

	pipe pipe_1;
	pipe_1.id = "1A";
	cout << pipe_1.id << endl;

	pipe pipe1 = createpipe();
	cout << pipe1.diameter << endl;

	return 0;
}
