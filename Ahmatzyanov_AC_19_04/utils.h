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
	int i = getValue("������� ����� �������", 1u, group.size()) - 1;
	group.erase(group.begin() + i);
}

//template <class vec>
//int findObjByID(const std::vector <vec>& group, int id) {
//	for (auto& obj : group) {
//		if (obj.id == id) {
//			return group;
//		}
//		else {
//			return -1;
//		}
//	}
//}
//vector <int> findPipeByID(const vector <pipe>& group, int id) {
//	vector <int> result;
//	int i = 0;
//	for (auto& p : group) {
//		if (p.id == id) {
//			result.push_back(i);
//		}
//		i++;
//	}
//	return result;
//}