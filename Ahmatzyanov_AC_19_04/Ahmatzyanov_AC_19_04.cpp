#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "KC.h"
#include "pipe.h"
#include "utils.h"
#include <unordered_map>
#include <list>

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
		<< "11. Топологическая сортировка\n"
		<< "\n"
		<< "0. Выход\n";
}

void stepDown(list <int>& answer, const unordered_map <int, pipe>& groupPipe, const unordered_map <int, KC>& groupKC, unordered_map <int, bool>& visited, int id, bool& cycle) {
	if (visited.find(id)->second == false) {
		list <int> linkedKCs;
		visited[id] = true;
		for (auto i : groupKC.find(id)->second.output) { //поиск смежных КС
			if (groupPipe.find(i)->second.repairStatus == 0) {
				for (auto j : groupKC) {
					for (auto k : j.second.input) { //3 фора, так как в листе нет find
						if (k == i) {
							linkedKCs.push_front(j.first);
						}
					}
				}
			}
		}
		for (auto i : linkedKCs) { //для всех найденных КС делаем проход
			stepDown(answer, groupPipe, groupKC, visited, i, cycle);
		}
		answer.push_front(id);
	}
	else {
		cycle = true;
	}
}

void topologicSort(const unordered_map <int, pipe>& groupPipe, const unordered_map <int, KC>& groupКС, list <int>& answer, bool& cycle) {
	unordered_map <int, bool> visited;
	cout << "Проверка на цикличность:";
	for (auto i : groupКС) { //метки посещения на false
		for (auto j : groupКС)
			visited[j.first] = false;
		stepDown(answer, groupPipe, groupКС, visited, i.first, cycle);
	}
	if (cycle == false) {
		cout << "Граф ацикличен. Включение сортировки... \n";
		for (auto i : groupКС) { //метки посещения на false
			visited[i.first] = false;
		}
		for (auto i : groupКС) { //первый шаг для любой вершины
			if (visited.find(i.first)->second == false) {
				stepDown(answer, groupPipe, groupКС, visited, i.first, cycle);
			}
		}
		cycle = false; // в ходе работы найдет посещенную вершину
	}
}
int main() {

	setlocale(LC_ALL, "Russian");

	unordered_map <int, pipe> groupPipe;
	unordered_map <int, KC>groupKC;

	while (1) {
		Menu();
		string text = "Введите команду: ";
		int i = getIntValue(text, 0, 11);
		switch (i) {
		case 1: {
			bool act = true;
			while (act) {
				pipe newPipe;
				cin >> newPipe;
				groupPipe.emplace(newPipe.id, newPipe);
				check(act);
			}
			break;
		}
		case 2: {
			bool act = true;
			while (act) {
				KC newKC;
				cin >> newKC;
				groupKC.emplace(newKC.id, newKC);
				check(act);
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
					bool act = true;
					while (act) {
						int id = getIntValue("Введите ID: ", result[0], result[result.size() - 1]);
						groupPipe[id].changePipeRepairStatus();
						check(act);
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
				bool act = true;
				while (act) {
					select(groupKC).changeKCWorkingWorkshopCount();
					check(act);
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
					bool act = true;
					while (act) {
						deleteObj(groupPipe);
						check(act);
					}
				}
				else {
					cout << "Труб не существует" << endl;
				}
			}
			else {
				if (groupKC.size() != 0) {
					bool act = true;
					while (act) {
						deleteObj(groupKC);
						check(act);
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
		case 11: {
			list <int> answer;
			bool cycle = false;
			topologicSort(groupPipe, groupKC, answer, cycle);
			if (cycle == false){
				cout << "Результат топологической сортировки: \n";
				for (int i = 1; i <= groupKC.size(); i++) {
					cout << "Вершина " << i << " : KC id " << answer.front() << endl;
					answer.pop_front();
				}
			}
			else {
				cout << "граф цикличен!";
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
