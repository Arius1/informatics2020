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

