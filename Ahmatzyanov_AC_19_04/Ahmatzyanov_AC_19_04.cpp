#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "KC.h"
#include "pipe.h"
#include "gts.h"
#include "utils.h"
#include <unordered_map>
#include <list>
#include <unordered_set>

using namespace std;

int main() {

	setlocale(LC_ALL, "Russian");

	unordered_map <int, pipe> groupPipe;
	unordered_map <int, KC>groupKC;
	unordered_map <int, gts> linkedKCs;
	unordered_set <int> linkedPipes;

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
				groupPipe.emplace(newPipe.getId(), newPipe);
				check(act);
			}
			break;
		}
		case 2: {
			bool act = true;
			while (act) {
				KC newKC;
				cin >> newKC;
				groupKC.emplace(newKC.getId(), newKC);
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
					groupPipe.emplace(newPipe.getId(), newPipe);
				}
				int max;
				fin >> max;
				pipe::maxId = max;

				fin >> count;
				while (count--) {
					KC newKC;
					newKC.readKCFile(fin);
					groupKC.emplace(newKC.getId(), newKC);
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
					result = findObjectByFilter(groupPipe, checkPipeByID, id);
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
			int j = getIntValue("Введите действие: \n 1. Создать гтс без связей. \n 2. Считать гтс из файла. \n 3. Установить связь. \n 4. Удалить связь \n 5. Топологическая сортировка \n 6. Показать связи \n 7. Вывод в файл. \n 8. Кратчайший путь.", 1, 9);
			switch (j) {
				case 1: {
					for (const auto& obj : groupKC) {
						gts newKC;
						linkedKCs.emplace(obj.first, newKC);
					}
					break;
				}
				case 2: {
					linkedKCs.clear();
					ifstream fin;
					fin.open(getName(), ios::in);
					if (fin.is_open()) {
						int count, id, link;
						fin >> count;
						while (count--) {
							gts newKC;
							fin >> id;
							linkedKCs.emplace(id, newKC);
							fin >> link;
							while (link != -1) {
								linkedKCs.find(id)->second.input.insert(link);
								fin >> link;
							}
							fin >> link;
							while (link != -1) {
								linkedKCs.find(id)->second.output.insert(link);
								fin >> link;
							}
						}
					}
					fin.close();
					linkedPipes.clear();
					if (linkedKCs.size() > 0) {
						for (const auto& obj : linkedKCs) {
							for (const auto& k : obj.second.input) {
								linkedPipes.insert(k);
							}
							for (const auto& k : obj.second.output) {
								linkedPipes.insert(k);
							}
						}
					}
					break;
				}
				case 3: {
					link(groupKC, groupPipe, linkedKCs, linkedPipes);
					break;
				}
				case 4: {
					unlink(linkedKCs, linkedPipes);
					break;
				}
				case 5: {
					list <int> answer;
					bool cycle = false;
					topologicSort(groupPipe, linkedKCs, answer, cycle);
					if (cycle == false) {
						cout << "Результат топологической сортировки: \n";
						for (int i = 1; i <= linkedKCs.size(); i++) {
							cout << "Вершина " << i << " : KC id " << answer.front() << endl;
							answer.pop_front();
						}
					}
					else {
						cout << "граф цикличен!";
					}
					break;
				}
				case 6: {
					for (const auto& obj : linkedKCs) {
						cout << "\n КС id "<<obj.first << "\t input: ";
						for (const auto& links : obj.second.input) {
							cout << links << " ";
						}
						cout << "\t output: ";
						for (const auto& links : obj.second.output) {
							cout << links << " ";
						}
					}
					break;
				}
				case 7: {
					ofstream fout;
					fout.open(getName(), ios::out);
					if (fout.is_open()) {
						fout << linkedKCs.size();
						for (const auto& obj : linkedKCs) {
							fout << "\n" << obj.first << "\t";
							for (const auto& link : obj.second.input) {
								fout << link << "\t";
							}
							fout << "-1 \t";
							for (const auto& link : obj.second.output) {
								fout << link << "\t";
							}
							fout << "-1 \t";
						}
					}
					fout.close();
					break;
				}
				case 8: {
					int first, last;
					double distance;
					bool correct = false;
					list <int> answer;

					first = getIntValue("Введите id начальной КС", 0, 10000);
					if (groupKC.find(first) != groupKC.end()) {
						correct = true;
					}
					else {
						cout << "\nТакого объекта нет! Повторите попытку. ";
					}
					correct = false;
					while (!correct) {
						last = getIntValue("Введите id конечной КС", 0, 10000);
						if (groupKC.find(last) != groupKC.end()) {
							  correct = true;
						}
						else {
							cout << "\nТакого объекта нет! Повторите попытку. ";
						}
					}
					minDist(groupPipe, linkedKCs, answer, first, last, distance);
					if (linkedKCs.size() > 0) {
						int countKC = answer.size();
						for (int i = 1; i <= countKC; i++) {
							cout << "Вершина " << i << " : KC id " << answer.front() << endl;
							answer.pop_front();
						}
						cout << "Минимальный путь равен: " << distance << "м. \n";
					}
					else {
						cout << "Путь между станциями не найден.\n";
					}
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
