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

void link(const unordered_map <int, KC>& groupKC, const unordered_map <int, pipe>& groupPipe, unordered_map <int, gts>& linkedKCs, unordered_set <int>& linkedPipes)
{
	int inputKC;
	int outputKC;
	int pipeId;
	bool act = true;
	bool correct = false;
	while (act) {
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
		correct = false;
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