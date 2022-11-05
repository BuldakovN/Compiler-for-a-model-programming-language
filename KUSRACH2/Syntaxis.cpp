#include "Syntaxis.h"

using namespace std;

bool Syntaxis::gl()
{
    static int number = 1;
    if (lexeme_file.eof()) 
        return true;
    string lex;
    lexeme_file >> lex;
    LEX.tab = (Table_index)(lex[1] - 48);
    LEX.id = stoi(lex.substr(3,lex.size()-4));
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

bool Syntaxis::EQ(std::string S)
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

bool Syntaxis::ID()
{
    return LEX.tab == Table_index::TI_index;
}

bool Syntaxis::NUM()
{
    return LEX.tab == Table_index::TN_index;
}

std::string Syntaxis::get()
{
    switch (LEX.tab)
    {
    case(Table_index::TW_index):
        for (auto elem : TW)
            if (elem.second == LEX.id) return elem.first;
    case(Table_index::TL_index):
        for (auto elem : TL)
            if (elem.second == LEX.id) return elem.first;
    case(Table_index::TI_index):
        for (auto elem : TI)
            if (elem.second == LEX.id) return elem.first;
    case(Table_index::TN_index):
        for (auto elem : TN)
            if (elem.second == LEX.id) return elem.first;
    default:
        return "";
    }
}

int Syntaxis::err_proc(int error)
{
    cout << error;
    throw error;
}

Syntaxis::Syntaxis(std::string p_filename) :
    filename("lexems " + p_filename),
    LEX({ Table_index::TL_index, 1 })
{
}

void Syntaxis::scanner()
{

    lexeme_file.open(filename, ios::in);

    PROG();
    
    cout << "Синтаксический анализ успешно завершен";

    lexeme_file.close();
}

void Syntaxis::PROG()
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

void Syntaxis::DESCR()
{
    gl();
    while (EQ(",")) {
        gl();
        if (!ID())
            err_proc(228);
        gl();
    }
    if (EQ(":")) {
        gl();
        TYPE();
    }
    else  err_proc(228);
}

void Syntaxis::OPERATOR()
{
    if (EQ("{"))
        COMP_OP();
    else if (EQ("let"))
        ASSIGN_OP();
    else if (EQ("if"))
        CONDITION_OP();
    else if (EQ("for"))
        FOR_CICLE();
    else if (EQ("do while"))
        WHILE_CICLE();
    else if (EQ("input"))
        INPUT();
    else if (EQ("output"))
        OUTPUT();
    else
        err_proc(228);
}

void Syntaxis::TYPE()
{
    if (!EQ("%") && !EQ("!") && EQ("$")) err_proc(228);
    gl();
}

void Syntaxis::COMP_OP()
{
    if (EQ("{")) {
        do {
            gl();
            OPERATOR();
        } while (EQ(";"));

        if (!EQ("}"))
            err_proc(553);
    }
    else err_proc(1337);
    gl();
}

void Syntaxis::ASSIGN_OP()
{
    if (EQ("let")) {
        gl();
        if (!ID())
            err_proc(228);
        gl();
        if (!EQ("="))
            err_proc(228);
        gl();
        EXPRESSION();
    }
    else err_proc(228);
}

void Syntaxis::CONDITION_OP()
{
    if (EQ("if")) {
        gl();
        EXPRESSION();
        if (!EQ("then"))
            err_proc(228);
        gl();
        OPERATOR();
        if (EQ("else")) {
            OPERATOR();
        }
        if (!EQ("end_else"))
            err_proc(228);
    }
    else err_proc(228);
    gl();
}

void Syntaxis::FOR_CICLE()
{
    if (EQ("for")) {
        gl();
        if (!EQ("("))
            err_proc(228);
        gl();
        if (ID() || NUM() || EQ("true") || EQ("false") || EQ("not") || EQ("(")) {
            EXPRESSION();
            gl();
        }
        if (!EQ(";"))
            err_proc(228);
        gl();
        if (ID() || NUM() || EQ("true") || EQ("false") || EQ("not") || EQ("(")) {
            EXPRESSION();
            gl();
        }
        if (!EQ(";"))
            err_proc(228);
        gl();
        if (ID() || NUM() || EQ("true") || EQ("false") || EQ("not") || EQ("(")) {
            EXPRESSION();
            gl();
        }
        if (!EQ(")"))
            err_proc(228);
        OPERATOR();
    }
    else err_proc(228);
}

void Syntaxis::WHILE_CICLE()
{
    if (EQ("do while")) {
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
            err_proc(69);

        if (!EQ("loop"))
            err_proc(1337);
    }
    else err_proc(420);
    gl();
}

void Syntaxis::INPUT(){
    if (EQ("input")) {
        gl();
        if (!EQ("("))
            err_proc(228);
        gl();
        while (ID()) {
            gl();
        }
        if (!EQ(")"))
            err_proc(228);
        gl();
    }
    else err_proc(228);
}

void Syntaxis::OUTPUT()
{
    if (EQ("output")) {
        gl();
        if (!EQ("("))
            err_proc(228);
        gl();
        while (ID() || NUM() || EQ("true") || EQ("false") || EQ("not") || EQ("(")) {
            EXPRESSION();
        }
        if (!EQ(")"))
            err_proc(228);
        gl();
    }
    else err_proc(228);

}

void Syntaxis::EXPRESSION()
{
    if (ID() || NUM() || EQ("true") || EQ("false") || EQ("not") || EQ("(")) {
        OPERAND();
    }
    else err_proc(228);

    if (EQ("< >") || EQ("=") || EQ("<") || EQ("<=") || EQ(">") || EQ(">=")) 
    {
        RATIO();
        if (ID() || NUM() || EQ("true") || EQ("false") || EQ("not") || EQ("(")) {
            OPERAND();
        }
        else err_proc(228);
    }
}

void Syntaxis::OPERAND()
{
    if (ID() || NUM() || EQ("true") || EQ("false") || EQ("not") || EQ("(")) {
        SUMMAND();
    }
    else err_proc(228);

    if ( EQ("+") || EQ("-") || EQ("or"))
    {
        ADDITION();
        if (ID() || NUM() || EQ("true") || EQ("false") || EQ("not") || EQ("(")) {
            SUMMAND();
        }
        else err_proc(228);
    }
}

void Syntaxis::SUMMAND()
{
    if (ID() || NUM() || EQ("true") || EQ("false") || EQ("not") || EQ("(")) {
        MULTIPLIER();
    }
    else err_proc(228);

    if (EQ("*") || EQ("/") || EQ("and"))
    {
        MULTIPLICATION();
        if (ID() || NUM() || EQ("true") || EQ("false") || EQ("not") || EQ("(")) {
            MULTIPLIER();
        }
        else err_proc(228);
    }
}

void Syntaxis::MULTIPLIER()
{
    if (!(ID() || NUM() || EQ("true") || EQ("false") || EQ("not") || EQ("("))) {
        err_proc(228);
    }
    if (EQ("(")) {
        gl();
        EXPRESSION();
        if (!EQ(")"))
            err_proc(228);
           
    }
    else if (EQ("not")) {
        UNARY();
    }
    gl();
}

void Syntaxis::NUMBER()
{
    if (!NUM()) err_proc(228);
    gl();

}

void Syntaxis::RATIO()
{
    if (!(EQ("< >") || EQ("=") || EQ("<") || EQ("<=") || EQ(">") || EQ(">="))) err_proc(228);
    gl();
}

void Syntaxis::ADDITION()
{
    if (!(EQ("+") || EQ("-") || EQ("or"))) err_proc(228);
    gl();
}

void Syntaxis::MULTIPLICATION()
{
    if (!(EQ("*") || EQ("/") || EQ("and"))) err_proc(228);
    gl();
}

void Syntaxis::UNARY()
{
    if (!EQ("not")) err_proc(228);
    gl();
}