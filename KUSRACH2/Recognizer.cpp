#include "Recognizer.h"


Recognizer::Recognizer(std::string p_filename):
	lexer(p_filename), 
	parser(p_filename)
{}

void Recognizer::run()
{
	lexer.scanner();
	parser.scanner();
}
