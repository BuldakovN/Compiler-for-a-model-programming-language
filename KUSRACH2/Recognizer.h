#pragma once
#include "Lexer.h"
#include "Parser.h"

extern 

class Recognizer
{
	Lexer lexer;
	Parser parser;
public:
	Recognizer(std::string);
	void run();
};