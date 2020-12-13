#include "utils.h"

using namespace std;

void check(bool& act) {
	int check = getIntValue("��������� ��������? 0 - ���/ 1 - ��: ", 0, 1);
	if (check == 0) {
		act = !act;
	}
}

std::string getName()
{	
	std::string name;
	std::cout << "������� �������� ����� � �����������: " << std::endl;
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
			inputKC = getIntValue("������� id ��������� ��", 0, 10000);
			if (groupKC.find(inputKC) != groupKC.end()) {
				correct = true;
			}
			else {
				cout << "\n������ ������� ���! ��������� �������. ";
			}
		}
		correct = false;
		while (!correct) {
			outputKC = getIntValue("������� id �������� ��", 0, 10000);
			if (groupKC.find(outputKC) != groupKC.end()) {
				correct = true;
			}
			else {
				cout << "\n������ ������� ���! ��������� �������. ";
			}
		}
		correct = false;
		while (!correct) {
			pipeId = getIntValue("������� id �����", 0, 10000);
			if (groupPipe.find(pipeId) != groupPipe.end() and linkedPipes.find(pipeId) == linkedPipes.end()) {
				cout << "\n����� �����������. \n" ;
				correct = true;
			}
			else if  (linkedPipes.find(pipeId) != linkedPipes.end()) {
				cout << "\n������ ��� ���������! ��������� �������. ";
			}
			else {
				cout << "\n������ ������� ���! ��������� �������. ";
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
			inputKC = getIntValue("������� id ������ ��", 0, 10000);
			if (linkedKCs.find(inputKC) != linkedKCs.end() and linkedKCs.find(inputKC)->second.output.size() != 0) {
				correct = true;
			}
			else {
				cout << "\n������ ������� ��� ����� ���! ��������� �������. ";
			}
		}
		correct = false;
		while (!correct) {
			outputKC = getIntValue("������� id ������ ��", 0, 10000);
			if (linkedKCs.find(outputKC) != linkedKCs.end() and linkedKCs.find(outputKC)->second.input.size() != 0) {
				correct = true;
			}
			else {
				cout << "\n������ ������� ��� ����� ���! ��������� �������. ";
			}
		}
		for (auto& linkPipe : linkedKCs.find(inputKC)->second.output) {
			if (linkedKCs.find(outputKC)->second.input.find(linkPipe) != linkedKCs.find(outputKC)->second.input.end()) {
				linkedKCs.find(inputKC)->second.output.erase(linkPipe);
				linkedKCs.find(outputKC)->second.input.erase(linkPipe);
				linkedPipes.erase(linkPipe);
				cout << "����� �������.\n";
				break;
			}
		}
		check(act);
	}
}

void Menu() {
	cout << "\n1. ������� ����� �����\n"
		<< "2. ������� ����� ��\n"
		<< "3. ������� ����� � �� �� �����\n"
		<< "4. ����� ����� � �� � ���� \n"
		<< "5. ������� �����\n"
		<< "6. ������� ��\n"
		<< "7. ������������� ������ ����\n"
		<< "8. ������������� ���������� ���������� ������� �� \n"
		<< "9. ������� ������\n"
		<< "10. ����� ������\n"
		<< "11. ������ � ���\n"
		<< "\n"
		<< "0. �����\n";
}