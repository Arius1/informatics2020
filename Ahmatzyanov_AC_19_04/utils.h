#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "KC.h"
#include "pipe.h"

template <typename T>
T getValue(std::string text, T border1, T border2) {
	T value;
	std::cout << text << std::endl;
	while (!(std::cin >> value) || value < border1 || value > border2) {
		std::cin.clear();
		std::cin.ignore(32767, '\n');
		std::cout << "\nНеправильный ввод! Введите от " << border1 << " до " << border2 << ": ";
	}
	return value;
}

template <class vec>
vec& select(std::vector <vec>& group) {
	unsigned int index = getValue("Введите номер объекта: ", 1u, group.size());
	return group[index - 1];
}
template <class vec>
void deleteObj(std::vector <vec>& group) {
	int i = getValue("Введите номер объекта", 1u, group.size())-1;
	group.erase(group.begin() + i);
}
