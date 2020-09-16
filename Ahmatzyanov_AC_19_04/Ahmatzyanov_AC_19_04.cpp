#include <iostream>
#include <string>
#include <fstream>

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
	double workshop_count;
	double working_workshop_count;
	float efficiency;

};

pipe create_pipe() {
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

KC create_KC() {
	
	KC newKC;
	cout << "Считывание данных для трубы: " << endl;

	newKC.id = " ";

	cout << "\nВведите название КС: ";
	cin >> newKC.Name;

	cout << "\nВведите кол-во станций: ";
	cin >> newKC.workshop_count;

	cout << "\nВведите кол-во работающих станций: ";
	cin >> newKC.working_workshop_count;

	newKC.efficiency = newKC.working_workshop_count / newKC.workshop_count * 100;

	return newKC;
}

void printPipe(pipe n) {

	cout << "Длина трубы: " << n.length << endl;
	cout << "Диаметр трубы: " << n.diameter << endl;
	cout << "Статус: Труба" << ((n.repair_status == true) ? " в ремонте" : " работает") << endl;

}

void printKC(KC n) {

	setlocale(LC_ALL, "Russian");
	cout << "Название КС: " << n.Name << endl;
	cout << "Кол-во цехов: " << n.workshop_count << endl;
	cout << "Кол-во работающих цехов: " << n.working_workshop_count << endl;
	cout << "Эффективность КС: " << n.efficiency << "%" << endl;

}

void changePipeRepairStatus(pipe changePipe, bool status) {
	changePipe.repair_status = status;
}

pipe readPipeFile() {
	pipe newPipe;
	ifstream fin;
	fin.open("inPipe.txt", ios::in);
	if (fin.is_open()) {
		fin >> newPipe.length >> newPipe.diameter;
	}
	fin.close();
	return newPipe;
}

void printPipeFile(const pipe& writePipe) {
	ofstream fout;
	fout.open("outPipe.txt", ios::out);
	if (fout.is_open()) {
		fout << writePipe.length << endl << writePipe.diameter << endl;
	}
	fout.close();
}

int main() {

	setlocale(LC_ALL, "Russian");

	pipe pipe_1;
	pipe_1.id = "1A";
	cout << pipe_1.id << endl;

	pipe pipe1 = create_pipe();
	printPipe(pipe1);

	KC kc1 = create_KC();
	printKC(kc1);

	bool j = true;
	changePipeRepairStatus(pipe1, j);
	printPipe(pipe1);
	
	pipe pipe2 = readPipeFile();
	printPipeFile(pipe2);


	return 0;
}
