#include <iostream>

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

int createpipe(x) {
	pipe x;
	cout << "Считывание данных для трубы: " << endl;

	cout << "Введите Индентификатор трубы: ";
	cin >> x.id;

	cout << "\nВведите длину трубы: ";
	cin >> x.length;

	cout << "\nВведите диаметр трубы: ";
	cin >> x.diameter;
}

int main() {

	setlocale(LC_ALL, "Russian");

	pipe pipe_1;
	pipe_1.id = "1A";
	cout << pipe_1.id;
	return 0;
}
