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
		std::cout << "\nНеправильный ввод! Введите от " << border1 << " до " << border2 << ": ";
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
		std::cout << "\nНеправильный ввод! Введите от " << border1 << " до " << border2 << ": ";
	}
	return value;
}

template <class className>
className& select(std::unordered_map <int ,className>& group) {
	unsigned int index = getIntValue("Введите id объекта: ", 0u, 10000u);
	std::cout << group.size() <<std::endl;
	if (group.find(index) != group.end()) {
		return group[index];
	}
	else {
		std::cout << "Ошибка \n";
	}
}

template <class className>
void deleteObj(std::unordered_map <int, className>& group) {
	int id = getIntValue("Введите id объекта", 0u, group.size());
	if (group.find(id) != group.end()) {
		group.erase(id);
		std::cout << "Объект с id: " << id << " успешно удален" << std::endl;
	}
	else {
		std::cout << "Такого объекта нет!" << std::endl;
	}
}
