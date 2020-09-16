#include <iostream>

using namespace std;

struct pipe {

	string id;
	float length;
	int diameter;
	bool repair_status;
};

struct KC {
	
	string id;
	string Name;
	int workshop_count;
	int working_workshop_count;
	double efficiency;

};

int main() {
	setlocale(LC_ALL, "Russian");
	cout << "Считывание данных для трубы: " << endl;

	int ch;
	cin >> ch;

	cout << 10. / ch << endl;

	cin >> ch;

	return 0;
}