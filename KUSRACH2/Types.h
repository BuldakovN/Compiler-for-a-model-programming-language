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
extern std::unordered_map<std::string, int> TN;	//������� �����
extern std::unordered_map<std::string, int> TI;	//������� ���������������

//�������� ������� ������
enum class Table_index {
	TW_index = 1,	//������� ��������� ����
	TL_index = 2,	//������� �������������
	TN_index = 3,	//������� �����
	TI_index = 4	//������� ���������������
};