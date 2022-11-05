#pragma once
#include "Types.h"

//�������
struct lexem {
	enum class Table_index tab; //�������������� ������� 
	int id;						//���������� ����� � �������
	std::string value;			//�������� �������
	int number;					//����� ������� �� �������
};

class Parser
{
	std::vector<lexem> declareted_identificators;	//������ ���������� ���������������
	std::string filename;							//�������� �����
	std::fstream lexeme_file;						//���� � ���������
	lexem LEX;										//�������

	bool gl();
	bool EQ(std::string);
	bool ID();
	bool NUM();
	int err_proc(int);								//����� ������
	int check_lex();
	void add();										//�������� ������������� � ������ �����������

public:
	Parser(std::string);
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
	void IF_OP();

	//<����_�����>::= 	for �(�[<���������>] ; [<���������>] ; [<���������>] �)� <��������>
	void FOR_CICLE();

	//<���������_�����>:: = do while <���������> <��������> loop
	void WHILE_CICLE();

	//<�����>::= 		input �(�<�������������> {������ <�������������>} �)�
	void INPUT();

	//<������>::= 		output �(�<���������> { ������ <���������> } �)�
	void OUTPUT();

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