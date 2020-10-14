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
	cout << "Кол-во цехов: " << n.workingWorkshopCount << " / " << n.workshopCount << endl;
	cout << "Эффективность КС: " << n.efficiency << endl;

}

void changePipeRepairStatus(bool &repair_status, bool status) {
	repair_status = !repair_status;
}

int changeKCWorkingWorkshopCount(int workingCount, int count) {
	workingCount += count;
	return workingCount;
	
}
void readFile(KC& newKC, pipe& newPipe) {

	ifstream fin;
	fin.open("data.txt", ios::in);
	if (fin.is_open()) {
		fin >> newPipe.length >> newPipe.diameter >> newKC.Name >> newKC.workshopCount >> newKC.workingWorkshopCount >> newKC.efficiency;
		fin.close();
	}
}
void printFile(const pipe writePipe, const KC writeKC) {
	ofstream fout;
	fout.open("data.txt", ios::app);
	if (fout.is_open()) {
		fout << writePipe.length << "\t" << writePipe.diameter << "\n" << writeKC.Name << "\t" << writeKC.workshopCount << "\t" << writeKC.workingWorkshopCount << "\t" << writeKC.efficiency << endl;
		fout.close();
	}
}

void Menu() {
	cout << "\n1. Создать новую трубу\n"
		<< "2. Создать новый КС\n"
		<< "3. Считать трубу и КС из файла\n"
		<< "4. Вывод трубы и КС в файл \n"
		<< "5. Вывести трубу\n"
		<< "6. Вывести КС\n"
		<< "7. Изменить статус ремонта трубы\n"
		<< "8. Изменить количество работающих цехов\n"
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
		int i = getIntValue(text, 0, 8);
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
			readFile(kc1, pipe1);
			break;
		}
		case 4: {
			if (pipe1.length != 0 or kc1.workshopCount != 0) {
				printFile(pipe1, kc1);
			}
			else {
				cout << "Труба и КС не существуют\n";
			}
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
			if (kc1.workshopCount != 0) {
				printKC(kc1);
			}
			else {
				cout << "КС не существует\n";
			}
			break;
		}
		
		case 7: {
			if (pipe1.length != 0) {
				bool j = true;
				changePipeRepairStatus(pipe1.repairStatus, j);
			}
			else {
				cout << "Труба не существует\n";
			}
			break;
		}
		case 8: {
			if (kc1.workshopCount != 0) {
				int count, border;
				border = -1 * kc1.workingWorkshopCount;
				count = getIntValue("Введите, сколько цехов вы хотите включить(положительное число)/выключить(отрицательное число): ", border, 1000);
				kc1.workingWorkshopCount = changeKCWorkingWorkshopCount(kc1.workingWorkshopCount, count);
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
