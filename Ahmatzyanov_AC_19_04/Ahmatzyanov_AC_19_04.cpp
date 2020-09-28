#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct pipe {

	string id;
	float length;
	int diameter;
	bool repairStatus = false;
};

struct KC {
	
	string id;
	string Name;
	int workshopCount;
	int workingWorkshopCount;
	float efficiency;

};

int getIntValue() {
	while (true) {
		int value;
		cin >> value;
		if (value != NULL) {
			return value;
		}
		else {
			cout << "Неправильный ввод \n";
		}
	}
}

pipe create_pipe() {
	
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
	cout << "Считывание данных для КС: " << endl;

	newKC.id = " ";

	cout << "\nВведите название КС: ";
	cin >> newKC.Name;

	cout << "\nВведите кол-во станций: ";
	cin >> newKC.workshopCount;

	cout << "\nВведите кол-во работающих станций: ";
	cin >> newKC.workingWorkshopCount;

	cout << "\nВведите 'эффективность КС: " << endl;
	cin >> newKC.efficiency;

	return newKC;
}

void printPipe(pipe n) {

	cout << "Длина трубы: " << n.length << endl;
	cout << "Диаметр трубы: " << n.diameter << endl;
	cout << "Статус: Труба" << (n.repairStatus == true ? " в ремонте" : " работает") << endl;

}

void printKC(KC n) {

	setlocale(LC_ALL, "Russian");
	cout << "Название КС: " << n.Name << endl;
	cout << "Кол-во цехов: " << n.workshopCount << endl;
	cout << "Кол-во работающих цехов: " << n.workingWorkshopCount << endl;
	cout << "Эффективность КС: " << n.efficiency << endl;

}

void changePipeRepairStatus(bool &repair_status, bool status) {
	repair_status = status;
}

void changeKCWorkingWorkshopCount(int &workingCount, int count) {
	workingCount += count;
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

KC readKCFile() {
	KC newKC;
	ifstream fin;
	fin.open("inKC.txt", ios::in);
	if (fin.is_open()) {
		fin >> newKC.Name >> newKC.workshopCount >> newKC.workingWorkshopCount >> newKC.efficiency;
	}
	fin.close();
	return newKC;
}

void printPipeFile(const pipe& writePipe) {
	ofstream fout;
	fout.open("outPipe.txt", ios::out);
	if (fout.is_open()) {
		fout << writePipe.length << endl << writePipe.diameter << endl;
	}
	fout.close();
}

void printKCeFile(const KC& writeKC) {
	ofstream fout;
	fout.open("outKC.txt", ios::out);
	if (fout.is_open()) {
		fout << writeKC.Name << endl << writeKC.workshopCount << endl << writeKC.workingWorkshopCount << endl << writeKC.efficiency << endl;
	}
	fout.close();
}

int main() {

	setlocale(LC_ALL, "Russian");

	pipe pipeTest;
	pipeTest.id = "1A";
	cout << pipeTest.id << endl;

	pipe pipe1 = create_pipe();
	printPipe(pipe1);

	KC kc1 = create_KC();
	printKC(kc1);

	bool j = 1;
	changePipeRepairStatus(pipe1.repairStatus, j);
	printPipe(pipe1);
	
	pipe pipe2 = readPipeFile();
	printPipeFile(pipe2);

	changeKCWorkingWorkshopCount(kc1.workingWorkshopCount, -2);
	printKC(kc1);

	return 0;
}
