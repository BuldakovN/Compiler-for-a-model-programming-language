// KUSRACH2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

//#include <iostream>
//#include "Recognizer.h"
//
//int main(){
//    setlocale(LC_ALL, "rus");
//    Recognizer rec("example_4.txt");
//    rec.run();
//}

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
//ЛЕКСИЧЕСКИЙ АНАЛИЗАТОР

class Lexer_N {
	enum states {
		H,	//начало
		I,	//идентификатор
		N2,	//двоичное число
		N8,	//восьмеричное число
		N10,//десятичное число
		N16,//шестнадцатеричное число
		L,	//разделитель
		C1,	//комментарий
		C2,	//комментарий
		C3,	//комментарий
		P1,	//точка
		P2,	//дробная часть числа
		EQ, //оператор присваивани, равно
		CM, //меньше/больше (или равно), не равно
		B,	//символ «B» или «b»
		O,	//символ «O» или «o»
		D,	//символ «D» или «d»
		HX,	//символ «H» или «h»
		E11,//символ «E» или «e»
		E12,//порядок числа в экспоненциальной форме
		E13,//порядок числа в экспоненциальной форме
		E22,//порядок числа в экспоненциальной форме
		ZN,	//знак порядка числа в экспоненциальной форме
		E21,//знак порядка числа в экспоненциальной форме
		OR,	//или
		AND,//и
		V,	//выход
		ER	//ошибка
	};

	fstream file;
	string str = "";
	char ch;

protected:

	enum tables {
		tl,	//таблица разделителей
		tw,	//таблица служебных слов
		ti,	//таблица идентификаторов
		tn	//таблица чисел
	};

	struct ID {
		string name;
		bool declared;
		bool assigned;
	};

	vector<string> TL{ "{", "}", ",", ";", ":=", "~", "==", "%", "!", "$", "(", ")", "[", "]", "*", "/", "/*", "*/","|", ".", "&&", "<", ">","=",":" ,"+", "-" };//таблица разделителей
	vector<string> TW{ "if", "else", "program", "begin", "end.", "end", "next", "writeln", "readln", "while", "for", "step", "integer", "real", "boolean", "to", "true", "false", "NE","EQ","LT","LE","GT","GE","plus","min","or","mult","and","div","dollar","percent","factorial" };	//таблица служебных слов
	vector<ID*>TI;	//таблица идентификаторов
	vector<string>TN;		//таблица чисел

public:
	struct Lexem {
		tables tableN;
		unsigned i;
		//string str;
	};

	vector<Lexem*> LexemT;

	bool withinRangeN2(char ch) {
		return ch == '0' || ch == '1';
	}

	bool withinRangeN8(char ch) {
		return ch >= '0' && ch <= '7';
	}

	bool withinRangeN16(char ch) {
		return ch >= '0' && ch <= '9' || toupper(ch) >= 'A' && toupper(ch) <= 'F';
	}

	bool gc() {
		if (!file.eof()) {
			ch = file.get();
			return true;
		}
		return false;
	}

	Lexer_N():file("test.txt")
	{
		//file.open("‪test.txt");
		string a;
		file >> a;
		if (!file)
		{
			cout << "Lexer \nThis file cannot be opened";
		}
		fillLexemT();
		file.close();
	}


	void put(tables t) {
		Lexem* lexem = new Lexem;
		lexem->tableN = t;
		//lexem->str = str;
		ID* id = new ID;
		switch (t) {
		case tl:
			lexem->i = find(TL.begin(), TL.end(), str) - TL.begin();
			break;
		case tw:
			lexem->i = find(TW.begin(), TW.end(), str) - TW.begin();
			break;
		case ti:
			for (unsigned i = 0; i < TI.size(); i++) {
				if (TI[i]->name == str) {
					lexem->i = i;
					LexemT.push_back(lexem);
					return;
				}
			}
			lexem->i = TI.size();
			id->name = str;
			id->assigned = false;
			id->declared = false;
			TI.push_back(id);
			break;
		case tn:
			if (!count(TN.begin(), TN.end(), str)) {
				TN.push_back(str);
			}
			lexem->i = find(TN.begin(), TN.end(), str) - TN.begin();
			break;
		}
		LexemT.push_back(lexem);
	}

	void fillLexemT() {
		enum states CS = H;
		gc();
		while (CS != V)
		{
			switch (CS)
			{
			case H:
				str = "";
				while (isspace(ch) && gc());
				if (file.eof()) {
					CS = ER;
				}
				else if (withinRangeN2(ch)) {
					CS = N2;
				}
				else if (withinRangeN8(ch)) {
					CS = N8;
				}
				else if (isdigit(ch)) {
					str += ch;
					CS = N10;
				}
				else if (ch == '.') {
					CS = P1;
				}
				else if (ch == 'div') {
					CS = C1;
				}
				else if (ch == '!' || ch == 'EQ' || ch == 'NE') {
					CS = CM;
				}
				else if (ch == ':' || ch == 'GT') {
					CS = EQ;
				}
				else if (ch == '|') {
					CS = OR;
				}
				else if (ch == 'and') {
					CS = AND;
				}
				else if (isalpha(ch)) {
					CS = I;
				}
				else {
					str = ch;
					gc();
					CS = L;
				}
				break;
			case I:
				str += ch;
				CS = H;
				while (gc() && (isalnum(ch) || ch == '.'))
				{
					str += ch;
				}
				if (count(TW.begin(), TW.end(), str)) {
					put(tw);
					if (str == "end.") {
						CS = V;
					}
				}
				else {
					put(ti);
				}
				break;
			case OR:
				str = ch;
				if (gc() && ch == '|') {
					str += ch;
					gc();
					put(tl);
					CS = H;
				}
				else {
					CS = ER;
				}
				break;
			case AND:
				str = ch;
				if (gc() && ch == 'and') {
					str += ch;
					gc();
					put(tl);
					CS = H;
				}
				else {
					CS = ER;
				}
				break;
			case CM:
				str = ch;
				if (gc() && ch == 'GT') {
					str += ch;
					gc();
				}
				put(tl);
				CS = H;
				break;
			case EQ:
				str = ch;
				if (gc() && ch == 'GT') {
					str += ch;
					gc();
					put(tl);
					CS = H;
				}
				else {
					CS = ER;
				}
				break;
			case L:
				if (count(TL.begin(), TL.end(), str)) {
					put(tl);
					CS = H;
				}
				else {
					CS = ER;
				}
				break;
			case N2:
				str += ch;
				while (gc() && withinRangeN2(ch)) {
					str += ch;
				}
				if (toupper(ch) == 'B') {
					CS = B;
				}
				else if (toupper(ch) == 'O') {
					CS = O;
				}
				else if (toupper(ch) == 'D') {
					CS = D;
				}
				else if (toupper(ch) == 'H') {
					CS = HX;
				}
				else if (toupper(ch) == 'E') {
					CS = E11;
				}
				else if (ch == '.') {
					CS = P1;
				}
				else if (withinRangeN8(ch)) {
					CS = N8;
				}
				else if (isdigit(ch)) {
					CS = N10;
				}
				else if (withinRangeN16(ch)) {
					CS = N16;
				}
				else if (isalpha(ch)) {
					CS = ER;
				}
				else {
					CS = N10;
				}
				break;
			case N8:
				str += ch;
				while (gc() && withinRangeN8(ch)) {
					str += ch;
				}
				if (toupper(ch) == 'O') {
					CS = O;
				}
				else if (toupper(ch) == 'D') {
					CS = D;
				}
				else if (toupper(ch) == 'H') {
					CS = HX;
				}
				else if (toupper(ch) == 'E') {
					CS = E11;
				}
				else if (ch == '.') {
					CS = P1;
				}
				else if (isdigit(ch)) {
					CS = N10;
				}
				else if (withinRangeN16(ch)) {
					CS = N16;
				}
				else if (isalpha(ch)) {
					CS = ER;
				}
				else {
					CS = N10;
				}
				break;
			case N10:
				while (withinRangeN8(ch)) {
					str += ch;
					if (!gc())
						break;
				}
				if (toupper(ch) == 'O') {
					CS = O;
				}
				else if (toupper(ch) == 'D') {
					CS = D;
				}
				else if (toupper(ch) == 'H') {
					CS = HX;
				}
				else if (toupper(ch) == 'E') {
					CS = E11;
				}
				else if (ch == '.') {
					CS = P1;
				}
				else if (isdigit(ch)) {
					CS = N10;
				}
				else if (withinRangeN16(ch)) {
					CS = N16;
				}
				else if (isalpha(ch)) {
					CS = ER;
				}
				else {
					put(tn);
					CS = H;
				}
				break;
			case N16:
				str += ch;
				while (gc() && withinRangeN8(ch)) {
					str += ch;
					ch = file.get();
				}
				if (toupper(ch) == 'H') {
					CS = HX;
				}
				else {
					CS = ER;
				}
				break;
			case B:
				str += ch;
				if (!gc()) {
					put(tn);
					CS = H;
				}
				if (withinRangeN16(ch)) {
					CS = N16;
				}
				else if (toupper(ch) == 'H') {
					CS = HX;
				}
				else if (isalpha(ch)) {
					CS = ER;
				}
				else {
					put(tn);
					CS = H;
				}
				break;
			case O:
				str += ch;
				if (gc() && isalnum(ch)) {
					CS = ER;
				}
				else {
					put(tn);
					CS = H;
				}
				break;
			case D:
				str += ch;
				if (gc() && withinRangeN16(ch)) {
					CS = N16;
				}
				else if (toupper(ch) == 'H') {
					CS = HX;
				}
				else if (isalpha(ch)) {
					CS = ER;
				}
				else {
					put(tn);
					CS = H;
				}
				break;
			case HX:
				str += ch;
				if (gc() && isalnum(ch)) {
					CS = ER;
				}
				else {
					put(tn);
					CS = H;
				}
				break;
			case E11:
				str += ch;
				gc();
				if (isdigit(ch)) {
					CS = E12;
				}
				else if (ch == 'plus' || ch == 'min') {
					CS = ZN;
				}
				else if (toupper(ch) == 'H') {
					CS = HX;
				}
				else if (withinRangeN16(ch)) {
					CS = N16;
				}
				else {
					CS = ER;
				}
				break;
			case ZN:
				str += ch;
				gc();
				if (isdigit(ch)) {
					CS = E13;
				}
				else {
					CS = ER;
				}
				break;
			case E12:
				str += ch;
				while (gc() && isdigit(ch)) {
					str += ch;
				}
				if (withinRangeN16(ch)) {
					CS = N16;
				}
				else if (toupper(ch) == 'H') {
					CS = HX;
				}
				else if (isalpha(ch)) {
					CS = ER;
				}
				else {
					put(tn);
					CS = H;
				}
				break;
			case E13:
				str += ch;
				while (gc() && isdigit(ch)) {
					str += ch;
				}
				if (isalpha(ch) || ch == '.') {
					CS = ER;
				}
				else {
					put(tn);
					CS = H;
				}
				break;
			case P1:
				str += ch;
				if (gc() && isdigit(ch)) {
					CS = P2;
				}
				else {
					CS = ER;
				}
				break;
			case P2:
				str += ch;
				while (gc() && isdigit(ch)) {
					str += ch;
					ch = file.get();
				}
				if (toupper(ch) == 'E') {
					CS = E21;
				}
				else if (isalpha(ch) || ch == '.') {
					CS = ER;
				}
				else {
					put(tn);
					CS = H;
				}
				break;
			case E21:
				str += ch;
				if (gc() && (ch == 'plus' || ch == 'min')) {
					CS = ZN;
				}
				else if (isdigit(ch)) {
					CS = E22;
				}
				else {
					CS = ER;
				}
				break;
			case E22:
				str += ch;
				while (gc() && isdigit(ch)) {
					str += ch;
				}
				if (isalpha(ch) || ch == '.') {
					CS = ER;
				}
				else {
					put(tn);
					CS = H;
				}
				break;
			case C1:
				str = ch;
				if (gc() && ch == 'mult') {
					CS = C2;
				}
				else {
					CS = L;
				}
				break;
			case C2:
				while (gc() && ch != 'mult' && ch != '}');
				if (file.eof()) {
					CS = ER;
				}
				else {
					CS = C3;
				}
				break;
			case C3:
				if (gc() && ch == 'div') {
					gc();
					CS = H;
				}
				else {
					CS = C2;
				}
				break;
			case ER:
				throw string("Unknown lexem at position " + file.tellg());
			}
		}
	}
};

//СИНТАКСИЧЕСКИЙ АНАЛИЗАТОР
class Parser_N : public Lexer_N
{
	Lexem* curr_lex;       // текущая лексема
	int c_type;
	tables c_table;    //тип нашей лексемы
	int i;

	enum class DELIM {//разделители
		OPEN_BRACKET, CLOSE_BRACKET, OPEN_BRACE, CLOSE_BRACE, OPEN_PARENTHESE, CLOSE_PARENTHESE, COMMA, SEMICOLON, ASSIGN, INEQUAL, EQUAL, LESS, NOT_MORE, MORE, NOT_LESS,
		PLUS, MINUS, OR, MULTIPLY, DIVIDE, AND, NOT, SLASH, NE, EQ, LT, LE, GT, GE
	};

	enum class KEYWORDS {//ключевые(служебные) слова
		IF, ELSE, PROGRAM, BEGIN, FIN, END, NEXT, WRITELN, READLN, WHILE, FOR, STEP, PERCENT, DOLLAR, FACTORIAL, INT, REAL, BOOL, TO, TRUE, FALSE
	};

	// получение лексемы
	void gl()
	{
		curr_lex = LexemT[++i];
		c_type = curr_lex->i;
		c_table = curr_lex->tableN;
	}

public:
	void analyze()
	{
		gl();
		PROGRAM();
	}

	Parser_N()
	{
		i = -1;
	}

	bool check(tables T, int type) {
		return c_table == T && c_type == type;
	}

	// PROGRAM	→	«{» {/ (<DESC> | <OPERATOR>) ; /} «}»
	void PROGRAM()
	{
		if (check(tw, static_cast<int>(DELIM::OPEN_BRACE))) {
			gl();
		}
		else {
			throw curr_lex;
		}
		if (check(tw, static_cast<int>(DELIM::SLASH))) {
			gl();
		}
		else {
			throw curr_lex;
		}
		DESC();
		if (check(tw, static_cast<int>(DELIM::OPEN_PARENTHESE))) {
			gl();
		}
		else {
			throw curr_lex;
		}
		if (check(tw, static_cast<int>(DELIM::CLOSE_PARENTHESE))) {
			gl();
		}
		else {
			throw curr_lex;
		}
		OPERATOR();
		while (check(tl, static_cast<int>(DELIM::SEMICOLON))) {
			gl();
			OPERATOR();
		}
		if (!check(tw, static_cast<int>(KEYWORDS::FIN))) {
			throw curr_lex;
		}
	}

	// DESC →	TYPE id {, id }
	void DESC()
	{
		TYPE();
		if (c_table == ti) {
			if (TI[c_type]->declared == false) {
				TI[c_type]->declared = true;
				gl();
			}
			else {
				throw string("SEMANTIC ERROR");
			}
		}
		else {
			throw curr_lex;
		}
		while (check(tl, static_cast<int>(DELIM::COMMA))) {
			gl();
			if (c_table == ti) {
				if (TI[c_type]->declared == false) {
					TI[c_type]->declared = true;
					gl();
				}
				else {
					throw string("SEMANTIC ERROR");
				}
			}
			else {
				throw curr_lex;
			}
		}
	}

	// TYPE →	% | ! | $
	// TYPE →	PERCENT | FACTORIAL | DOLLAR
	void TYPE()
	{
		if (check(tw, static_cast<int>(KEYWORDS::PERCENT)) || check(tw, static_cast<int>(KEYWORDS::FACTORIAL)) || check(tw, static_cast<int>(KEYWORDS::DOLLAR))) {
			gl();
		}
		else {
			throw curr_lex;
		}
	}

	// OPERATOR →	COMPLEX | ASSIGN | CONDITION | LOOP | UNTIL | READLN | WRITELN
	void OPERATOR()
	{
		if (check(tw, static_cast<int>(KEYWORDS::BEGIN))) {
			gl();
			COMPLEX();
		}
		else if (c_table == ti) {
			TI[c_type]->assigned = true;
			gl();
			ASSIGN();
		}
		else if (check(tw, static_cast<int>(KEYWORDS::IF))) {
			gl();
			CONDITION();
		}
		else if (check(tw, static_cast<int>(KEYWORDS::FOR))) {
			gl();
			LOOP();
		}
		else if (check(tw, static_cast<int>(KEYWORDS::WHILE))) {
			gl();
			UNTIL();
		}
		else if (check(tw, static_cast<int>(KEYWORDS::READLN))) {
			gl();
			READLN();
		}
		else if (check(tw, static_cast<int>(KEYWORDS::WRITELN))) {
			gl();
			WRITELN();
		}
		else {
			throw curr_lex;
		}
	}

	// COMPLEX	→ begin OPERATOR {; OPERATOR } end
	void COMPLEX() {
		OPERATOR();
		while (check(tl, static_cast<int>(DELIM::SEMICOLON))) {
			gl();
			OPERATOR();
		}
		if (check(tw, static_cast<int>(KEYWORDS::END))) {
			gl();
		}
		else {
			throw curr_lex;
		}
	}

	// ASSIGN	→ id : = EXPR
	void ASSIGN() {
		if (check(tl, static_cast<int>(DELIM::ASSIGN))) {
			gl();
		}
		else {
			throw curr_lex;
		}
		EXPR();
	}

	// CONDITION 	→ if «(» EXPR «)» OPERATOR [else OPERATOR]
	void CONDITION() {
		if (check(tl, static_cast<int>(DELIM::OPEN_BRACKET))) {
			gl();
		}
		else {
			throw curr_lex;
		}
		EXPR();
		if (check(tl, static_cast<int>(DELIM::CLOSE_BRACKET))) {
			gl();
		}
		else {
			throw curr_lex;
		}
		OPERATOR();
		if (check(tw, static_cast<int>(KEYWORDS::ELSE))) {
			gl();
			OPERATOR();
		}
	}

	// LOOP	→ for ASSIGN to EXPR [step EXPR] OPERATOR next
	void LOOP() {
		if (c_table == ti) {
			TI[c_type]->assigned = true;
			gl();
		}
		else {
			throw curr_lex;
		}
		ASSIGN();
		if (check(tw, static_cast<int>(KEYWORDS::TO))) {
			gl();
		}
		else {
			throw curr_lex;
		}
		EXPR();
		if (check(tw, static_cast<int>(KEYWORDS::STEP))) {
			gl();
			EXPR();
		}
		OPERATOR();
		if (check(tw, static_cast<int>(KEYWORDS::NEXT))) {
			gl();
		}
		else {
			throw curr_lex;
		}
	}

	// UNTIL	→ while «(» EXPR «)» OPERATOR
	void UNTIL() {
		if (check(tl, static_cast<int>(DELIM::OPEN_BRACKET))) {
			gl();
		}
		else {
			throw curr_lex;
		}
		EXPR();
		if (check(tl, static_cast<int>(DELIM::CLOSE_BRACKET))) {
			gl();
		}
		else {
			throw curr_lex;
		}
		OPERATOR();
	}

	// READLN	→ readln id { , id }
	void READLN() {
		if (c_table == ti) {
			TI[c_type]->assigned = true;
			gl();
		}
		else {
			throw curr_lex;
		}
		while (check(tl, static_cast<int>(DELIM::COMMA))) {
			gl();
			if (c_table == ti) {
				gl();
			}
			else {
				throw curr_lex;
			}
		}
	}

	// WRITELN	→ EXPR {, EXPR }
	void WRITELN() {
		EXPR();
		while (check(tl, static_cast<int>(DELIM::COMMA))) {
			gl();
			EXPR();
		}
	}


	// EXPR	→ OPERAND { ( GE|GT| EQ | LE | NE | LT)  OPERAND }
	void EXPR() {
		OPERAND();
		while (c_table == tl && c_type >= static_cast<int>(DELIM::GE) && c_type <= static_cast<int>(DELIM::LT)) {
			gl();
			OPERAND();
		}
	}


	// OPERAND	→ COMP { ( PLUS | MIN | OR ) COMP }
	void OPERAND() {
		COMP();
		while (c_table == tl && c_type >= static_cast<int>(DELIM::PLUS) && c_type <= static_cast<int>(DELIM::OR)) {
			gl();
			COMP();
		}
	}


	// COMP	→ MULT { ( MULT | DIV | AND ) MULT }
	void COMP() {
		MULT();
		while (c_table == tl && c_type >= static_cast<int>(DELIM::MULTIPLY) && c_type <= static_cast<int>(DELIM::AND)) {
			gl();
			MULT();
		}
	}

	// MULT	→ id | n | ~ MULT | ( EXPR )
	void MULT() {
		if (c_table == ti) {
			if (TI[c_type]->assigned) {
				gl();
			}
			else {
				throw string("SEMANTIC ERROR");
			}
		}
		else if (c_table == tn || check(tw, static_cast<int>(KEYWORDS::TRUE)) || check(tw, static_cast<int>(KEYWORDS::FALSE))) {
			gl();
		}
		else if (check(tl, static_cast<int>(DELIM::NOT))) {
			gl();
			MULT();
		}
		else if (check(tl, static_cast<int>(DELIM::OPEN_BRACKET))) {
			gl();
			EXPR();
			if (check(tl, static_cast<int>(DELIM::CLOSE_BRACKET))) {
				gl();
			}
			else {
				throw curr_lex;
			}
		}
		else {
			throw curr_lex;
		}
	}
};



int main()
{

	try {
		Parser_N parser;
		parser.analyze();
		cout << "OK" << endl;
	}
	catch (Lexer_N::Lexem* lex) {
		cout << "Error => (" << lex->tableN << ", " << lex->i << ")" << endl;
	}
	catch (string str) {
		cout << str << endl;
	}
	return 0;
}
