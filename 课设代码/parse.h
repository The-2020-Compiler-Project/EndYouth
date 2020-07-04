#ifndef PARSE_H_INCLUDED
#define PARSE_H_INCLUDED
#include "byylf_cf.h"

typedef enum
{
	stmtk,	//���
	expk	//���ʽ
} Nodekind; ///�������

typedef enum
{
	ifk,
	fork,
	whilek,
	returnk,
	assignk,
	funck,
	defineparak,
	maink,
	define_arrayk,
	structk,
	switchk,
	casek,
	breakk,
	defaultk
} Stmtkind; ///��������

typedef enum
{
	opk,
	constk,
	idk,
	cite_arrayk
} Expkind; ///���ʽ����

typedef struct treenode
{
	struct treenode *child[4]; //Ҳ��for�����ĸ�����
	struct treenode *sibling;
	int lineno;
	Nodekind nodekind; //�ڵ����ͣ����/���ʽ
	union
	{
		Stmtkind stmt; //���
		Expkind exp;   //���ʽ
	} kind;
	string tokentype1; //token������
	int loc;	 //�ڹؼ��֡��������ʶ�����ַ����������е��±�/λ��
		
	
} treenode; 
///�ο�����ԭ��ʵ�������ṹ�Ķ���
///��Expkind������������������ʶ��������������������idk����
	//��������������������ֵ������ ����INT,FLOAT,CHAR,DOUBLE,VOID

int line_num_table[1000];
int lineno;
int tokenno;
string token;

#endif // PARSE_H_INCLUDED
