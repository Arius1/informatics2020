#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "KC.h"
#include "pipe.h"
#include "utils.h"

using namespace std;

void changePipeRepairStatus(bool &repair_status, bool status) {
	repair_status = !repair_status;
}

int changeKCWorkingWorkshopCount(KC changeKC) {
	int count, border;
	border = -1 * changeKC.workingWorkshopCount;
	count = getValue("Введите, сколько цехов вы хотите включить(положительное число)/выключить(отрицательное число): ", border, changeKC.workshopCount - changeKC.workingWorkshopCount);
	changeKC.workingWorkshopCount += count;
	return changeKC.workingWorkshopCount;
}
void readPipeFile(ifstream& fin, pipe& newPipe) {
	fin >> newPipe.length >> newPipe.diameter;
}
void readKCFile(ifstream& fin, KC& newKC) {
	fin >> newKC.Name >> newKC.workshopCount >> newKC.workingWorkshopCount >> newKC.efficiency;
}
void printPipeFile(ofstream& fout, const pipe writePipe) {
	fout << writePipe.length << "\t" << writePipe.diameter << endl;
}

void printKCFile(ofstream& fout, const KC writeKC) {
	fout <<  writeKC.Name << "\t" << writeKC.workshopCount << "\t" << writeKC.workingWorkshopCount << "\t" << writeKC.efficiency << endl;
}

void Menu() {
	cout << "\n1. Создать новую трубу\n"
		<< "2. Создать новую КС\n"
		<< "3. Считать трубу и КС из файла\n"
		<< "4. Вывод трубы и КС в файл \n"
		<< "5. Вывести трубу\n"
		<< "6. Вывести КС\n"
		<< "7. Изменить статус ремонта трубы\n"
		<< "8. Изменить количество работающих цехов\n"
		<< "9. Удалить объект\n"
		<< "10. Найти объект\n"
		<< "\n"
		<< "0. Выход\n";
}
template <typename par, class vec>
using Filter = bool(*)(const vec& object, par parameter);

bool checkByName(const KC& kc, string parameter) {
	return kc.Name == parameter;
}
bool checkByStatus(const pipe& p, bool parameter) {
	return p.repairStatus == parameter;
}
bool checkByWorkingPercent(const KC& kc, int parameter) {
	return (kc.workingWorkshopCount/kc.workshopCount)*100 >= parameter;
}
bool checkPipeByID(const pipe& p, int parameter) {
	return p.id == parameter;
}
template <typename obj, class vec>
vector <int> findObjectByFilter(const vector <vec>& group, Filter <obj, vec> f,  obj parameter) {
	vector <int> result;
	int i = 0;
	for (auto& p : group) {
		if (f(p, parameter)) {
			result.push_back(i);
		}
		i++;
	}
	return result;
}

int main() {

	setlocale(LC_ALL, "Russian");

	vector <pipe> groupPipe;
	vector <KC> groupKC;

	while (1) {
		Menu();
		string text = "Введите команду: ";
		int i = getValue(text, 0, 10);
		switch (i) {
		case 1: {
			pipe newPipe;
			cin >> newPipe;
			groupPipe.push_back(newPipe);
			break;
		}
		case 2: {
			KC newKC;
			cin >> newKC;
			groupKC.push_back(newKC);
			break;
		}
		case 3: {
			ifstream fin;
			fin.open("data.txt", ios::in);
			if (fin.is_open()) {
				int count;
				fin >> count;
				groupPipe.reserve(count);
				while (count--) {
					pipe newPipe;
					readPipeFile(fin, newPipe);
					groupPipe.push_back(newPipe);
				}
			}
			if (fin.is_open()) {
				int count;
				fin >> count;
				groupPipe.reserve(count);
				while (count--) {
					KC newKC;
					readKCFile(fin, newKC);
					groupKC.push_back(newKC);
				}
			}
			fin.close();
			break;
		}
		case 4: {
			ofstream fout;
			fout.open("data.txt", ios::app);
			if (fout.is_open()) {
				if (groupPipe.size() != 0) {
					for (pipe p : groupPipe) {
						printPipeFile(fout, p);
					}
				}
				else {
					cout << "Труба не существует\n";
				}
				if (groupKC.size() != 0) {
					for (KC kc : groupKC) {
						printKCFile(fout, kc);
					}
				}
				else {
					cout << "КС не существует\n";
				}
			}
			fout.close();
			break;
		}
		case 5: {
			if (groupPipe.size() != 0) {
				cout << select(groupPipe);
			}
			else {
				cout << "Труба не существует\n";
			}
			break;
		}

		case 6: {
			if (groupKC.size() != 0) {
				cout << select(groupKC);
			}
			else {
				cout << "КС не существует\n";
			}
			break;
		}

		case 7: {
			if (groupPipe.size() != 0) {
				bool j = true;
				changePipeRepairStatus(select(groupPipe).repairStatus, j);
			}
			else {
				cout << "Труба не существует\n";
			}
			break;
		}
		case 8: {
			if (groupKC.size() != 0) {
				KC changeKC = select(groupKC);
				changeKC.workingWorkshopCount = changeKCWorkingWorkshopCount(changeKC);
			}
			else {
				cout << "КС не существует\n";
			}
			break;
		}
		case 9: {
			if (getValue("Удалить трубу - 1, удалить КС - 2", 1, 2) == 1) {
				if (groupPipe.size() != 0) {

					deleteObj(groupPipe);
				}
				else {
					cout << "Труб не существует" << endl;
				}
			}
			else {
				if (groupKC.size() != 0) {
					deleteObj(groupKC);
				}
				else {
					cout << "KC не существует" << endl;
				}
			}
			break;
		}
		case 10: {
			int j = getValue("Введите фильтр поиска: \n 1. ID трубы \n 2. Имя КС \n 3.Процент работающих станций \n 4. Статус ремонта трубы", 1, 4);
				switch (j) {
				case 1: {
					int id = getValue("Введите id объекта", 0u, 10000u);
					for (int i : findObjectByFilter(groupPipe, checkPipeByID, id))
						cout << groupPipe[i];
					break;
				}
				case 2: {
					cout << "\nВведите название КС: ";
					string name;
					cin.get();
					getline(cin, name);
					for (int i : findObjectByFilter <string> (groupKC, checkByName, name))
						cout << groupKC[i];
					break;
				}
				case 3: {
					int perc = getValue("Введите процент действующих цехов КС для поиска: ", 0, 100);
					for (int i : findObjectByFilter (groupKC, checkByWorkingPercent, perc ))
						cout << groupKC[i];
					break;
				}
				case 4: {
					bool status = getValue("Введите статус ремонта для поиска: ", 0, 1);
					for (int i : findObjectByFilter(groupPipe, checkByStatus, status))
						cout << groupPipe[i];
					break;
				}
			}

			/*for (int i : findByID(groupPipe)) {
				cout << groupPipe[i];
			}*/
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
