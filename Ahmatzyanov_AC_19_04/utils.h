#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "KC.h"
#include "pipe.h"

template <typename T>
int getIntValue(std::string text, T border1, T border2) {
	double value;
	std::cout << text << std::endl;
	while (!(std::cin >> value) || (value - floor(value)) || value < border1 || value > border2) {
		std::cin.clear();
		std::cin.ignore(32767, '\n');
		std::cout << "\n������������ ����! ������� �� " << border1 << " �� " << border2 << ": ";
	}
	int valueInt = (int)value;
	return valueInt;
}

template <typename T>
double getDoubleValue(std::string text, T border1, T border2) {
	double value;
	std::cout << text << std::endl;
	while (!(std::cin >> value) || value < border1 || value > border2) {
		std::cin.clear();
		std::cin.ignore(32767, '\n');
		std::cout << "\n������������ ����! ������� �� " << border1 << " �� " << border2 << ": ";
	}
	return value;
}

template <class className>
className& select(std::vector <className>& group) {
	unsigned int index = getIntValue("������� ����� �������: ", 1u, group.size());
	return group[index - 1];
}

template <class className>
void deleteObj(std::vector <className>& group) {
	int id = getIntValue("������� id �������", 0u, 10000u);
	int i = 0;
	for (auto& obj : group) {
		if (obj.id == id) {
			group.erase(group.begin() + i);
			std::cout << "������ � id: " << id << " ������� ������" << std::endl;
		}
		i++;
	}
	if (i == group.size()) {
		std::cout << "������ ������� ���!" << std::endl;
	}
}
