#include "utils.h"

void check(bool& flag) {
	int check = getIntValue("��������� ��������? 0 - ���/ 1 - ��: ", 0, 1);
	if (check == 0) {
		flag = !flag;
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

