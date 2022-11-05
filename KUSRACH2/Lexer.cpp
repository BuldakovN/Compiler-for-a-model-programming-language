#include "Lexer.h"
#include <string>
#include <cmath> 
using namespace std;

std::unordered_map<std::string, int> TW = {		//таблица служебных слов
	{"true",1},
	{"false",2},
	{"not",3},
	{"let",4},
	{"if",5},
	{"then",6},
	{"else",7},
	{"end_else",8},
	{"for",9},
	{"do while",10},
	{"input",11},
	{"output",12},
	{"or",13},
	{"and",14},
	{"not",15},
	{"loop",16}
};
std::unordered_map<std::string, int> TL = {		//таблица ограничителей
	{"{",1},
	{"}",2},
	{"+",3},
	{"-",4},
	{"*",5},
	{"/",6},
	{"< >",7},
	{"=",8},
	{"<",9},
	{">",10},
	{"<=",11},
	{">=",12},
	{"(",13},
	{")",14},
	{"/*",15},
	{"*/",16},
	{"%",17},			//целый тип
	{"!",18},			//действительный тип
	{"$",19},			//логический тип
	{".",20},
	{",",21},
	{":",22},
	{";",23}
};
std::unordered_map<std::string, int> TN = {};	//таблица чисел
std::unordered_map<std::string, int> TI = {};	//таблица идентификаторов


Lexer::Lexer(string p_filename) :
	S(""),
	d(0),
	CH(' '),
	CS(States::H),
	filename(p_filename)
{
}

bool Lexer::scanner()
{
	example_program.open(filename, ios::in);
	lexeme_file.open("lexems " + filename, ios::out);

	gc();
	int z = 0;
	do {
		switch (CS) {
		case H: {
			while ((CH == ' ' || CH == '\n' || CH == '\t') && !example_program.eof()) { gc(); }
			if (example_program.eof()){
				CS = ER; 
				break; 
			}
			if (let()) {
				nill(); 
				add();
				gc();
				CS = I;
			}
			else if (CH == '0' || CH == '1') {
				nill(); 
				CS = N2; 
				add(); 
				gc(); 
			}
			else if (CH >= '2' && CH <= '7'){
				nill(); 
				CS = N8; 
				add(); 
				gc();
			}
			else if (CH >= '8' && CH <= '9') { 
				nill(); 
				CS = N10; 
				add(); 
				gc(); 
			}
			else if (CH == '.') { 
				nill(); 
				add(); 
				gc(); 
				CS = P1; 
			}
			else if (CH == '/') { 
				gc(); 
				CS = C1; 
			}
			else if (CH == '<') { 
				gc(); 
				CS = M1; 
			}
			else if (CH == '>') { 
				gc(); 
				CS = M2; 
			}
			else if (CH == '}') { 
				out(Table_index::TL_index, 2); 
				if (example_program.eof())
					CS = V;
				else
					gc();
					CS = H;
			}
			else CS = OG;
			break;
		}

		case I: {
			while (let() || digit() || CH=='_') { add(); gc(); }
			if (S == "do") {
				string do_while_check;
				gc();
				do {
					do_while_check += CH;
					gc();
				} while (let());
				if (do_while_check == "while")
					S += " " + do_while_check;
				else
					CS = ER;
			}
			z = look(Table_index::TW_index);
			if (z != 0) { 
				out(Table_index::TW_index, z); 
				CS = H; 
			}
			else { 
				z=put(Table_index::TI_index); 
				out(Table_index::TI_index, z); 
				CS = H; 
			}
			break; 
		}

		case N2: {
			while (CH == '0' || CH == '1') { add(); gc(); }
			if (CH >= '2' && CH <= '7')
				CS = N8;
			else if (CH == '8' || CH == '9')  
				CS = N10; 
			else if (CH == 'A' || CH == 'a' || CH == 'C' || CH == 'c' || CH == 'F' || CH == 'f')  
				CS = N16; 
			else if (CH == 'E' || CH == 'e') { 
				add(); 
				gc(); 
				CS = E11; 
			}
			else if (CH == 'D' || CH == 'd') { 
				add(); 
				gc(); 
				CS = D; 
			}
			else if (CH == 'O' || CH == 'o')  
				CS = O; 
			else if (CH == 'H' || CH == 'h') { 
				gc(); 
				CS = HX;
			}
			else if (CH == '.') { 
				add(); 
				gc(); 
				CS = P1; 
			}
			else if (CH == 'B' || CH == 'b') { 
				add(); 
				gc(); 
				CS = B; 
			}
			else if (let())  
				CS = ER; 
			else  
				CS = N10; 
			break; 
		}

		case N8: {
			while (CH >= '2' && CH <= '7') { add(); gc(); }
			if (CH == '8' || CH == '9') { CS = N10; }
			else if (CH == 'A' || CH == 'a' || CH == 'B' || CH == 'b' || CH == 'C' || CH == 'c' || CH == 'F' || CH == 'f') 
				CS = N16; 
			else if (CH == 'E' || CH == 'e') { 
				add(); 
				gc(); 
				CS = E11; 
			}
			else if (CH == 'D' || CH == 'd') { 
				add(); 
				gc();
				CS = D; 
			}
			else if (CH == 'H' || CH == 'h') { 
				gc(); 
				CS = HX; 
			}
			else if (CH == '.') { 
				add(); 
				gc(); 
				CS = P1; 
			}
			else if (CH == 'O' || CH == 'o') {
				gc(); 
				CS = O; 
			}
			else if (let())  
				CS = ER; 
			else 
				CS = N10;
			break; 
		}

		case N10: {
			while (CH == '8' || CH == '9') { add(); gc(); }
			if (CH == 'A' || CH == 'a' || CH == 'B' || CH == 'b' || CH == 'C' || CH == 'c' || CH == 'F' || CH == 'f') 
				CS = N16; 
			else if (CH == 'E' || CH == 'e') {
				add(); 
				gc(); 
				CS = E11; 
			}
			else if (CH == 'H' || CH == 'h') {
				gc(); 
				CS = HX; 
			}
			else if (CH == '.') {
				add();
				gc();
				CS = P1;
			}
			else if (CH == 'D' || CH == 'd') {
				add();
				gc();
				CS = D; 
			}
			else if (let())  
				CS = ER; 
			else { 
				z=put(Table_index::TN_index); 
				out(Table_index::TN_index, z);
				CS = H;
			}
			break; 
		}

		case N16: {
			while (check_hex()) { add(); gc(); }

			if (CH == 'H' || CH == 'h') { 
				gc(); 
				CS = HX; 
			}
			else
				CS = ER;
			break; 
		}

		case B: {
			if (check_hex()) 
				CS = N16;
			else if (CH == 'H' || CH == 'h') { 
				gc(); 
				CS = HX; 
			}
			else if (let()) 
				CS = ER; 
			else { 
				translate(2); 
				z=put(Table_index::TN_index);
				out(Table_index::TN_index, z);
				CS = H; 
			}
			break; 
		}

		case O: {
			if (let() || digit()) 
				CS = ER; 
			else {
				translate(8);
				z=put(Table_index::TN_index);
				out(Table_index::TN_index, z);
				CS = H;
			}
			break; 
		}

		case D: {
			if (CH == 'H' || CH == 'h') { 
				gc(); 
				CS = HX; 
			}
			else if (check_hex()) 
				CS = N16; 
			else if (let()) 
				CS = ER; 
			else {
				z=put(Table_index::TN_index); 
				out(Table_index::TN_index, z);
				CS = H; 
			}
			break; 
		}

		case HX: {
			if (let() || digit()) 
				CS = ER; 
			else { 
				translate(16);
				z=put(Table_index::TN_index); 
				out(Table_index::TN_index, z);
				CS = H;
			}
			break; 
		}

		case E11: {
			if (digit()) {
				add(); 
				gc();
				CS = E12;
			}
			else if (CH == '+' || CH == '-') {
				add();
				gc();
				CS = ZN; 
			}
			else if (CH == 'H' || CH == 'h') {
				gc();
				CS = HX; 
			}
			else if (check_hex()) {
				add();
				gc(); 
				CS = N16;
			}
			else 
				CS = ER;
			break; 
		}

		case ZN: {
			if (digit()) { 
				add();
				gc(); 
				CS = E13;
			}
			else 
				CS = ER; 
			break; 
		}

		case E12: {
			while (digit()) { add(); gc(); }
			if (check_hex())
				CS = N16;
			else if (CH == 'H' || CH == 'h') { 
				gc(); 
				CS = HX;
			}
			else if (let()) 
				CS = ER; 
			else { 
				convert();
				z=put(Table_index::TN_index);
				out(Table_index::TN_index, z);
				CS = H;
			}
			break; 
		}

		case E13: {
			while (digit()) { add(); gc(); }
			if (let() || CH == '.') 
				CS = ER; 
			else { 
				convert();
				z=put(Table_index::TN_index); 
				out(Table_index::TN_index, z);
				CS = H;
			}
			break; 
		}

		case P1: {
			if (digit()) 
				CS = P2; 
			else 
				CS = ER; 
			break; 
		}

		case P2: {
			while (digit()) { add(); gc(); }
			if (CH == 'E' || CH == 'e') { 
				add(); 
				gc(); 
				CS = E21;
			}
			else if (let() || CH == '.') {
				CS = ER;
			}
			else {
				convert();
				z=put(Table_index::TN_index); 
				out(Table_index::TN_index, z);
				CS = H;
			}
			break; 
		}

		case E21: {
			if (CH == '+' || CH == '-') { 
				add();
				gc();
				CS = ZN;
			}
			else if (digit()) 
				CS = E22; 
			else 
				CS = ER;
			break; 
		}

		case E22: {
			while (digit()) { add(); gc(); }
			if (let() || CH == '.') 
				CS = ER; 
			else { 
				convert();
				z=put(Table_index::TN_index);
				out(Table_index::TN_index, z)
					; CS = H;
			}
			break; 
		}

		case C1: {
			if (CH == '*') {
				gc();
				CS = C2;
			}
			else {
				out(Table_index::TN_index, look(Table_index::TN_index)); 
				CS = H;
			}
			break; 
		}

		case C2: {
			bool flag = 0;	//флаг конца файла
			while (CH != '*' && !flag && CH != '}') { flag = gc(); }
			if (CH == '}' || flag) 
				CS = ER;
			else { 
				gc(); 
				CS = C3; 
			}
			break; 
		}

		case C3: {
			if (CH == '/') {
				gc(); 
				CS = H;
			}
			else 
				CS = C2; 
			break; 
		}

		case M1: {
			if (CH == '>') { 
				gc(); 
				out(Table_index::TL_index, 7);
				CS = H; 
			}
			else if (CH == '=') {
				gc();
				out(Table_index::TL_index, 11);
				CS = H;
			}
			else { 
				out(Table_index::TL_index, 9);
				CS = H;
			}
			break; 
		}

		case M2: {
			if (CH == '=') { 
				gc(); 
				out(Table_index::TL_index, 12); 
				CS = H; 
			}
			else { 
				out(Table_index::TL_index, 10);
				CS = H; 
			}
			break; 
		}

		case OG: {
			nill(); 
			add();
			z=look(Table_index::TL_index);
			if (z != 0) {
				gc();
				out(Table_index::TL_index, z); 
				CS = H;
			}
			else CS = ER;
			break; 
		}
		}
	} while (CS != V && CS != ER);
	example_program.close();
	lexeme_file.close();
	cout << "Ћексический анализ успешно завершен" << endl;
	return CS;
}

void Lexer::print_lexems()
{
	struct lexeme
	{
		int id;
		string value;
		Table_index tab;
		int number;
	};
	lexeme LEX;
	static int number = 1;
	lexeme_file.open("lexems " + filename);
	string lex;
	lexeme_file >> lex;
	while (!lexeme_file.eof()){
		LEX.tab = (Table_index)(lex[1] - 48);
		LEX.id = stoi(lex.substr(3, lex.size() - 4));
		switch (LEX.tab)
		{
		case(Table_index::TW_index):
			for (auto elem : TW)
				if (elem.second == LEX.id) LEX.value = elem.first;
			break;
		case(Table_index::TL_index):
			for (auto elem : TL)
				if (elem.second == LEX.id) LEX.value = elem.first;
			break;
		case(Table_index::TI_index):
			for (auto elem : TI)
				if (elem.second == LEX.id) LEX.value = elem.first;
			break;
		case(Table_index::TN_index):
			for (auto elem : TN)
				if (elem.second == LEX.id) LEX.value = elem.first;
			break;
		default:
			throw "Ќеопознанна€ лексема";
		}
		LEX.number = number;
		++number;
		std::cout << lex << " --- " << LEX.value << endl;
		lexeme_file >> lex;
	}
	lexeme_file.close();
}

bool Lexer::gc()
{
	if (example_program.eof()) 
		return true;
	CH = example_program.get();
	return example_program.eof();
	
}

bool Lexer::let()
{
	return (CH >= 'a' && CH <= 'z') || (CH >= 'A' && CH <= 'Z');
}

bool Lexer::digit()
{
	return CH >= '0' && CH <= '9';
}

void Lexer::nill()
{
	S = "";
}

void Lexer::add()
{
	S += CH;
}

int Lexer::look(Table_index t)
{
	switch (t)
	{
	case Table_index::TW_index:
		if (TW.find(S) == TW.end()) 
			return 0;
		return TW.at(S);
		break;
	case Table_index::TL_index:
		if (TL.find(S) == TL.end()) 
			return 0;
		return TL.at(S);
		break;
	case Table_index::TN_index:
		if (TN.find(S) == TN.end()) return 0;
		return TL.at(S);
		break;
	case Table_index::TI_index:
		if (TI.find(S) == TI.end()) return 0;
		return TL.at(S);
		break;
	default:
		return 0;
		break;
	}
}

int Lexer::put(Table_index t)
{
	//cout << (int)t << " " << S << endl;
	switch (t)
	{
	case Table_index::TN_index:
		if (TN.size() == 0){
			TN[S] = 1;
			return 1;
		}
		else if (TN.find(S) == TN.end()) {
			TN[S] = TN.size()+1;
			return TN.size();
		}
		else
			return TN[S];
		break;
	case Table_index::TI_index:
		if (TI.size() == 0) {
			TI[S] = 1;
			return 1;
		}
		else if (TI.find(S) == TI.end()) {
			TI[S] = TI.size()+1;
			return TI.size();
		}
		else
			return TI[S];
		break;
	default:
		return 0;
		break;
	}
}

void Lexer::out(Table_index t, int n)
{
	lexeme_file << "(" << (int)t << "," << n << ")" << endl;
	//cout << S << " -- (" << (int)t << "," << n << ")" << endl;
}

bool Lexer::check_hex()
{
	return digit() || (CH >= 'a' && CH <= 'f') || (CH >= 'A' && CH <= 'F');
}

bool Lexer::AFH()
{
	return check_hex() || CH=='H' || CH=='h';
}

void Lexer::translate(int base)
{
	for (int i = 0; i < S.length(); ++i) {
		d += (S[i] - 48) * pow(2, S.length() - 1 - i);
	}
	S = to_string(d);
}

void Lexer::convert()
{
	d = stoi(S);
}

Lexer::~Lexer() {
	example_program.close();
	lexeme_file.close();
}