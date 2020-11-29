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

