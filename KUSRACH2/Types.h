#pragma once
#include <string>
#include <unordered_map>
#include <iostream>
#include <stack>
#include <vector>
#include <fstream>
#include <unordered_map>
extern std::unordered_map<std::string, int> TW;
extern std::unordered_map<std::string, int> TL;
extern std::unordered_map<std::string, int> TN;	//таблица чисел
extern std::unordered_map<std::string, int> TI;	//таблица идентификаторов

//значения таблицы лексем
enum class Table_index {
	TW_index = 1,	//таблица служебных слов
	TL_index = 2,	//таблица ограничителей
	TN_index = 3,	//таблица чисел
	TI_index = 4	//таблица идентификаторов
};