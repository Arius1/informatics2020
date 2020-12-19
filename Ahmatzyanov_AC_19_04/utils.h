#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "KC.h"
#include "pipe.h"
#include "gts.h"
#include <unordered_map>
#include <unordered_set>

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
	while (1) {
		unsigned int index = getIntValue("Введите id объекта: ", 0u, 10000u);
		if (group.find(index) != group.end()) {
			return group[index];
		}
		else {
			std::cout << "Ошибка! Такого объекта нет! \n";
		}
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

void link(const std::unordered_map <int, KC>& groupKC, const std::unordered_map <int, pipe>& groupPipe, std::unordered_map <int, gts>& linkedKCs, std::unordered_set <int>& linkedPipes);
void unlink(std::unordered_map <int, gts>& linkedKCs, std::unordered_set <int>& linkedPipes);
void check(bool& act);
std::string getName();
void Menu();


void topologicSort(const std::unordered_map <int, pipe>& groupPipe, const std::unordered_map <int, gts>& KCs, std::list <int>& answer, bool& cycle);
void minDist(const std::unordered_map <int, pipe>& groupPipe, const std::unordered_map <int, gts>& KCs, std::list <int>& answer, const int& first, const int& last, double& distance);
void maxFlow(const std::unordered_map <int, pipe>& groupPipe, const std::unordered_map <int, gts>& KCs, const int& first, const int& last, int& max);

template <class className, typename par>
using Filter = bool(*)(className& object, par parameter);

bool checkByName(KC& kc, std::string parameter);
bool checkByStatus(pipe& p, bool parameter);
bool checkByWorkingPercent(KC& kc, double parameter);
bool checkPipeByID(pipe& obj, int parameter);

template <class className, typename T>
std::vector <int> findObjectByFilter(std::unordered_map<int, className>& group, Filter <className, T> f, T parameter) {
	std::vector <int> result;
	for (auto& p : group) {
		if (f(p.second, parameter)) {
			result.push_back(p.first);
		}
	}
	return result;
}

template <class className>
void searchCout(std::unordered_map <int, className> group, const std::vector <int>& result) {
	if (result.size() > 0) {
		for (auto i : result) {
			std::cout << group[i];
		}
	}
	else {
		std::cout << "Таких объектов нет! \n";
	}
}