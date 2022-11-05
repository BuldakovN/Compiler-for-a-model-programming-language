//#pragma once
//#include <string>
//#include <unordered_map>
//#include <iostream>
//#include <stack>
//#include <vector>
//#include <fstream>
//#include <unordered_map>
//using namespace std;
//std::unordered_map<std::string, int> TW = {		//������� ��������� ����
//	{"true",1},
//	{"false",2},
//	{"not",3},
//	{"let",4},
//	{"if",5},
//	{"then",6},
//	{"else",7},
//	{"end_else",8},
//	{"for",9},
//	{"do while",10},
//	{"input",11},
//	{"output",12},
//	{"or",13},
//	{"and",14},
//	{"not",15},
//	{"loop",16}
//};
//std::unordered_map<std::string, int> TL = {		//������� �������������
//	{"{",1},
//	{"}",2},
//	{"+",3},
//	{"-",4},
//	{"*",5},
//	{"/",6},
//	{"< >",7},
//	{"=",8},
//	{"<",9},
//	{">",10},
//	{"<=",11},
//	{">=",12},
//	{"(",13},
//	{")",14},
//	{"/*",15},
//	{"*/",16},
//	{"%",17},			//����� ���
//	{"!",18},			//�������������� ���
//	{"$",19},			//���������� ���
//	{".",20},
//	{",",21},
//	{":",22},
//	{";",23}
//};
//std::unordered_map<std::string, int> TN = {};	//������� �����
//std::unordered_map<std::string, int> TI = {};	//������� ���������������
//
////�������� ������� ������
//enum class Table_index {
//	TW_index = 1,	//������� ��������� ����
//	TL_index = 2,	//������� �������������
//	TN_index = 3,	//������� �����
//	TI_index = 4	//������� ���������������
//};
//
////��������� ��������� ��������
//enum States {
//	ER = 0,		//������(�������� ���������)
//	H,		//������
//	I,		//��������������
//	N2,		//�������� �����
//	N8,		//������������ �����
//	N10,	//���������� �����
//	N16,	//����������������� �����
//	C1,		//�����������(������)
//	C2,		//�����������(����������)
//	C3,		//�����������(�����)
//	M1,		//������, ������ ��� �����, �������
//	M2,		//������, ������ ��� �����, �����
//	P1,		//�����
//	P2,		//������ ����� �����
//	B,		//������ B
//	O,		//������ O
//	D,		//������ D
//	HX,		//������ H
//	E11,	//������ E
//	E12,	//������� ����� � ���������������� �����
//	E13,	//������� ����� � ���������������� �����
//	E22,	//������� ����� � ���������������� �����
//	ZN,		//���� ������� ����� � ���������������� �����
//	E21,	//���� ������� ����� � ���������������� �����
//	OG,		//������������
//	V,		//�����(�������� ���������)
//};
//
//class Lexer
//{
//	int d;										//���������� ��� ������������ ������ �������� ���������
//	char CH;									//������� ������
//	std::string S;								//������ ��� ������������ �������� �������
//	enum States CS;								//������� ���������
//	std::string filename;						//��� ����� � �����
//	std::fstream lexeme_file;					//���� � ���������
//	std::fstream example_program;				//��������� ��� �������
//
//
//	bool gc();									//��������� ���������� ���������� ������� � ���������� CH
//	bool let();									//���������� �������, �����������, �������� �� ���������� CH ������
//	bool digit();								//���������� �������, �����������, �������� �� ���������� CH ������
//	void nill();								//��������� ������� ������ S
//	void add();									//��������� ���������� ���������� ������� � ����� 
//	int look(enum class Table_index t);			//������� ������ ������� �� ������ S � ������� t
//	int put(enum class Table_index t);			//��������� ������ ������� �� ������ S � ������� t
//	void out(enum class Table_index, int);		//��������� ������ ���� ����� (n,t) � ���� ������
//	bool check_hex();							//���������� �������, �����������, �������� �� ���������� CH ������ ��� ������ �� ��������� a..fA..F
//	bool AFH();									//���������� �������, �������� check_hex, �� ������������� ���������, �������� �� CH ������ H ��� h
//	void translate(int);						//��������� �������� ����� � ������ �� ������� ��������� �� ��������� base � ���������� ��
//	void convert();								//��������� �������� ����� � ������ �� ��������� ����� ������ � ���������� �����
//
//public:
//	Lexer(std::string);
//	bool scanner();								//������ �������
//	void print_lexems();
//	~Lexer();
//};
//
//std::unordered_map<std::string, int> TW = {		//������� ��������� ����
//	{"true",1},
//	{"false",2},
//	{"not",3},
//	{"let",4},
//	{"if",5},
//	{"then",6},
//	{"else",7},
//	{"end_else",8},
//	{"for",9},
//	{"do while",10},
//	{"input",11},
//	{"output",12},
//	{"or",13},
//	{"and",14},
//	{"not",15},
//	{"loop",16}
//};
//std::unordered_map<std::string, int> TL = {		//������� �������������
//	{"{",1},
//	{"}",2},
//	{"+",3},
//	{"-",4},
//	{"*",5},
//	{"/",6},
//	{"< >",7},
//	{"=",8},
//	{"<",9},
//	{">",10},
//	{"<=",11},
//	{">=",12},
//	{"(",13},
//	{")",14},
//	{"/*",15},
//	{"*/",16},
//	{"%",17},			//����� ���
//	{"!",18},			//�������������� ���
//	{"$",19},			//���������� ���
//	{".",20},
//	{",",21},
//	{":",22},
//	{";",23}
//};
//std::unordered_map<std::string, int> TN = {};	//������� �����
//std::unordered_map<std::string, int> TI = {};	//������� ���������������
//
//
//Lexer::Lexer(string p_filename) :
//	S(""),
//	d(0),
//	CH(' '),
//	CS(States::H),
//	filename(p_filename)
//{
//}
//
//bool Lexer::scanner()
//{
//	example_program.open(filename, ios::in);
//	lexeme_file.open("lexems " + filename, ios::out);
//
//	gc();
//	int z = 0;
//	do {
//		switch (CS) {
//		case H: {
//			while ((CH == ' ' || CH == '\n' || CH == '\t') && !example_program.eof()) { gc(); }
//			if (example_program.eof()) {
//				CS = ER;
//				break;
//			}
//			if (let()) {
//				nill();
//				add();
//				gc();
//				CS = I;
//			}
//			else if (CH == '0' || CH == '1') {
//				nill();
//				CS = N2;
//				add();
//				gc();
//			}
//			else if (CH >= '2' && CH <= '7') {
//				nill();
//				CS = N8;
//				add();
//				gc();
//			}
//			else if (CH >= '8' && CH <= '9') {
//				nill();
//				CS = N10;
//				add();
//				gc();
//			}
//			else if (CH == '.') {
//				nill();
//				add();
//				gc();
//				CS = P1;
//			}
//			else if (CH == '/') {
//				gc();
//				CS = C1;
//			}
//			else if (CH == '<') {
//				gc();
//				CS = M1;
//			}
//			else if (CH == '>') {
//				gc();
//				CS = M2;
//			}
//			else if (CH == '}') {
//				out(Table_index::TL_index, 2);
//				if (example_program.eof())
//					CS = V;
//				else
//					gc();
//				CS = H;
//			}
//			else CS = OG;
//			break;
//		}
//
//		case I: {
//			while (let() || digit() || CH == '_') { add(); gc(); }
//			if (S == "do") {
//				string do_while_check;
//				gc();
//				do {
//					do_while_check += CH;
//					gc();
//				} while (let());
//				if (do_while_check == "while")
//					S += " " + do_while_check;
//				else
//					CS = ER;
//			}
//			z = look(Table_index::TW_index);
//			if (z != 0) {
//				out(Table_index::TW_index, z);
//				CS = H;
//			}
//			else {
//				z = put(Table_index::TI_index);
//				out(Table_index::TI_index, z);
//				CS = H;
//			}
//			break;
//		}
//
//		case N2: {
//			while (CH == '0' || CH == '1') { add(); gc(); }
//			if (CH >= '2' && CH <= '7')
//				CS = N8;
//			else if (CH == '8' || CH == '9')
//				CS = N10;
//			else if (CH == 'A' || CH == 'a' || CH == 'C' || CH == 'c' || CH == 'F' || CH == 'f')
//				CS = N16;
//			else if (CH == 'E' || CH == 'e') {
//				add();
//				gc();
//				CS = E11;
//			}
//			else if (CH == 'D' || CH == 'd') {
//				add();
//				gc();
//				CS = D;
//			}
//			else if (CH == 'O' || CH == 'o')
//				CS = O;
//			else if (CH == 'H' || CH == 'h') {
//				gc();
//				CS = HX;
//			}
//			else if (CH == '.') {
//				add();
//				gc();
//				CS = P1;
//			}
//			else if (CH == 'B' || CH == 'b') {
//				add();
//				gc();
//				CS = B;
//			}
//			else if (let())
//				CS = ER;
//			else
//				CS = N10;
//			break;
//		}
//
//		case N8: {
//			while (CH >= '2' && CH <= '7') { add(); gc(); }
//			if (CH == '8' || CH == '9') { CS = N10; }
//			else if (CH == 'A' || CH == 'a' || CH == 'B' || CH == 'b' || CH == 'C' || CH == 'c' || CH == 'F' || CH == 'f')
//				CS = N16;
//			else if (CH == 'E' || CH == 'e') {
//				add();
//				gc();
//				CS = E11;
//			}
//			else if (CH == 'D' || CH == 'd') {
//				add();
//				gc();
//				CS = D;
//			}
//			else if (CH == 'H' || CH == 'h') {
//				gc();
//				CS = HX;
//			}
//			else if (CH == '.') {
//				add();
//				gc();
//				CS = P1;
//			}
//			else if (CH == 'O' || CH == 'o') {
//				gc();
//				CS = O;
//			}
//			else if (let())
//				CS = ER;
//			else
//				CS = N10;
//			break;
//		}
//
//		case N10: {
//			while (CH == '8' || CH == '9') { add(); gc(); }
//			if (CH == 'A' || CH == 'a' || CH == 'B' || CH == 'b' || CH == 'C' || CH == 'c' || CH == 'F' || CH == 'f')
//				CS = N16;
//			else if (CH == 'E' || CH == 'e') {
//				add();
//				gc();
//				CS = E11;
//			}
//			else if (CH == 'H' || CH == 'h') {
//				gc();
//				CS = HX;
//			}
//			else if (CH == '.') {
//				add();
//				gc();
//				CS = P1;
//			}
//			else if (CH == 'D' || CH == 'd') {
//				add();
//				gc();
//				CS = D;
//			}
//			else if (let())
//				CS = ER;
//			else {
//				z = put(Table_index::TN_index);
//				out(Table_index::TN_index, z);
//				CS = H;
//			}
//			break;
//		}
//
//		case N16: {
//			while (check_hex()) { add(); gc(); }
//
//			if (CH == 'H' || CH == 'h') {
//				gc();
//				CS = HX;
//			}
//			else
//				CS = ER;
//			break;
//		}
//
//		case B: {
//			if (check_hex())
//				CS = N16;
//			else if (CH == 'H' || CH == 'h') {
//				gc();
//				CS = HX;
//			}
//			else if (let())
//				CS = ER;
//			else {
//				translate(2);
//				z = put(Table_index::TN_index);
//				out(Table_index::TN_index, z);
//				CS = H;
//			}
//			break;
//		}
//
//		case O: {
//			if (let() || digit())
//				CS = ER;
//			else {
//				translate(8);
//				z = put(Table_index::TN_index);
//				out(Table_index::TN_index, z);
//				CS = H;
//			}
//			break;
//		}
//
//		case D: {
//			if (CH == 'H' || CH == 'h') {
//				gc();
//				CS = HX;
//			}
//			else if (check_hex())
//				CS = N16;
//			else if (let())
//				CS = ER;
//			else {
//				z = put(Table_index::TN_index);
//				out(Table_index::TN_index, z);
//				CS = H;
//			}
//			break;
//		}
//
//		case HX: {
//			if (let() || digit())
//				CS = ER;
//			else {
//				translate(16);
//				z = put(Table_index::TN_index);
//				out(Table_index::TN_index, z);
//				CS = H;
//			}
//			break;
//		}
//
//		case E11: {
//			if (digit()) {
//				add();
//				gc();
//				CS = E12;
//			}
//			else if (CH == '+' || CH == '-') {
//				add();
//				gc();
//				CS = ZN;
//			}
//			else if (CH == 'H' || CH == 'h') {
//				gc();
//				CS = HX;
//			}
//			else if (check_hex()) {
//				add();
//				gc();
//				CS = N16;
//			}
//			else
//				CS = ER;
//			break;
//		}
//
//		case ZN: {
//			if (digit()) {
//				add();
//				gc();
//				CS = E13;
//			}
//			else
//				CS = ER;
//			break;
//		}
//
//		case E12: {
//			while (digit()) { add(); gc(); }
//			if (check_hex())
//				CS = N16;
//			else if (CH == 'H' || CH == 'h') {
//				gc();
//				CS = HX;
//			}
//			else if (let())
//				CS = ER;
//			else {
//				convert();
//				z = put(Table_index::TN_index);
//				out(Table_index::TN_index, z);
//				CS = H;
//			}
//			break;
//		}
//
//		case E13: {
//			while (digit()) { add(); gc(); }
//			if (let() || CH == '.')
//				CS = ER;
//			else {
//				convert();
//				z = put(Table_index::TN_index);
//				out(Table_index::TN_index, z);
//				CS = H;
//			}
//			break;
//		}
//
//		case P1: {
//			if (digit())
//				CS = P2;
//			else
//				CS = ER;
//			break;
//		}
//
//		case P2: {
//			while (digit()) { add(); gc(); }
//			if (CH == 'E' || CH == 'e') {
//				add();
//				gc();
//				CS = E21;
//			}
//			else if (let() || CH == '.') {
//				CS = ER;
//			}
//			else {
//				convert();
//				z = put(Table_index::TN_index);
//				out(Table_index::TN_index, z);
//				CS = H;
//			}
//			break;
//		}
//
//		case E21: {
//			if (CH == '+' || CH == '-') {
//				add();
//				gc();
//				CS = ZN;
//			}
//			else if (digit())
//				CS = E22;
//			else
//				CS = ER;
//			break;
//		}
//
//		case E22: {
//			while (digit()) { add(); gc(); }
//			if (let() || CH == '.')
//				CS = ER;
//			else {
//				convert();
//				z = put(Table_index::TN_index);
//				out(Table_index::TN_index, z)
//					; CS = H;
//			}
//			break;
//		}
//
//		case C1: {
//			if (CH == '*') {
//				gc();
//				CS = C2;
//			}
//			else {
//				out(Table_index::TN_index, look(Table_index::TN_index));
//				CS = H;
//			}
//			break;
//		}
//
//		case C2: {
//			bool flag = 0;	//���� ����� �����
//			while (CH != '*' && !flag && CH != '}') { flag = gc(); }
//			if (CH == '}' || flag)
//				CS = ER;
//			else {
//				gc();
//				CS = C3;
//			}
//			break;
//		}
//
//		case C3: {
//			if (CH == '/') {
//				gc();
//				CS = H;
//			}
//			else
//				CS = C2;
//			break;
//		}
//
//		case M1: {
//			if (CH == '>') {
//				gc();
//				out(Table_index::TL_index, 7);
//				CS = H;
//			}
//			else if (CH == '=') {
//				gc();
//				out(Table_index::TL_index, 11);
//				CS = H;
//			}
//			else {
//				out(Table_index::TL_index, 9);
//				CS = H;
//			}
//			break;
//		}
//
//		case M2: {
//			if (CH == '=') {
//				gc();
//				out(Table_index::TL_index, 12);
//				CS = H;
//			}
//			else {
//				out(Table_index::TL_index, 10);
//				CS = H;
//			}
//			break;
//		}
//
//		case OG: {
//			nill();
//			add();
//			z = look(Table_index::TL_index);
//			if (z != 0) {
//				gc();
//				out(Table_index::TL_index, z);
//				CS = H;
//			}
//			else CS = ER;
//			break;
//		}
//		}
//	} while (CS != V && CS != ER);
//	example_program.close();
//	lexeme_file.close();
//	cout << "����������� ������ ������� ��������" << endl;
//	return CS;
//}
//
//void Lexer::print_lexems()
//{
//	struct lexeme
//	{
//		int id;
//		string value;
//		Table_index tab;
//		int number;
//	};
//	lexeme LEX;
//	static int number = 1;
//	lexeme_file.open("lexems " + filename);
//	string lex;
//	lexeme_file >> lex;
//	while (!lexeme_file.eof()) {
//		LEX.tab = (Table_index)(lex[1] - 48);
//		LEX.id = stoi(lex.substr(3, lex.size() - 4));
//		switch (LEX.tab)
//		{
//		case(Table_index::TW_index):
//			for (auto elem : TW)
//				if (elem.second == LEX.id) LEX.value = elem.first;
//			break;
//		case(Table_index::TL_index):
//			for (auto elem : TL)
//				if (elem.second == LEX.id) LEX.value = elem.first;
//			break;
//		case(Table_index::TI_index):
//			for (auto elem : TI)
//				if (elem.second == LEX.id) LEX.value = elem.first;
//			break;
//		case(Table_index::TN_index):
//			for (auto elem : TN)
//				if (elem.second == LEX.id) LEX.value = elem.first;
//			break;
//		default:
//			throw "������������ �������";
//		}
//		LEX.number = number;
//		++number;
//		std::cout << lex << " --- " << LEX.value << endl;
//		lexeme_file >> lex;
//	}
//	lexeme_file.close();
//}
//
//bool Lexer::gc()
//{
//	if (example_program.eof())
//		return true;
//	CH = example_program.get();
//	return example_program.eof();
//
//}
//
//bool Lexer::let()
//{
//	return (CH >= 'a' && CH <= 'z') || (CH >= 'A' && CH <= 'Z');
//}
//
//bool Lexer::digit()
//{
//	return CH >= '0' && CH <= '9';
//}
//
//void Lexer::nill()
//{
//	S = "";
//}
//
//void Lexer::add()
//{
//	S += CH;
//}
//
//int Lexer::look(Table_index t)
//{
//	switch (t)
//	{
//	case Table_index::TW_index:
//		if (TW.find(S) == TW.end())
//			return 0;
//		return TW.at(S);
//		break;
//	case Table_index::TL_index:
//		if (TL.find(S) == TL.end())
//			return 0;
//		return TL.at(S);
//		break;
//	case Table_index::TN_index:
//		if (TN.find(S) == TN.end()) return 0;
//		return TL.at(S);
//		break;
//	case Table_index::TI_index:
//		if (TI.find(S) == TI.end()) return 0;
//		return TL.at(S);
//		break;
//	default:
//		return 0;
//		break;
//	}
//}
//
//int Lexer::put(Table_index t)
//{
//	//cout << (int)t << " " << S << endl;
//	switch (t)
//	{
//	case Table_index::TN_index:
//		if (TN.size() == 0) {
//			TN[S] = 1;
//			return 1;
//		}
//		else if (TN.find(S) == TN.end()) {
//			TN[S] = TN.size() + 1;
//			return TN.size();
//		}
//		else
//			return TN[S];
//		break;
//	case Table_index::TI_index:
//		if (TI.size() == 0) {
//			TI[S] = 1;
//			return 1;
//		}
//		else if (TI.find(S) == TI.end()) {
//			TI[S] = TI.size() + 1;
//			return TI.size();
//		}
//		else
//			return TI[S];
//		break;
//	default:
//		return 0;
//		break;
//	}
//}
//
//void Lexer::out(Table_index t, int n)
//{
//	lexeme_file << "(" << (int)t << "," << n << ")" << endl;
//	//cout << S << " -- (" << (int)t << "," << n << ")" << endl;
//}
//
//bool Lexer::check_hex()
//{
//	return digit() || (CH >= 'a' && CH <= 'f') || (CH >= 'A' && CH <= 'F');
//}
//
//bool Lexer::AFH()
//{
//	return check_hex() || CH == 'H' || CH == 'h';
//}
//
//void Lexer::translate(int base)
//{
//	for (int i = 0; i < S.length(); ++i) {
//		d += (S[i] - 48) * pow(2, S.length() - 1 - i);
//	}
//	S = to_string(d);
//}
//
//void Lexer::convert()
//{
//	d = stoi(S);
//}
//
//Lexer::~Lexer() {
//	example_program.close();
//	lexeme_file.close();
//}
//
////�������
//struct lexem {
//	enum class Table_index tab; //�������������� ������� 
//	int id;						//���������� ����� � �������
//	std::string value;			//�������� �������
//	int number;					//����� ������� �� �������
//};
//
//class Parser
//{
//	std::vector<lexem> declareted_identificators;	//������ ���������� ���������������
//	std::string filename;							//�������� �����
//	std::fstream lexeme_file;						//���� � ���������
//	lexem LEX;										//�������
//
//	bool gl();
//	bool EQ(std::string);
//	bool ID();
//	bool NUM();
//	int err_proc(int);								//����� ������
//	int check_lex();
//	void add();										//�������� ������������� � ������ �����������
//
//public:
//	Parser(std::string);
//	void scanner();
//private:
//	/*--------------------------��������� �������� ���������� ������, ����������� ������� ����--------------------------*/
//	//<���������>::= 		�{� {/ (<��������> | <��������>) ; /} �}�
//	void PROG();
//
//	//<��������>::= 		{<�������������> {, <�������������> } : <���> ;}
//	void DESCR();
//
//	//<��������>::= 	<���������> | <������������> | <��������> |
//	//		<��������������_�����> | <���������_�����> | <�����> |
//	//		<������>
//	void OPERATOR();
//
//	//<���>::= 		% | ! | $
//	void TYPE();
//
//	/*--------------------------�������, ������������ �������� ���������--------------------------*/
//	//<���������>::= 		�{� <��������> { ; <��������> } �}�
//	void COMP_OP();
//
//	//<������������>::= 	[ let ] <�������������> = <���������>
//	void ASSIGN_OP();
//
//	//<��������>:: = if <���������> then <��������>[else <��������>] end_else
//	void IF_OP();
//
//	//<����_�����>::= 	for �(�[<���������>] ; [<���������>] ; [<���������>] �)� <��������>
//	void FOR_CICLE();
//
//	//<���������_�����>:: = do while <���������> <��������> loop
//	void WHILE_CICLE();
//
//	//<�����>::= 		input �(�<�������������> {������ <�������������>} �)�
//	void INPUT();
//
//	//<������>::= 		output �(�<���������> { ������ <���������> } �)�
//	void OUTPUT();
//
//	/*--------------------------��������� �����--------------------------*/
//		//<���������>:: =	<�������>{ <��������_������_���������> <�������> }
//	void EXPRESSION();
//
//	//<�������>::= 		<���������> {<��������_������_��������> <���������>}
//	void OPERAND();
//
//	//<���������>::= 	<���������> {<��������_������_���������> <���������>}
//	void SUMMAND();
//
//	//<���������>::= 	<�������������> | <�����> | <����������_���������> |
//	//					<�������_��������> <���������> | �(�<���������>�)�
//	void MULTIPLIER();
//
//	//<�����>:: =		<�����> | <��������������>
//	void NUMBER();
//
//	/*--------------------------�������� �����--------------------------*/
//		//<��_������_���������>:: = 	< > | = | < | <= | > | >=
//	void RATIO();
//
//	//<��_������_��������>:: = 		+ | - | or
//	void ADDITION();
//
//	//<��_������_���������>:: =		*| / |and
//	void MULTIPLICATION();
//
//	//<�������_��������>::= 		not
//	void UNARY();
//};
//
//bool Parser::gl()
//{
//	static int number = 1;
//	if (lexeme_file.eof())
//		return true;
//	string lex;
//	lexeme_file >> lex;
//	LEX.tab = (Table_index)(lex[1] - 48);
//	LEX.id = stoi(lex.substr(3, lex.size() - 4));
//	switch (LEX.tab)
//	{
//	case(Table_index::TW_index):
//		for (auto elem : TW)
//			if (elem.second == LEX.id) LEX.value = elem.first;
//		break;
//	case(Table_index::TL_index):
//		for (auto elem : TL)
//			if (elem.second == LEX.id) LEX.value = elem.first;
//		break;
//	case(Table_index::TI_index):
//		for (auto elem : TI)
//			if (elem.second == LEX.id) LEX.value = elem.first;
//		break;
//	case(Table_index::TN_index):
//		for (auto elem : TN)
//			if (elem.second == LEX.id) LEX.value = elem.first;
//		break;
//	default:
//		throw "������������ �������";
//	}
//	LEX.number = number;
//	++number;
//	return lexeme_file.eof();
//
//}
//
//bool Parser::EQ(std::string S)
//{
//	switch (LEX.tab)
//	{
//	case(Table_index::TW_index):
//		return TW[S] == LEX.id;
//	case(Table_index::TL_index):
//		return TL[S] == LEX.id;
//	case(Table_index::TI_index):
//		return TI[S] == LEX.id;
//	case(Table_index::TN_index):
//		return TN[S] == LEX.id;
//	default:
//		return false;
//	}
//}
//
//bool Parser::ID()
//{
//	return (LEX.tab == Table_index::TI_index);
//}
//
//bool Parser::NUM()
//{
//	return LEX.tab == Table_index::TN_index;
//}
//
//int Parser::err_proc(int error)
//{
//	cout << "������: " << error << ": ";
//	switch (error)
//	{
//	case  201:
//		cout << "�������� �������������" << endl;
//		break;
//	case  202:
//		cout << "�������� ':'" << endl;
//		break;
//	case  203:
//		cout << "�������� ��������" << endl;
//		break;
//	case  204:
//		cout << "�������� ���" << endl;
//		break;
//	case  205:
//		cout << "�������� '}'" << endl;
//		break;
//	case  206:
//		cout << "�������� '{'" << endl;
//		break;
//	case  207:
//		cout << "�������� '='" << endl;
//		break;
//	case  208:
//		cout << "�������� 'then'" << endl;
//		break;
//	case  209:
//		cout << "�������� 'end_else'" << endl;
//		break;
//	case  210:
//		cout << "�������� '('" << endl;
//		break;
//	case  211:
//		cout << "�������� ';'" << endl;
//		break;
//	case  212:
//		cout << "�������� ')'" << endl;
//		break;
//	case  213:
//		cout << "�������� 'loop' " << endl;
//		break;
//	case  214:
//		cout << "�������� ������� " << endl;
//		break;
//	case  215:
//		cout << "��������� ���������" << endl;
//		break;
//	case  216:
//		cout << "�������� ���������" << endl;
//		break;
//	case  217:
//		cout << "��������� �����" << endl;
//		break;
//	case  218:
//		cout << "�������� �������� ������ ���������" << endl;
//		break;
//	case  219:
//		cout << "�������� �������� ������ ��������" << endl;
//		break;
//	case  220:
//		cout << "�������� �������� ������ ���������" << endl;
//		break;
//	case  221:
//		cout << "�������� ������� ��������" << endl;
//		break;
//	case 301:
//		cout << "���������� ��� ���� ���������" << endl;
//		break;
//	case 302:
//		cout << "���������� �� ���� ��������� �����" << endl;
//		break;
//	default:
//		cout << "����������� ������" << endl;
//		break;
//	}
//	cout << "�������� " << LEX.value << ", ����� �������: " << LEX.number;
//	throw error;
//}
//
//Parser::Parser(std::string p_filename) :
//	filename("lexems " + p_filename),
//	declareted_identificators(0),
//	LEX({ Table_index::TL_index, 1 })
//{}
//
//void Parser::scanner()
//{
//	lexeme_file.open(filename, ios::in);
//	PROG();
//	cout << "�������������� � ������������� ������� ������� ���������";
//	lexeme_file.close();
//}
//
//void Parser::PROG()
//{
//	gl();
//	if (EQ("{")) {
//		do {
//			gl();
//			if (ID())
//				DESCR();
//			else if (EQ("if") || EQ("do while") || EQ("for") || EQ("input") || EQ("output") || EQ("{") || EQ("let"))
//				OPERATOR();
//			else if (EQ("}"))
//				break;
//			else
//				err_proc(31);
//
//			if (!EQ(";"))
//				err_proc(22);
//		} while (EQ(";"));
//
//		if (!(EQ("}")))
//			err_proc(3);
//	}
//	else err_proc(2);
//}
//
//void Parser::DESCR()
//{
//	if (check_lex())
//		err_proc(301);
//	add();
//	gl();
//	while (EQ(",")) {
//		gl();
//		if (!ID())
//			err_proc(201);
//		if (check_lex())
//			err_proc(301);
//		add();
//		gl();
//	}
//	if (EQ(":")) {
//		gl();
//		TYPE();
//	}
//	else  err_proc(202);
//}
//
//void Parser::OPERATOR()
//{
//	if (EQ("{"))
//		COMP_OP();
//	else if (EQ("let"))
//		ASSIGN_OP();
//	else if (EQ("if"))
//		IF_OP();
//	else if (EQ("for"))
//		FOR_CICLE();
//	else if (EQ("do while"))
//		WHILE_CICLE();
//	else if (EQ("input"))
//		INPUT();
//	else if (EQ("output"))
//		OUTPUT();
//	else
//		err_proc(203);
//}
//
//void Parser::TYPE()
//{
//	if (!EQ("%") && !EQ("!") && EQ("$"))
//		err_proc(204);
//	gl();
//}
//
//void Parser::COMP_OP()
//{
//	do {
//		gl();
//		OPERATOR();
//	} while (EQ(";"));
//	if (!EQ("}"))
//		err_proc(205);
//	gl();
//}
//
//void Parser::ASSIGN_OP()
//{
//	gl();
//	if (!ID())
//		err_proc(201);
//	if (!check_lex())
//		err_proc(302);
//	gl();
//	if (!EQ("="))
//		err_proc(207);
//	gl();
//	EXPRESSION();
//}
//
//void Parser::IF_OP()
//{
//	gl();
//	EXPRESSION();
//	if (!EQ("then"))
//		err_proc(208);
//	gl();
//	OPERATOR();
//	if (EQ("else")) {
//		OPERATOR();
//	}
//	if (!EQ("end_else"))
//		err_proc(228);
//	gl();
//}
//
//void Parser::FOR_CICLE()
//{
//	gl();
//	if (!EQ("("))
//		err_proc(210);
//	gl();
//	if (ID() || NUM() || EQ("true") || EQ("false") || EQ("not") || EQ("(")) {
//		if (ID() && !check_lex())
//			err_proc(302);
//		EXPRESSION();
//	}
//	if (!EQ(";"))
//		err_proc(211);
//	gl();
//	if (ID() || NUM() || EQ("true") || EQ("false") || EQ("not") || EQ("(")) {
//		if (ID() && !check_lex())
//			err_proc(302);
//		EXPRESSION();
//	}
//	if (!EQ(";"))
//		err_proc(211);
//	gl();
//	if (ID() || NUM() || EQ("true") || EQ("false") || EQ("not") || EQ("(")) {
//		if (ID() && !check_lex())
//			err_proc(302);
//		EXPRESSION();
//	}
//	if (!EQ(")"))
//		err_proc(212);
//	gl();
//	OPERATOR();
//}
//
//void Parser::WHILE_CICLE()
//{
//	gl();
//	if (ID() || NUM() || EQ("true") || EQ("false") || EQ("not") || EQ("(")) {
//		EXPRESSION();
//	}
//	else
//		err_proc(228);
//
//	if (EQ("if") || EQ("do while") || EQ("for") || EQ("input") || EQ("output") || EQ("{") || EQ("let")) {
//		OPERATOR();
//	}
//	else
//		err_proc(203);
//	if (!EQ("loop"))
//		err_proc(213);
//	gl();
//}
//
//void Parser::INPUT()
//{
//	gl();
//	if (!EQ("("))
//		err_proc(228);
//	gl();
//	while (ID()) {
//		gl();
//	}
//	if (!EQ(")"))
//		err_proc(228);
//	gl();
//}
//
//void Parser::OUTPUT()
//{
//	gl();
//	if (!EQ("("))
//		err_proc(210);
//	gl();
//	while (ID() || NUM() || EQ("true") || EQ("false") || EQ("not") || EQ("(")) {
//		if (ID() && !check_lex())
//			err_proc(302);
//		EXPRESSION();
//	}
//	if (!EQ(")"))
//		err_proc(212);
//	gl();
//}
//
//void Parser::EXPRESSION()
//{
//	if (ID() || NUM() || EQ("true") || EQ("false") || EQ("not") || EQ("(")) {
//		if (ID() && !check_lex())
//			err_proc(302);
//		OPERAND();
//	}
//	else err_proc(214);
//
//	if (EQ("< >") || EQ("=") || EQ("<") || EQ("<=") || EQ(">") || EQ(">="))
//	{
//		RATIO();
//		if (ID() || NUM() || EQ("true") || EQ("false") || EQ("not") || EQ("(")) {
//			if (ID() && !check_lex())
//				err_proc(302);
//			OPERAND();
//		}
//		else err_proc(214);
//	}
//}
//
//void Parser::OPERAND()
//{
//	if (ID() || NUM() || EQ("true") || EQ("false") || EQ("not") || EQ("(")) {
//		if (ID() && !check_lex())
//			err_proc(302);
//		SUMMAND();
//	}
//	else err_proc(215);
//
//	if (EQ("+") || EQ("-") || EQ("or"))
//	{
//		ADDITION();
//		if (ID() || NUM() || EQ("true") || EQ("false") || EQ("not") || EQ("(")) {
//			if (ID() && !check_lex())
//				err_proc(302);
//			SUMMAND();
//		}
//		else err_proc(215);
//	}
//}
//
//void Parser::SUMMAND()
//{
//	if (ID() || NUM() || EQ("true") || EQ("false") || EQ("not") || EQ("(")) {
//		if (ID() && !check_lex())
//			err_proc(302);
//		MULTIPLIER();
//	}
//	else err_proc(216);
//
//	if (EQ("*") || EQ("/") || EQ("and"))
//	{
//		MULTIPLICATION();
//		if (ID() || NUM() || EQ("true") || EQ("false") || EQ("not") || EQ("(")) {
//			if (ID() && !check_lex())
//				err_proc(302);
//			MULTIPLIER();
//		}
//		else err_proc(216);
//	}
//}
//
//void Parser::MULTIPLIER()
//{
//	if (EQ("(")) {
//		gl();
//		EXPRESSION();
//		if (!EQ(")"))
//			err_proc(212);
//
//	}
//	else if (EQ("not")) {
//		UNARY();
//	}
//	gl();
//}
//
//void Parser::NUMBER()
//{
//	if (!NUM())
//		err_proc(217);
//	gl();
//
//}
//
//void Parser::RATIO()
//{
//	if (!(EQ("< >") || EQ("=") || EQ("<") || EQ("<=") || EQ(">") || EQ(">=")))
//		err_proc(218);
//	gl();
//}
//
//void Parser::ADDITION()
//{
//	if (!(EQ("+") || EQ("-") || EQ("or")))
//		err_proc(219);
//	gl();
//}
//
//void Parser::MULTIPLICATION()
//{
//	if (!(EQ("*") || EQ("/") || EQ("and")))
//		err_proc(220);
//	gl();
//}
//
//void Parser::UNARY()
//{
//	if (!EQ("not"))
//		err_proc(221);
//	gl();
//}
//
//int Parser::check_lex()
//{
//	for (lexem lex : declareted_identificators)
//		if (lex.id == LEX.id and lex.tab == LEX.tab)
//			return true;
//	return false;
//}
//
//void Parser::add()
//{
//	declareted_identificators.push_back(LEX);
//}