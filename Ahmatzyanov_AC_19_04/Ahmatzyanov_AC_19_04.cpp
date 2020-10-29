#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "KC.h"
#include "pipe.h"
#include "utils.h"

using namespace std;

void readPipeFile(ifstream& fin, pipe& newPipe) {
	fin >> newPipe.id >> newPipe.length >> newPipe.diameter;
}
void readKCFile(ifstream& fin, KC& newKC) {
	fin >> newKC.id >> newKC.Name >> newKC.workshopCount >> newKC.workingWorkshopCount >> newKC.efficiency;
}
void printPipeFile(ofstream& fout, const pipe writePipe) {
	fout << writePipe.id << "\t" << writePipe.length << "\t" << writePipe.diameter << endl;
}
void printKCFile(ofstream& fout, const KC writeKC) {
	fout << writeKC.id << "\t" << writeKC.Name << "\t" << writeKC.workshopCount << "\t" << writeKC.workingWorkshopCount << "\t" << writeKC.efficiency << endl;
}
void printCount(ofstream& fout, int count) {
	fout << count << endl;
}
void printMaxId(ofstream& fout, int maxId) {
	fout << maxId << endl;
}

void statusFilter(int count) {
	if (count == -1) {
		cout << "Таких объектов не существует" << endl;
	}
}

template <typename par, class className>
using Filter = bool(*)(const className& object, par parameter);

bool checkByName(const KC& kc, string parameter) {
	return kc.Name == parameter;
}
bool checkByStatus(const pipe& p, bool parameter) {
	return p.repairStatus == parameter;
}
bool checkByWorkingPercent(const KC& kc, double parameter) {
	return (((double)kc.workingWorkshopCount / (double)kc.workshopCount) * 100) >= parameter;
}
template <class className>
bool checkPipeByID(const className& obj, int parameter) {
	return obj.id == parameter;
}

template <typename obj, class className>
vector <int> findObjectByFilter(const vector <className>& group, Filter <obj, className> f, obj parameter) {
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

void Menu() {
	cout << "\n1. Создать новую трубу\n"
		<< "2. Создать новую КС\n"
		<< "3. Считать трубу и КС из файла\n"
		<< "4. Вывод трубы и КС в файл \n"
		<< "5. Вывести трубу\n"
		<< "6. Вывести КС\n"
		<< "7. Редактировать статус труб\n"
		<< "8. Редактировать количество работающих станций КС \n"
		<< "9. Удалить объект\n"
		<< "10. Найти объект\n"
		<< "\n"
		<< "0. Выход\n";
}

int main() {

	setlocale(LC_ALL, "Russian");

	vector <pipe> groupPipe;
	vector <KC> groupKC;

	while (1) {
		Menu();
		string text = "Введите команду: ";
		int i = getIntValue(text, 0, 10);
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
				int count, buffer;
				fin >> count;
				buffer = count;
				groupPipe.reserve(count);
				while (count--) {
					pipe newPipe;
					readPipeFile(fin, newPipe);
					groupPipe.push_back(newPipe);
				}
				fin >> groupPipe[buffer-1].maxId;
			}
			if (fin.is_open()) {
				int count, buffer;
				fin >> count;
				buffer = count;
				groupPipe.reserve(count);
				while (count--) {
					KC newKC;
					readKCFile(fin, newKC);
					groupKC.push_back(newKC);
				}
				fin >> groupKC[buffer - 1].maxId;
			}
			fin.close();
			break;
		}
		case 4: {
			ofstream fout;
			fout.open("data.txt", ios::out);
			if (fout.is_open()) {
				if (groupPipe.size() != 0) {
					printCount(fout, groupPipe.size());
					for (pipe p : groupPipe) {
						printPipeFile(fout, p);
					}
					printMaxId(fout, groupPipe[groupPipe.size() - 1].maxId);
				}
				else {
					cout << "Труба не существует\n";
				}
				if (groupKC.size() != 0) {
					printCount(fout, groupKC.size());
					for (KC kc : groupKC) {
						printKCFile(fout, kc);
					}
					printMaxId(fout, groupKC[groupKC.size()-1].maxId);
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
			
			bool status = getIntValue("Введите статус ремонта для поиска: ", 0, 1);
			vector <int> result;
			cout << "Были найдены трубы с id:" << endl;
			for (int i : findObjectByFilter(groupPipe, checkByStatus, status)) {
				result.push_back(i);
				cout << i << endl;
			}
			if (result.size() != 0) {
				int j = getIntValue("Выберите способ замены статуса: \n 1) Для всех найденных \n 2) Для определенных ", 1u, 2u);
				switch (j) {
				case 1: {
					for (auto& i : result) {
						groupPipe[result[i]].changePipeRepairStatus();
					}
					break;
				}
				case 2: {
					int border = getIntValue("Введите количество объектов редактирования", 1u, result.size());
					for (int i = 1; i <= border; i++ ) {
						int id = getIntValue("Введите ID: ", result[0], result[result.size()-1]);
						groupPipe[id].changePipeRepairStatus();
					}
					break;
				}
				}
			}
			else {
				cout << "Таких труб не существует\n";
			}
			break;
		}
		case 8: {
			if (groupKC.size() != 0) {
				select(groupKC).changeKCWorkingWorkshopCount();
			}
			else {
				cout << "КС не существует\n";
			}
			
			break;
		}
		case 9: {
			if (getIntValue("Удалить трубу - 1, удалить КС - 2", 1, 2) == 1) {
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
			int j = getIntValue("Введите фильтр поиска: \n 1. ID трубы \n 2. Имя КС \n 3. Процент работающих станций \n 4. Статус ремонта трубы", 1, 4);
				switch (j) {
				case 1: {
					/*search("Введите id объекта", 0u, 10000u, groupPipe, checkPipeByID);*/
					int count = -1;
					int id = getIntValue("Введите id объекта", 0u, 10000u);
					for (int i : findObjectByFilter(groupPipe, checkPipeByID, id)) {
						cout << groupPipe[i];
						count = i;
					}
					statusFilter(count);
					break;
				}
				case 2: {
					int count = -1;
					cout << "\nВведите название КС: ";
					string name;
					cin.get();
					getline(cin, name);
					for (int i : findObjectByFilter <string>(groupKC, checkByName, name)) {
						cout << groupKC[i];
						count = i;
					}
					statusFilter(count);
					break;
				}
				case 3: {
					int count = -1;
					double perc = getDoubleValue("Введите процент действующих цехов КС для поиска (более, чем): ", 0, 100);
					for (int i : findObjectByFilter (groupKC, checkByWorkingPercent, perc )) {
						cout << groupKC[i];
						count = i;
					}
					statusFilter(count);
					break;
				}
				case 4: {
					int count = -1;
					bool status = getIntValue("Введите статус ремонта для поиска: ", 0, 1);
					for (int i : findObjectByFilter(groupPipe, checkByStatus, status)) {
						cout << groupPipe[i];
						count = i;
					}
					statusFilter(count);
					break;
				}
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
// не заработало
//template <class className, typename T>
//void search(string text, int border1, int border2, const vector <className>& group, Filter <T, className> filter) {
//	int count = -1;
//	bool parameter = getIntValue(text, border1, border2);
//	for (int i : findObjectByFilter(group, filter, parameter)) {
//		cout << group[i];
//		count = i;
//	}
//	statusFilter(count);
//}