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
		std::cout << "\n������������ ����! ������� �� " << border1 << " �� " << border2 << ": ";
	}
	return value;
}

template <class vec>
vec& select(std::vector <vec>& group) {
	unsigned int index = getValue("������� ����� �������: ", 1u, group.size());
	return group[index - 1];
}

template <class vec>
void deleteObj(std::vector <vec>& group) {
	int id = getValue("������� id �������", 0u, 10000u);
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


template <class vec>
std::vector <int> findByID(std::vector <vec>& group) {
	std::vector <int> result;
	int id = getValue("������� id �������", 0u, 10000u);
	int i = 0;
	for (auto& p : group) {
		if (p.id == id) {
			result.push_back(i);
		}
		i++;
	}
	return result;
}