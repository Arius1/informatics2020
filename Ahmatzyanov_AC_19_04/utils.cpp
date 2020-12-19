#include "utils.h"

using namespace std;

void check(bool& act) {
	int check = getIntValue("Повторить действие? 0 - нет/ 1 - да: ", 0, 1);
	if (check == 0) {
		act = !act;
	}
}

std::string getName()
{	
	std::string name;
	std::cout << "Введите название файла с расширением: " << std::endl;
	std::cin.get();
	std::getline(std::cin, name);
	return name;
}


bool checkByName(KC& kc, string parameter) {
	return kc.Name == parameter;
}
bool checkByStatus(pipe& p, bool parameter) {
	return p.repairStatus == parameter;
}
bool checkByWorkingPercent(KC& kc, double parameter) {
	return (((double)kc.workingWorkshopCount / (double)kc.workshopCount) * 100) >= parameter;
}
bool checkPipeByID(pipe& obj, int parameter) {
	return obj.getId() == parameter;
}

void correctKCsSelect(const unordered_map <int, KC>& groupKC, int& inputKC, int& outputKC) {
	bool correct = false;
	while (!correct) {
		inputKC = getIntValue("Введите id начальной КС", 0, 10000);
		if (groupKC.find(inputKC) != groupKC.end()) {
			correct = true;
		}
		else {
			cout << "\nТакого объекта нет! Повторите попытку. ";
		}
	}
	correct = false;
	while (!correct) {
		outputKC = getIntValue("Введите id конечной КС", 0, 10000);
		if (groupKC.find(outputKC) != groupKC.end()) {
			correct = true;
		}
		else {
			cout << "\nТакого объекта нет! Повторите попытку. ";
		}
	}
}

void link(const unordered_map <int, KC>& groupKC, const unordered_map <int, pipe>& groupPipe, unordered_map <int, gts>& linkedKCs, unordered_set <int>& linkedPipes)
{
	int inputKC;
	int outputKC;
	int pipeId;
	bool act = true;
	bool correct = false;
	while (act) {
		correctKCsSelect(groupKC, inputKC, outputKC);
		while (!correct) {
			pipeId = getIntValue("Введите id трубы", 0, 10000);
			if (groupPipe.find(pipeId) != groupPipe.end() and linkedPipes.find(pipeId) == linkedPipes.end()) {
				cout << "\nСвязь установлена. \n" ;
				correct = true;
			}
			else if  (linkedPipes.find(pipeId) != linkedPipes.end()) {
				cout << "\nОбъект уже подключен! Повторите попытку. ";
			}
			else {
				cout << "\nТакого объекта нет! Повторите попытку. ";
			}
		}
		linkedKCs.find(inputKC)->second.output.insert(pipeId);
		linkedKCs.find(outputKC)->second.input.insert(pipeId);
		linkedPipes.insert(pipeId);
		check(act);
	}
}

void unlink(std::unordered_map<int, gts>& linkedKCs, std::unordered_set<int>& linkedPipes)
{
	int inputKC;
	int outputKC;
	bool act = true;
	bool correct = false;
	while (act) {
		while (!correct) {
			inputKC = getIntValue("Введите id первой КС", 0, 10000);
			if (linkedKCs.find(inputKC) != linkedKCs.end() and linkedKCs.find(inputKC)->second.output.size() != 0) {
				correct = true;
			}
			else {
				cout << "\nТакого объекта или связи нет! Повторите попытку. ";
			}
		}
		correct = false;
		while (!correct) {
			outputKC = getIntValue("Введите id второй КС", 0, 10000);
			if (linkedKCs.find(outputKC) != linkedKCs.end() and linkedKCs.find(outputKC)->second.input.size() != 0) {
				correct = true;
			}
			else {
				cout << "\nТакого объекта или связи нет! Повторите попытку. ";
			}
		}
		for (auto& linkPipe : linkedKCs.find(inputKC)->second.output) {
			if (linkedKCs.find(outputKC)->second.input.find(linkPipe) != linkedKCs.find(outputKC)->second.input.end()) {
				linkedKCs.find(inputKC)->second.output.erase(linkPipe);
				linkedKCs.find(outputKC)->second.input.erase(linkPipe);
				linkedPipes.erase(linkPipe);
				cout << "Связь удалена.\n";
				break;
			}
		}
		check(act);
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
		<< "11. Работа с ГТС\n"
		<< "\n"
		<< "0. Выход\n";
}

void findLinkedKCs(unordered_map <int, int>& linkedKCs, const unordered_map <int, pipe>& groupPipe, const unordered_map <int, gts>& KCs, const int& id) {
	for (auto i : KCs.find(id)->second.output) {
		if (groupPipe.find(i) != groupPipe.end() and groupPipe.find(i)->second.repairStatus == 0) {
			for (auto j : KCs) {
				if (j.second.input.find(i) != j.second.input.end()) {
					linkedKCs.emplace(j.first, groupPipe.find(i)->first);
				}
			}
		}
	}
}
void reverseFindLinkedKCs(unordered_map <int, int>& linkedKCs, const unordered_map <int, pipe>& groupPipe, const unordered_map <int, gts>& KCs, const int& id) { //обратный проход
	for (auto i : KCs.find(id)->second.input) {
		if (groupPipe.find(i) != groupPipe.end() and groupPipe.find(i)->second.repairStatus == 0) {
			for (auto j : KCs) {
				if (j.second.output.find(i) != j.second.output.end()) {
					linkedKCs.emplace(j.first, groupPipe.find(i)->first);
				}
			}
		}
	}
}

void stepDown(list <int>& answer, const unordered_map <int, pipe>& groupPipe, const unordered_map <int, gts>& KCs, unordered_map <int, bool>& visited, int id, bool& cycle) {
	if (visited.find(id)->second == false) {
		unordered_map <int, int> linkedKCs; //ключ - КС | значение - труба
		visited[id] = true;
		findLinkedKCs(linkedKCs, groupPipe, KCs, id);
		for (auto i : linkedKCs) { //для всех найденных КС делаем проход
			stepDown(answer, groupPipe, KCs, visited, i.first, cycle);
		}
		answer.push_front(id);
	}
	else {
		cycle = true;
	}
}

void topologicSort(const unordered_map <int, pipe>& groupPipe, const unordered_map <int, gts>& KCs, list <int>& answer, bool& cycle) {
	unordered_map <int, bool> visited;
	cout << "Проверка на цикличность:";
	for (auto i : KCs) {
		for (auto j : KCs) {//метки посещения на false
			visited[j.first] = false;
		}
		stepDown(answer, groupPipe, KCs, visited, i.first, cycle);
	}
	if (cycle == false) {
		cout << "Граф ацикличен. Включение сортировки... \n";
		for (auto i : KCs) { //метки посещения на false
			visited[i.first] = false;
		}
		for (auto i : KCs) { //первый шаг для любой вершины
			if (visited.find(i.first)->second == false) {
				stepDown(answer, groupPipe, KCs, visited, i.first, cycle);
			}
		}
		cycle = false; // в ходе работы найдет посещенную вершину
	}
}

void comparingStepDown(const unordered_map <int, pipe>& groupPipe, const unordered_map <int, gts>& KCs, unordered_map <int, double>& vertexes, const int& current, const int& last) {
	if (current != last) {
		unordered_map <int, int> linkedKCs;
		findLinkedKCs(linkedKCs, groupPipe, KCs, current);
		for (auto i : linkedKCs) {
			if (vertexes.find(i.first)->second >= (vertexes.find(current)->second + groupPipe.find(i.second)->second.length)) { //если метка следующей вершины больше (текущей + длины трубы)
				vertexes[i.first] = vertexes.find(current)->second + groupPipe.find(i.second)->second.length;
				if (i.first != last) {
					comparingStepDown(groupPipe, KCs, vertexes, i.first, last);
				}
			}
		}
	}
}

void findWay(const unordered_map <int, pipe>& groupPipe, const unordered_map <int, gts>& KCs, list <int>& answer, unordered_map <int, double> vertexes, const int& first, const int& current) {
	unordered_map <int, int> linkedKCs;
	answer.push_front(current);
	reverseFindLinkedKCs(linkedKCs, groupPipe, KCs, current);
	for (auto i : linkedKCs) {
		if (vertexes.find(current)->second == (vertexes.find(i.first)->second + groupPipe.find(i.second)->second.length)) { //сумма предыдущей метки и длины трубы равна текущей
			findWay(groupPipe, KCs, answer, vertexes, first, i.first);
		}
	}
}

void minDist(const unordered_map <int, pipe>& groupPipe, const unordered_map <int, gts>& KCs, list <int>& answer, const int& first, const int& last, double& distance) {
	unordered_map <int, double> vertexes; // ключ - КС | значение - вес пути
	for (auto i : KCs) {
		vertexes[i.first] = INFINITY;
	}
	vertexes[first] = 0;
	comparingStepDown(groupPipe, KCs, vertexes, first, last);
	if (vertexes.find(last)->second != INFINITY) {
		findWay(groupPipe, KCs, answer, vertexes, first, last);
		distance = vertexes.find(last)->second;
	}
}

int flowStepDown(const unordered_map <int, pipe>& groupPipe, const unordered_map <int, gts>& KCs, unordered_map <int, int> vertexes, //int flowStep, так как элемент логики
	unordered_map <int, bool>& visited, unordered_map <int, int> perf, const int& current, const int& last)
{
	unordered_map <int, int> linkedKCs; //ключ - КС | значение - труба
	if (current == last) {
		return vertexes.find(current)->second;
	}
	visited[current] = true;
	findLinkedKCs(linkedKCs, groupPipe, KCs, current);
	for (auto i : linkedKCs) {
		int flow = min((groupPipe.find(i.first)->second.maxPerformance - perf.find(i.first)->second), vertexes.find(current)->second); // минимум от (Макс поток - поток) и выходного потока текущего КС
		if (flow > 0 and visited.find(current)->second == false) {
			vertexes[i.first] = flow;
			int delta = flowStepDown(groupPipe, KCs, vertexes, visited, perf, i.first, last);
			if (delta > 0) {
				perf[i.first] += delta; //поднимаем потоки минимум подподтоков
				return delta; 
			}
		}
	}
	return 0; //если не найдено путей
}

void maxFlow(const unordered_map <int, pipe>& groupPipe, const unordered_map <int, gts>& KCs, unordered_map <int, int>& perf, const int& first, const int& last, int& max) {
	//map perf = труба - поток
	unordered_map <int, int> vertexes; //кс - выходной поток
	unordered_map <int, bool> visited;
	
	while (1) {
		for (auto i : KCs) {//метки посещения на false
			visited[i.first] = false;
			vertexes[i.first] = 0;
		}
		vertexes[first] = INT_MAX;
		int delta = flowStepDown(groupPipe, KCs, vertexes, visited, perf, first, last);
		if (delta == 0) {
			break;
		}
	}
}