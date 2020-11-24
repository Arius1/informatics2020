#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "KC.h"
#include "pipe.h"
#include <unordered_map>

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
className& select(std::unordered_map <int ,className>& group) {
	unsigned int index = getIntValue("������� id �������: ", 0u, 10000u);
	std::cout << group.size() <<std::endl;
	if (group.find(index) != group.end()) {
		return group[index];
	}
	else {
		std::cout << "������ \n";
	}
}

template <class className>
void deleteObj(std::unordered_map <int, className>& group) {
	int id = getIntValue("������� id �������", 0u, group.size());
	if (group.find(id) != group.end()) {
		group.erase(id);
		std::cout << "������ � id: " << id << " ������� ������" << std::endl;
	}
	else {
		std::cout << "������ ������� ���!" << std::endl;
	}
}
