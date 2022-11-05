#include "Parser.h"

using namespace std;

bool Parser::gl()
{
    static int number = 1;
    if (lexeme_file.eof())
        return true;
    string lex;
    lexeme_file >> lex;
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
        throw "Неопознанная лексема";
    }
    LEX.number = number;
    ++number;
    return lexeme_file.eof();

}

bool Parser::EQ(std::string S)
{
    switch (LEX.tab)
    {
    case(Table_index::TW_index):
        return TW[S] == LEX.id;
    case(Table_index::TL_index):
        return TL[S] == LEX.id;
    case(Table_index::TI_index):
        return TI[S] == LEX.id;
    case(Table_index::TN_index):
        return TN[S] == LEX.id;
    default:
        return false;
    }
}

bool Parser::ID()
{
    return (LEX.tab == Table_index::TI_index);
}

bool Parser::NUM()
{
    return LEX.tab == Table_index::TN_index;
}

int Parser::err_proc(int error)
{
    cout << "Ошибка: " << error << ": ";
    switch (error)
    {
    case  201:
        cout << "Ожидался идентификатор" << endl;
        break;
    case  202:
        cout << "Ожидался ':'" << endl;
        break;
    case  203:
        cout << "Ожидался оператор" << endl;
        break;
    case  204:
        cout << "Ожидался тип" << endl;
        break;
    case  205:
        cout << "Ожидался '}'" << endl;
        break;
    case  206:
        cout << "Ожидался '{'" << endl;
        break;
    case  207:
        cout << "Ожидался '='" << endl;
        break;
    case  208:
        cout << "Ожидался 'then'" << endl;
        break;
    case  209:
        cout << "Ожидался 'end_else'" << endl;
        break;
    case  210:
        cout << "Ожидался '('" << endl;
        break;
    case  211:
        cout << "Ожидался ';'" << endl;
        break;
    case  212:
        cout << "Ожидался ')'" << endl;
        break;
    case  213:
        cout << "Ожидался 'loop' " << endl;
        break;
    case  214:
        cout << "Ожидался операнд " << endl;
        break;
    case  215:
        cout << "Ожидалось слагаемое" << endl;
        break;
    case  216:
        cout << "Ожидался множитель" << endl;
        break;
    case  217:
        cout << "Ожидалось число" << endl;
        break;
    case  218:
        cout << "Ожидался оператор группы отношения" << endl;
        break;
    case  219:
        cout << "Ожидался оператор группы сложения" << endl;
        break;
    case  220:
        cout << "Ожидался оператор группы умножения" << endl;
        break;
    case  221:
        cout << "Ожидался унарный оператор" << endl;
        break;
    case 301:
        cout << "Переменная уже была объявлена" << endl;
        break;
    case 302:
        cout << "Переменная не была объявлена ранее" << endl;
        break;
    default:
        cout << "Неизвестная ошибка" << endl;
        break;
    }
    cout << "Встречен " << LEX.value << ", номер лексемы: " << LEX.number;
    throw error;
}

Parser::Parser(std::string p_filename) :
    filename("lexems " + p_filename),
    declareted_identificators(0),
    LEX({ Table_index::TL_index, 1 })
{}

void Parser::scanner()
{
    lexeme_file.open(filename, ios::in);
    PROG();
    cout << "Синтаксический и семантический анализы успешно завершены";
    lexeme_file.close();
}

void Parser::PROG()
{
    gl();
    if (EQ("{")) {
        do {
            gl();
            if (ID())
                DESCR();
            else if (EQ("if") || EQ("do while") || EQ("for") || EQ("input") || EQ("output") || EQ("{") || EQ("let"))
                OPERATOR();
            else if (EQ("}"))
                break;
            else
                err_proc(31);

            if (!EQ(";"))
                err_proc(22);
        } while (EQ(";"));

        if (!(EQ("}")))
            err_proc(3);
    }
    else err_proc(2);
}

void Parser::DESCR()
{
    if (check_lex())
        err_proc(301);
    add();
    gl();
    while (EQ(",")) {
        gl();
        if (!ID())
            err_proc(201);
        if (check_lex())
            err_proc(301);
        add();
        gl();
    }
    if (EQ(":")) {
        gl();
        TYPE();
    }
    else  err_proc(202);
}

void Parser::OPERATOR()
{
    if (EQ("{"))
        COMP_OP();
    else if (EQ("let"))
        ASSIGN_OP();
    else if (EQ("if"))
        IF_OP();
    else if (EQ("for"))
        FOR_CICLE();
    else if (EQ("do while"))
        WHILE_CICLE();
    else if (EQ("input"))
        INPUT();
    else if (EQ("output"))
        OUTPUT();
    else
        ID();
}

void Parser::TYPE()
{
    if (!EQ("%") && !EQ("!") && EQ("$")) 
        err_proc(204);
    gl();
}

void Parser::COMP_OP()
{
    do {
        gl();
        OPERATOR();
    } while (EQ(";"));
    if (!EQ("}"))
        err_proc(205);
    gl();
}

void Parser::ASSIGN_OP()
{
    gl();
    if (!ID())
        err_proc(201);
    if (!check_lex())
        err_proc(302);
    gl();
    if (!EQ("="))
        err_proc(207);
    gl();
    EXPRESSION();
}

void Parser::IF_OP()
{
    gl();
    EXPRESSION();
    if (!EQ("then"))
        err_proc(208);
    gl();
    OPERATOR();
    if (EQ("else")) {
        gl();
        OPERATOR();
    }
    if (!EQ("end_else"))
        err_proc(209);
    gl();
}

void Parser::FOR_CICLE()
{
    gl();
    if (!EQ("("))
        err_proc(210);
    gl();
    if (ID() || NUM() || EQ("true") || EQ("false") || EQ("not") || EQ("(")) {
        if (ID() && !check_lex())
            err_proc(302);
        EXPRESSION();
    }
    if (!EQ(";"))
        err_proc(211);
    gl();
    if (ID() || NUM() || EQ("true") || EQ("false") || EQ("not") || EQ("(")) {
        if (ID() && !check_lex())
            err_proc(302);
        EXPRESSION();
    }
    if (!EQ(";"))
        err_proc(211);
    gl();
    if (ID() || NUM() || EQ("true") || EQ("false") || EQ("not") || EQ("(")) {
        if (ID() && !check_lex())
            err_proc(302);
        EXPRESSION();
    }
    if (!EQ(")"))
        err_proc(212);
    gl();
    OPERATOR();
}

void Parser::WHILE_CICLE()
{
    gl();
    if (ID() || NUM() || EQ("true") || EQ("false") || EQ("not") || EQ("(")) {
        EXPRESSION();
    }
    else
        err_proc(228);

    if (EQ("if") || EQ("do while") || EQ("for") || EQ("input") || EQ("output") || EQ("{") || EQ("let")) {
        OPERATOR();
    }
    else
        err_proc(203);
    if (!EQ("loop"))
        err_proc(213);
    gl();
}

void Parser::INPUT()
{
    gl();
    if (!EQ("("))
        err_proc(210);
    gl();
    while (ID()) {
        gl();
    }
    if (!EQ(")"))
        err_proc(212);
    gl();
}

void Parser::OUTPUT()
{
    gl();
    if (!EQ("("))
        err_proc(210);
    gl();
    while (ID() || NUM() || EQ("true") || EQ("false") || EQ("not") || EQ("(")) {
        if (ID() && !check_lex())
            err_proc(302);
        EXPRESSION();
    }
    if (!EQ(")"))
        err_proc(212);
    gl();
}

void Parser::EXPRESSION()
{
    if (ID() || NUM() || EQ("true") || EQ("false") || EQ("not") || EQ("(")) {
        if (ID() && !check_lex())
            err_proc(302);
        OPERAND();
    }
    else err_proc(214);

    if (EQ("< >") || EQ("=") || EQ("<") || EQ("<=") || EQ(">") || EQ(">="))
    {
        RATIO();
        if (ID() || NUM() || EQ("true") || EQ("false") || EQ("not") || EQ("(")) {
            if (ID() && !check_lex())
                err_proc(302);
            OPERAND();
        }
        else err_proc(214);
    }
}

void Parser::OPERAND()
{
    if (ID() || NUM() || EQ("true") || EQ("false") || EQ("not") || EQ("(")) {
        if (ID() && !check_lex())
            err_proc(302);
        SUMMAND();
    }
    else err_proc(215);

    if (EQ("+") || EQ("-") || EQ("or"))
    {
        ADDITION();
        if (ID() || NUM() || EQ("true") || EQ("false") || EQ("not") || EQ("(")) {
            if (ID() && !check_lex())
                err_proc(302);
            SUMMAND();
        }
        else err_proc(215);
    }
}

void Parser::SUMMAND()
{
    if (ID() || NUM() || EQ("true") || EQ("false") || EQ("not") || EQ("(")) {
        if (ID() && !check_lex())
            err_proc(302);
        MULTIPLIER();
    }
    else err_proc(216);

    if (EQ("*") || EQ("/") || EQ("and"))
    {
        MULTIPLICATION();
        if (ID() || NUM() || EQ("true") || EQ("false") || EQ("not") || EQ("(")) {
            if (ID() && !check_lex())
                err_proc(302);
            MULTIPLIER();
        }
        else err_proc(216);
    }
}

void Parser::MULTIPLIER()
{
    if (EQ("(")) {
        gl();
        EXPRESSION();
        if (!EQ(")"))
            err_proc(212);

    }
    else if (EQ("not")) {
        UNARY();
    }
    gl();
}

void Parser::NUMBER()
{
    if (!NUM()) 
        err_proc(217);
    gl();

}

void Parser::RATIO()
{
    if (!(EQ("< >") || EQ("=") || EQ("<") || EQ("<=") || EQ(">") || EQ(">="))) 
        err_proc(218);
    gl();
}

void Parser::ADDITION()
{
    if (!(EQ("+") || EQ("-") || EQ("or")))
        err_proc(219);
    gl();
}

void Parser::MULTIPLICATION()
{
    if (!(EQ("*") || EQ("/") || EQ("and")))
        err_proc(220);
    gl();
}

void Parser::UNARY()
{
    if (!EQ("not")) 
        err_proc(221);
    gl();
}

int Parser::check_lex()
{
    for (lexem lex : declareted_identificators)
        if (lex.id == LEX.id and lex.tab == LEX.tab)
            return true;
    return false;
}

void Parser::add()
{
    declareted_identificators.push_back(LEX);
}
