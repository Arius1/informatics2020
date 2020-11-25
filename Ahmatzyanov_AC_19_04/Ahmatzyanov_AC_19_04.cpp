#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "KC.h"
#include "pipe.h"
#include "utils.h"
#include <unordered_map>

using namespace std;
//добавить задание имени файла
//основа теории по unorderedmap: https://www.cplusplus.com/reference/unordered_map/unordered_map/

template <class className, typename par>
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
bool checkByID(const className& obj, int parameter) {
	return obj.id == parameter;
}

template <class className, typename T>
vector <int> findObjectByFilter(const unordered_map<int, className>& group, Filter <className, T> f, T parameter) {
	vector <int> result;
	for (auto& p : group) {
		if (f(p.second, parameter)) {
			result.push_back(p.first);
		}
	}
	return result;
}

template <class className>
void searchCout(unordered_map <int, className> group, const vector <int>& result) {
	if (result.size() > 0) {
		for (auto i : result) {
			cout << group[i];
		}
	}
	else {
		cout << "Таких объектов нет! \n";
	}
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

	unordered_map <int, pipe> groupPipe;
	unordered_map <int, KC>groupKC;

	while (1) {
		Menu();
		string text = "Введите команду: ";
		int i = getIntValue(text, 0, 10);
		switch (i) {
		case 1: {
			bool flag = true;
			while (flag) {
				pipe newPipe;
				cin >> newPipe;
				groupPipe.emplace(newPipe.id, newPipe);
				check(flag);
			}
			break;
		}
		case 2: {
			bool flag = true;
			while (flag) {
				KC newKC;
				cin >> newKC;
				groupKC.emplace(newKC.id, newKC);
				check(flag);
			}
			break;
		}
		case 3: {
			groupPipe.clear();
			groupKC.clear();
			ifstream fin;
			fin.open(getName(), ios::in);
			if (fin.is_open()) {
				int count;
				fin >> count;
				while (count--) {
					pipe newPipe;
					newPipe.readPipeFile(fin);
					groupPipe.emplace(newPipe.id, newPipe);
				}
				int max;
				fin >> max;
				pipe::maxId = max;

				fin >> count;
				while (count--) {
					KC newKC;
					newKC.readKCFile(fin);
					groupKC.emplace(newKC.id, newKC);
				}
				fin >> max;
				KC::maxId = max;
			}
			else {
				cout << "Такого файла нет! \n";
			}
			fin.close();
			break;
		}
		case 4: {
			ofstream fout;
			fout.open(getName(), ios::out);
			if (fout.is_open()) {
				fout << groupPipe.size() << endl;
				for (auto p : groupPipe) {
					p.second.printPipeFile(fout);
				}
				fout << pipe::maxId << endl;

				fout << groupKC.size() << endl;
				for (auto kc : groupKC) {
					kc.second.printKCFile(fout);
				}
				fout << KC::maxId;
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
			result = findObjectByFilter(groupPipe, checkByStatus, status);
			cout << "Были найдены трубы с id:" << endl;
			for (int i : result) {
				cout << i << endl;
			}
			if (result.size() != 0) {
				int j = getIntValue("Выберите способ замены статуса: \n 1) Для всех найденных \n 2) Для определенных ", 1u, 2u);
				switch (j) {
				case 1: {
					for (auto& i : result) {
						groupPipe[i].changePipeRepairStatus();
					}
					break;
				}
				case 2: {
					bool flag = true;
					while (flag) {
						int id = getIntValue("Введите ID: ", result[0], result[result.size() - 1]);
						groupPipe[id].changePipeRepairStatus();
						check(flag);
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
				bool flag = true;
				while (flag) {
					select(groupKC).changeKCWorkingWorkshopCount();
					check(flag);
				}
			}
			else {
				cout << "КС не существует\n";
			}
			
			break;
		}
		case 9: {
			if (getIntValue("Удалить трубу - 1, удалить КС - 2", 1, 2) == 1) {
				if (groupPipe.size() != 0) {
					bool flag = true;
					while (flag) {
						deleteObj(groupPipe);
						check(flag);
					}
				}
				else {
					cout << "Труб не существует" << endl;
				}
			}
			else {
				if (groupKC.size() != 0) {
					bool flag = true;
					while (flag) {
						deleteObj(groupKC);
						check(flag);
					}
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
					bool found = false;
					int id = getIntValue("Введите id объекта", 0u, 10000u);
					vector <int> result;
					result = findObjectByFilter(groupPipe, checkByID, id);
					searchCout(groupPipe, result);
					break;
				}
				case 2: {
					int count = -1;
					cout << "\nВведите название КС: ";
					string name;
					cin.get();
					getline(cin, name);
					vector <int> result;
					result = findObjectByFilter < KC, string>(groupKC, checkByName, name);
					searchCout(groupKC, result);
					break;
				}
				case 3: {
					int count = -1;
					double perc = getDoubleValue("Введите процент действующих цехов КС для поиска (более, чем): ", 0, 100);
					vector <int> result;
					result = findObjectByFilter(groupKC, checkByWorkingPercent, perc);
					searchCout(groupKC, result);
					break;
				}
				case 4: {
					int count = -1;
					bool status = getIntValue("Введите статус ремонта для поиска: ", 0, 1);
					vector <int> result;
					result = findObjectByFilter(groupPipe, checkByStatus, status);
					searchCout(groupPipe, result);
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
