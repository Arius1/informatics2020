#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct pipe {

	string id = " ";
	double length = 0;
	int diameter = 0;
	bool repairStatus = false;
};

struct KC {
	
	string id = " ";
	string Name = " "; 
	int workshopCount = 0;
	int workingWorkshopCount = 0;
	double efficiency = 0;

};

void getIntValue(int &value, string text, int border1, int border2) {

	do {
		cin.clear();
		cin.ignore(32767, '\n');
		cout << text << endl;
		cin >> value;
	} while (cin.fail() || value < border1 || value > border2);

}

void getDoubleValue(double &value, string text, int border1, int border2) {

	do {
		cin.clear();
		cin.ignore(32767, '\n');
		cout << text << endl;
		cin >> value;
	} while (cin.fail() || value < border1 || value > border2);

}
pipe createPipe() {
	
	pipe p;
	cout << "Считывание данных для трубы:" << endl;
	
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

void Menu() {
	cout << "\n1. Создать новую трубу\n"
		<< "2. Создать новый КС\n"
		<< "3. Считать трубу из файла\n"
		<< "4. Считать КС из файла \n"
		<< "5. Вывести трубу\n"
		<< "6. Вывести трубу в файл\n"
		<< "7. Вывести КС\n"
		<< "8. Вывести КС в файл\n"
		<< "9. Изменить статус ремонта трубы\n"
		<< "10. Изменить количество работающих цехов\n"
		<< "\n"
		<< "0. Выход\n";
}

int main() {

	setlocale(LC_ALL, "Russian");

	pipe pipe1;
	KC kc1;

	while (1) {
		Menu();
		int i;
		cin >> i;
		switch (i) {
		case 1: {
			pipe1 = createPipe();
			break;
		}
		case 2: {
			kc1 = create_KC();
			break;
		}
		case 3: {
			pipe1 = readPipeFile();
			break;
		}
		case 4: {
			kc1 = readKCFile();
			break;
		}
		case 5: {
			if (pipe1.length != 0) {
				printPipe(pipe1);
			}	
			else {
				cout << "Труба не существует\n";
			}
			break;
		}
		case 6: {
			if (pipe1.length != 0) {
				printPipeFile(pipe1);
			}	
			else {
				cout << "Труба не существует\n";
			}
			break;
		}
		case 7: {
			if (kc1.workshopCount != 0) {
				printKC(kc1);
			}
			else {
				cout << "КС не существует\n";
			}
			break;
		}
		case 8: {
			if (kc1.workshopCount != 0) {
				printKCFile(kc1);
			}
			else {
				cout << "КС не существует\n";
			}
			break;
		}
		case 9: {
			if (pipe1.length != 0) {
				bool j = 1;
				changePipeRepairStatus(pipe1.repairStatus, j);
			}
			else {
				cout << "Труба не существует\n";
			}
			break;
		}
		case 10: {
			if (kc1.workshopCount != 0) {
				int count;
				cout << "Введите, сколько цехов вы хотите включить(положительное число)/выключить(отрицательное число): ";
				cin >> count;
				changeKCWorkingWorkshopCount(kc1.workingWorkshopCount, count);
			}
			else {
				cout << "КС не существует\n";
			}
			break;
		}
		case 0: {
			return 0;
			break;
		}
		default: {
			cout << "Неправильный ввод!\n";
		}

		}
	}

	/*
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
	*/

	return 0;
}
