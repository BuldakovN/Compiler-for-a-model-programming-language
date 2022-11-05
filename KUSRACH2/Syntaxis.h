#pragma once
#include "Types.h"

//�������
struct lexem {
	enum class Table_index tab; //�������������� ������� 
	int id;						//���������� ����� � �������
	std::string value;			//�������� �������
	int number;					//����� ������� �� �������
};

class Syntaxis
{
	std::string filename;		//�������� �����
	std::fstream lexeme_file;	//���� � ���������
	lexem LEX;					//�������

	bool gl();
	bool EQ(std::string);
	bool ID();
	bool NUM();
	std::string get();
	int err_proc(int);

public:
	Syntaxis(std::string);
	void scanner();

private:

/*--------------------------��������� �������� ���������� ������, ����������� ������� ����--------------------------*/

	//<���������>::= 		�{� {/ (<��������> | <��������>) ; /} �}�
	void PROG();

	//<��������>::= 		{<�������������> {, <�������������> } : <���> ;}
	void DESCR();
	
	//<��������>::= 	<���������> | <������������> | <��������> |
	//		<��������������_�����> | <���������_�����> | <�����> |
	//		<������>
	void OPERATOR();

	//<���>::= 		% | ! | $
	void TYPE();


/*--------------------------�������, ������������ �������� ���������--------------------------*/
	//<���������>::= 		�{� <��������> { ; <��������> } �}�
	void COMP_OP();

	//<������������>::= 	[ let ] <�������������> = <���������>
	void ASSIGN_OP();

	//<��������>:: = if <���������> then <��������>[else <��������>] end_else
	void CONDITION_OP();

	//<����_�����>::= 	for �(�[<���������>] ; [<���������>] ; [<���������>] �)� <��������>
	void FOR_CICLE();

	//<���������_�����>:: = do while <���������> <��������> loop
	void WHILE_CICLE();

	//<�����>::= 		input �(�<�������������> {������ <�������������>} �)�
	void INPUT();

	//<������>::= 		output �(�<���������> { ������ <���������> } �)�
	void OUTPUT();


/*--------------------------�������������, ����� ��� �����--------------------------*/
	//<�������������>::= 	<�����> {<�����> | <�����>}
	void IDENT();

	//<�����>
	void LETTER();

	//<�����>
	void DIGIT();


/*--------------------------��������� �����--------------------------*/
	//<���������>:: =	<�������>{ <��������_������_���������> <�������> }
	void EXPRESSION();

	//<�������>::= 		<���������> {<��������_������_��������> <���������>}
	void OPERAND();

	//<���������>::= 	<���������> {<��������_������_���������> <���������>}
	void SUMMAND();

	//<���������>::= 	<�������������> | <�����> | <����������_���������> |
	//					<�������_��������> <���������> | �(�<���������>�)�
	void MULTIPLIER();

	//<�����>:: =		<�����> | <��������������>
	void NUMBER();

	//<���_���������>::= 	true | false
	void BOOL();


/*--------------------------�������, ������������ ����� �����--------------------------*/
	//<�����>::= 		<��������> | <������������> | <����������> | <�����������������>
	void INTEGER();

	//<��������>::= 		{/ 0 | 1 /} (B | b)
	void BIN();

	//<������������>::= 	{/ 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 /} (O | o)
	void OCT();

	//<����������>:: = { / <�����> / }[D | d]
	void DEC();

	//<�����������������>::=	<�����>{ <�����> | A | B | C | D | E | F | a | b |
	//			c | d | e | f } (H | h)
	void HEX();


/*--------------------------�������, ����������� �������������� �����--------------------------*/
	//<��������������>::= 	<��������_������> <�������> |
	//			[<��������_������>] . <��������_������>[�������]
	void FLOAT();

	//<��������_������>::= 	{/ <�����> /}
	void NUMBER_STR();

	//<�������>::= 		( E | e )[+ | -] <��������_������>
	void ORDER();


/*--------------------------�������� �����--------------------------*/
	//<��_������_���������>:: = 	< > | = | < | <= | > | >=
	void RATIO();

	//<��_������_��������>:: = 		+ | - | or
	void ADDITION();

	//<��_������_���������>:: =		*| / |and
	void MULTIPLICATION();

	//<�������_��������>::= 		not
	void UNARY();
};
