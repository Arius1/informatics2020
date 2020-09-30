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

int getIntValue(string text, int border1, int border2) {
	int value;
	cout << text << endl;
	while (!(cin >> value) || value < border1 || value > border2) {
		cin.clear();
		cin.ignore(32767, '\n');
		cout << "\nНеправильный ввод! Введите от " << border1 << " до " << border2 << ": ";
	}
	return value;
}

double getDoubleValue(string text, int border1, int border2) {
	double value;
	cout << text << endl;
	while (!(cin >> value) || value < border1 || value > border2){
		cin.clear();
		cin.ignore(32767, '\n');
	}
	return value;
}

pipe createPipe() {
	
	pipe p;
	cout << "Считывание данных для трубы:" << endl;
	
	p.id = " ";

	p.length = getDoubleValue("\nВведите длину трубы: ", 0, 10000);

	p.diameter = getIntValue("\nВведите диаметр трубы : ", 0, 5000);

	return p;
}

KC create_KC() {
	
	KC newKC;
	cout << "Считывание данных для КС: " << endl;

	newKC.id = " ";

	cout << "\nВведите название КС: ";
	cin.get();
	getline(cin, newKC.Name);

	newKC.workshopCount = getIntValue("\nВведите кол-во станций: ", 0, 1000);

	newKC.workingWorkshopCount = getIntValue("\nВведите кол-во работающих станций: ", 0, 1000);

	newKC.efficiency = getDoubleValue("\nВведите эффективность станции: ", 0, 100);

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
	repair_status = !repair_status;
}

int changeKCWorkingWorkshopCount(int workingCount, int count) {
	
	if ((workingCount += count) >= 0) {
		workingCount += count;
	}
	else {
		return -1;
	}
}

pipe readPipeFile() {
	pipe newPipe;
	ifstream fin;
	fin.open("inPipe.txt", ios::in);
	if (fin.is_open()) {
		fin >> newPipe.length >> newPipe.diameter;
		fin.close();
	}
	return newPipe;
}

KC readKCFile() {
	KC newKC;
	ifstream fin;
	fin.open("inKC.txt", ios::in);
	if (fin.is_open()) {
		fin >> newKC.Name >> newKC.workshopCount >> newKC.workingWorkshopCount >> newKC.efficiency;
		fin.close();
	}
	return newKC;
}

void printPipeFile(const pipe& writePipe) {
	ofstream fout;
	fout.open("inPipe.txt", ios::out);
	if (fout.is_open()) {
		fout << writePipe.length << endl << writePipe.diameter << endl;
		fout.close();
	}
}

void printKCFile(const KC& writeKC) {
	ofstream fout;
	fout.open("inKC.txt", ios::out);
	if (fout.is_open()) {
		fout << writeKC.Name << endl << writeKC.workshopCount << endl << writeKC.workingWorkshopCount << endl << writeKC.efficiency << endl;
		fout.close();
	}
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
		string text = "Введите команду: ";
		int i = getIntValue(text, 0, 10);
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
				bool j = true;
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
				if (changeKCWorkingWorkshopCount(kc1.workingWorkshopCount, count) != -1) {
					kc1.workingWorkshopCount = changeKCWorkingWorkshopCount(kc1.workingWorkshopCount, count);
				}
				else {
					cout << "Неправильный ввод, нет столько станций для выключения";
				}
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
			break;
		}

		}
	}

	return 0;
}
