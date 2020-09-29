#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct pipe {

	string id;
	double length;
	int diameter;
	bool repairStatus = false;
};

struct KC {
	
	string id;
	string Name;
	int workshopCount;
	int workingWorkshopCount;
	double efficiency;

};

void getIntValue(int &value, string text, int border1, int border2) {

	do {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << text << endl;
		cin >> value;
	} while (cin.fail() || value < border1 || value > border2);

}

void getDoubleValue(double &value, string text, int border1, int border2) {

	do {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << text << endl;
		cin >> value;
	} while (cin.fail() || value < border1 || value > border2);

}
pipe createPipe() {
	
	pipe p;
	cout << "Далее будут считываться данные для трубы. Нажмите Enter." << endl;
	
	p.id = " ";

	string coutText = "\nВведите длину трубы: ";
	getDoubleValue(p.length, coutText, 0, 10000);

	coutText = "\nВведите диаметр трубы: ";
	getIntValue(p.diameter, coutText, 0, 1000);

	return p;
}

KC create_KC() {
	
	KC newKC;
	cout << "Считывание данных для КС: " << endl;

	newKC.id = " ";

	string coutText = "\nВведите название КС: ";
	cin >> newKC.Name;

	coutText = "\nВведите кол-во станций: ";
	getIntValue(newKC.workshopCount, coutText, 0, 1000);

	coutText = "\nВведите кол-во работающих станций: ";
	getIntValue(newKC.workingWorkshopCount, coutText, 0, 1000);

	coutText = "\nВведите 'эффективность КС: ";
	getDoubleValue(newKC.efficiency, coutText, 0, 100);

	return newKC;
}

void printPipe(pipe n) {

	cout << "\nДлина трубы: " << n.length << endl;
	cout << "Диаметр трубы: " << n.diameter << endl;
	cout << "Статус: Труба" << (n.repairStatus == true ? " в ремонте" : " работает") << endl;

}

void printKC(KC n) {

	cout << "\nНазвание КС: " << n.Name << endl;
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

void printKCFile(const KC& writeKC) {
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

	pipe pipe1 = createPipe();
	printPipe(pipe1);

	KC kc1 = create_KC();
	printKC(kc1);

	bool j = 1;
	changePipeRepairStatus(pipe1.repairStatus, j);
	printPipe(pipe1);
	
	pipe pipe2 = readPipeFile();
	printPipeFile(pipe2);

	pipe pipe3 = createPipe();
	printPipe(pipe3);

	changeKCWorkingWorkshopCount(kc1.workingWorkshopCount, -2);
	printKCFile(kc1);

	return 0;
}
