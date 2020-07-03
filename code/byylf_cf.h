#pragma once
#ifndef byylf_cf_H
#define byylf_cf_H
#include <bits/stdc++.h>

using namespace std;

//token_table��ʽ
struct Token
{
	string code; //�����
	int loc;	 //�ڹؼ��֡��������ʶ�����ַ����������е��±�/λ��
};

Token token_table[100];

int ct_num = 0;
//�����������Ӧ��
int number[9][6] = {{1, 2, 3, 0, 0, 0}, {0, 0, 3, 0, 0, 0}, {0, 0, 3, 0, 0, 0}, {0, 0, 3, 4, 6, 9}, {0, 0, 5, 0, 0, 0}, {0, 0, 5, 0, 6, 9}, {7, 7, 8, 0, 0, 0}, {0, 0, 8, 0, 0, 0}, {0, 0, 8, 0, 0, 9}};

//�ؼ��ֱ�
string keywords[] = {"const", "int", "float", "char", "bool","void", "main", "if", "else", "do", "while", "for", "scanf", "printf", "return"};

//�����
string punctuation[] = {"+", "-", "*", "/", "<", "<=", ">", ">=", "==", "!=", "=", ";", ",", "(", ")", "[", "]", "{", "}"};

//��ʶ����
string idenfr[100];
int use_idenfr = 0;

//�ַ���
string charcon[50];
int use_charcon = 0;

//�ַ�����
string stringcon[50];
int use_stringcon = 0;

//���ͳ�����
int intcon[50];
int use_intcon = 0;

//�����ͳ�����
float floatcon[50];
int use_floatcon = 0;

//��дToken���б�ͬʱ�����⵽Ϊ������ʹ�ó���ת�����Գ������д���
void parse(string t, int loc, Token token_table[])
{
	token_table[ct_num].code = t;
	token_table[ct_num++].loc = loc;
}
//���ҹؼ��֣���ʶ����,��дToken���б�
void search_keyoide(string t, Token token_table[])
{
	string code;
	int loc;
	int flag_key = 0, flag_id = 0;
	for (int i = 0; i < 14; i++)
	{
		if (t == keywords[i])
		{
			loc = i;
			switch (i)
			{
			case 0:
				code = "CONSTTK";
				break;
			case 1:
				code = "INTTK";
				break;
			case 2:
				code = "FLOATTK";
				break;
			case 3:
				code = "CHARTK";
				break;
			case 4:
				code = "VOIDTK";
				break;
			case 5:
				code = "MAINTK";
				break;
			case 6:
				code = "IFTK";
				break;
			case 7:
				code = "ELSETK";
				break;
			case 8:
				code = "DOTK";
				break;
			case 9:
				code = "WHILETK";
				break;
			case 10:
				code = "FORTK";
				break;
			case 11:
				code = "SCANFTK";
				break;
			case 12:
				code = "PRINTFTK";
				break;
			case 13:
				code = "RETURNTK";
				break;
			}
			flag_key = 1;
		}
		if (flag_key == 1)
			break;
	}
	if (flag_key == 0) //���ǹؼ���
	{
		code = "IDENFR";
		for (int i = 0; i < use_idenfr; i++) //�Ƿ��ڱ�ʶ������
		{
			if (t == idenfr[i])
			{
				loc = i;
				flag_id = 1;
			}
			if (flag_id == 1)
				break;
		}
		if (flag_id == 0) //���ڱ�ʶ������,����
		{
			idenfr[use_idenfr++] = t;
			loc = use_idenfr - 1;
		}
	}
	parse(code, loc, token_table); //��дToken���б�ͬʱ�����⵽Ϊ������ʹ�ó���ת�����Գ������д���
}
//�����ͱ������±�
int search_int(int i)
{
	int flag_int = 0, loc;
	for (int j = 0; j < use_intcon; j++)
	{
		if (i == intcon[i])
		{
			loc = j;
			flag_int = 1;
		}
		if (flag_int == 1)
			break;
	}
	if (flag_int == 0)
	{
		intcon[use_intcon++] = i;
		loc = use_intcon - 1;
	}
	return loc;
}
//�鸡���ͱ������±�
int search_float(float i)
{
	int flag_float = 0, loc;
	for (int j = 0; j < use_floatcon; j++)
	{
		if (i == floatcon[j])
		{
			loc = j;
			flag_float = 1;
		}
		if (flag_float == 1)
			break;
	}
	if (flag_float == 0)
	{
		floatcon[use_floatcon++] = i;
		loc = use_floatcon - 1;
	}
	return loc;
}
//���ַ���
void search_char(string ch, Token token_table[])
{
	int flag_char = 0, loc;
	for (int i = 0; i < use_charcon; i++)
	{
		if (ch == charcon[i])
		{
			loc = i;
			flag_char = 1;
		}
		if (flag_char == 1)
			break;
	}
	if (flag_char == 0)
	{
		charcon[use_charcon++] = ch;
		loc = use_charcon - 1;
	}
	parse("CHARCON", loc, token_table);
}
//���ַ�����
void search_string(string s, Token token_table[])
{
	int flag_string = 0, loc;
	for (int i = 0; i < use_stringcon; i++)
	{
		if (s == stringcon[i])
		{
			loc = i;
			flag_string = 1;
		}
		if (flag_string == 1)
			break;
	}
	if (flag_string == 0)
	{
		stringcon[use_stringcon++] = s;
		loc = use_stringcon - 1;
	}
	parse("STRCON", loc, token_table);
}
//��������������س���
float string_to_num(string t)
{
	//������Ϊfloat�ͣ��ڵ������ĺ����н��е���
	int n, m, p, s, y, e, i = 0, j;
	float num;
	string jin = "#";
	t += jin;
	int state = 1;
	while (state != 10)
	{
		switch (state)
		{
		case 1:
			n = 0;
			m = 0;
			p = 0;
			s = 0;
			y = 1;
			e = 1;
			num = 0;
			break;
		case 2:
			y = 1;
			break;
		case 3:
			y = -1;
			break;
		case 4:
			n = 10 * n + t[i - 1] - 48;
			break;
		case 5:
			s = 1;
			break;
		case 6:
			n = 10 * n + t[i - 1] - 48;
			m++;
			break;
		case 7:
			s = 1;
			break;
		case 8:
			if (t[i - 1] == '-')
				e = -1;
			break;
		case 9:
			p = 10 * p + t[i - 1] - 48;
			break;
		}
		switch (t[i++])
		{
		case '+':
			if (t[i - 2] == e)
				j = 6;
			else
				j = 0;
			break;
		case '-':
			if (t[i - 2] == e)
				j = 6;
			else
				j = 1;
			break;
		case '.':
			j = 3;
			break;
		case 'e':
			j = 4;
			break;
		case '#':
			j = 5;
			break;
		default:
			j = 2;
			break;
		}
		if (number[state - 1][j] == 0)
			cout << "error" << endl;
		else
			state = number[state - 1][j] + 1;
		if (state == 10)
			num = y * n * pow(10, e * p - m);
	}
	return num;
}
//����state_beforeȷ��,���������
void state_to_code(int state_before, string t, Token token_table[])
{
	int loc; //λ��
	int i;
	float f;
	switch (state_before)
	{
	case 2:
		parse("PLUS", 0, token_table);
		break;
	case 3:
		parse("MINU", 1, token_table);
		break;
	case 4:							 //����
		i = (int)string_to_num(t);	 //ͳһ���ظ����ͣ����͵��ڴ˽��е���
		loc = search_int(i);		 //��ѯ����д
		parse("INTCON", loc, token_table); //���ͷ�����
		break;
	case 6: //������߿�ѧ������
	case 9:
		f = string_to_num(t);
		loc = search_float(f);		   //��ѯ����д
		parse("FLOATCON", loc, token_table); //������������
		break;
	case 10:
		parse("MULT", 2, token_table);
		break;
	case 11:
		parse("DIV", 3, token_table);
		break;
	case 12:
		parse("LSS", 4, token_table);
		break;
	case 13:
		parse("LEQ", 5, token_table);
		break;
	case 14:
		parse("GRE", 6, token_table);
		break;
	case 15:
		parse("GEQ", 7, token_table);
		break;
	case 16:
		parse("ASSIGN", 10, token_table);
		break;
	case 17:
		parse("EQL", 8, token_table);
		break;
	case 19:
		parse("NEQ", 9, token_table);
		break;
	case 20:
		parse("SEMICN", 11, token_table);
		break;
	case 21:
		parse("COMMA", 12, token_table);
		break;
	case 22:
		parse("LPARENT", 13, token_table);
		break;
	case 23:
		parse("RPARENT", 14, token_table);
		break;
	case 24:
		parse("LBRACK", 15, token_table);
		break;
	case 25:
		parse("RBRACK", 16, token_table);
		break;
	case 26:
		parse("LBRACE", 17, token_table);
		break;
	case 27:
		parse("RBRACE", 18, token_table);
		break;
	case 30: //�ַ�
		search_char(t, token_table);
		break;
	case 33: //�ַ���
		search_string(t, token_table);
		break;
	case 34: //���ʶ�����ؼ���
	case 35:
		search_keyoide(t, token_table);
		break;
	default:
		break;
	}
}
//���ݵ�ǰ״̬�͵�ǰ���������ݣ�������һ��״̬
int state_change(int now_state, char now_ch)
{
	int next_state = 0; //��һ��״̬
	switch (now_state)
	{
	case 1:
		if (now_ch <= '9' && now_ch >= '0')
			next_state = 4;
		else if (now_ch <= 'Z' && now_ch >= 'A' || now_ch <= 'z' && now_ch >= 'a' || now_ch == '_')
			next_state = 34;
		else
			next_state = 1;
		switch (now_ch)
		{
		case '+':
			next_state = 2;
			break;
		case '-':
			next_state = 3;
			break;
		case '*':
			next_state = 10;
			break;
		case '/':
			next_state = 11;
			break;
		case '<':
			next_state = 12;
			break;
		case '>':
			next_state = 14;
			break;
		case '=':
			next_state = 16;
			break;
		case '!':
			next_state = 18;
			break;
		case ';':
			next_state = 20;
			break;
		case ',':
			next_state = 21;
			break;
		case '(':
			next_state = 22;
			break;
		case ')':
			next_state = 23;
			break;
		case '[':
			next_state = 24;
			break;
		case ']':
			next_state = 25;
			break;
		case '{':
			next_state = 26;
			break;
		case '}':
			next_state = 27;
			break;
		case 39: //������
			next_state = 28;
			break;
		case '"':
			next_state = 31;
			break;
		default:
			break;
		}
		break;
	case 2:
	case 3:
		if (now_ch <= '9' && now_ch >= '0')
			next_state = 4;
		else
			next_state = 0;
		break;
	case 4:
		if (now_ch <= '9' && now_ch >= '0')
			next_state = 4;
		else if (now_ch == '.')
			next_state = 5;
		else if (now_ch == 'e' || now_ch == 'E')
			next_state = 7;
		else
			next_state = 0;
		break;
	case 5:
		if (now_ch <= '9' && now_ch >= '0')
			next_state = 6;
		//�˴����ܳ��ִ��󣬴�����
		break;
	case 6:
		if (now_ch <= '9' && now_ch >= '0')
			next_state = 6;
		else if (now_ch == 'e')
			next_state = 7;
		//�˴����ܳ��ִ��󣬴�����
		break;
	case 7:
		if (now_ch <= '9' && now_ch >= '0')
			next_state = 9;
		else if (now_ch == '+' || now_ch == '-')
			next_state = 8;
		//�˴����ܳ��ִ��󣬴�����
		break;
	case 8:
		if (now_ch <= '9' && now_ch >= '0')
			next_state = 9;
		//�˴����ܳ��ִ��󣬴�����
		break;
	case 9:
		if (now_ch <= '9' && now_ch >= '0')
			next_state = 9;
		else
			next_state = 0;
		break;
	case 12:
		if (now_ch == '=')
			next_state = 13;
		else
			next_state = 0;
		break;
	case 14:
		if (now_ch == '=')
			next_state = 15;
		else
			next_state = 0;
		break;
	case 16:
		if (now_ch == '=')
			next_state = 17;
		else
			next_state = 0;
		break;
	case 18:
		if (now_ch == '=')
			next_state = 19;
		//�˴���Щ���������
		break;
	case 28:
		if (now_ch != 32)
			next_state = 29; //�����ַ���Ϊ�����,���ո�
		break;
	case 29:
		if (now_ch == 39)
			next_state = 30;
		//�˴����ܳ��ִ��󣬴�����
		break;
	case 31:
		if (now_ch == 32 || now_ch == 33 || now_ch <= 126 && now_ch >= 35)
			next_state = 32;
		//�˴����ܳ��ִ��󣬴�����
		break;
	case 32:
		if (now_ch == 32 || now_ch == 33 || now_ch <= 126 && now_ch >= 35)
			next_state = 32;
		else if (now_ch == '"')
			next_state = 33;
		break;
	case 34:
		if (now_ch <= 'Z' && now_ch >= 'A' || now_ch <= 'z' && now_ch >= 'a' || now_ch == '_')
			next_state = 34;
		else if (now_ch <= '9' && now_ch >= '0')
			next_state = 35;
		else
			next_state = 0;
		break;
	case 35:
		if (now_ch <= 'Z' && now_ch >= 'A' || now_ch <= 'z' && now_ch >= 'a' || now_ch == '_' || now_ch <= '9' && now_ch >= '0')
			next_state = 35;
		else
			next_state = 0;
		break;
	case 10:
	case 11:
	case 13:
	case 15:
	case 17:
	case 19:
	case 20:
	case 21:
	case 22:
	case 23:
	case 24:
	case 25:
	case 26:
	case 27:
	case 30:
	case 33:
		next_state = 0;
		break;
	default:
		next_state = 0;
		break;
	}
	return next_state;
}

void byylf_cf()
{
	ifstream file; //���ļ��л�ô���������
	string sta = "", stb;
	file.open("test.txt", ios::in);
	if (!file.good())
	{
		cout << "�ļ���ʧ�ܣ���";
		return;
	}
	while (!file.eof())
	{
		getline(file, stb);
		sta += stb;
	}
	int state = 1, state_before = 1;
	string t = ""; //���浱ǰ��
	int i = 0;	   //ѭ������
	while (i <= sta.length())
	{									 //�����������������
		char ch = sta[i];				 //һ�������������
		state_before = state;			 //���浱ǰ״̬����������к�������
		state = state_change(state, ch); //״̬ת�ƺ���
		if (state)
		{ //����δ�������״̬
			if (ch == ' ')
			{
				if (t[0] == '"')
					t = t + ch; //������Ѿ�����������ַ�
			}
			else
				t = t + ch; //������Ѿ�����������ַ�
		}
		else
		{										   //�������״̬
			state_to_code(state_before, t, token_table); //����state_beforeȷ�������
			i--;								   //��ֹ��©����������
			state = 1;
			t = ""; //����state��t
		}
		i++;
	}
	// for (i = 0; i < ct_num && ct_num < 100; i++)
	// 	cout << token_table[i].code << "  " << token_table[i].loc << endl;
	// cout << endl;
	cout<<token_table[5].code<<endl;
	// for (i = 0; i <= use_idenfr; i++)
	// 	cout << idenfr[i] << endl;
	// cout << endl;
	// for (i = 0; i <= use_stringcon; i++)
	// 	cout << stringcon[i] << endl;
	// cout << endl;
	// for (i = 0; i <= use_charcon; i++)
	// 	cout << charcon[i] << endl;
	// cout << endl;
	// for (i = 0; i <= use_floatcon; i++)
	// 	cout << floatcon[i] << endl;
	// cout << endl
	// 	 << use_intcon << endl;
	// for (i = 0; i <= use_intcon; i++)
	// 	cout << intcon[i] << endl;
}
#endif
