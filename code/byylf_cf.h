#ifndef byylf_cf_H
#define byylf_cf_H
#include <fstream>
#include <iostream>
#include <math.h>
#include <string>
using namespace std;

//token形式
struct Token
{
    string code; //类别码
    int loc;     //在关键字、界符、标识符、字符、常量表中的下标/位置
};

//填写Token序列表，同时如果监测到为常数，使用常数转换机对常数进行处理
void parse1(string t, int loc, Token token[]);

//查找关键字，标识符表,填写Token序列表
void search_keyoide(string t, Token token[]);
//查整型表，返回下标
int search_int(int i);
//查浮点型表，返回下标
int search_float(float i);
//查字符表
void search_char(string ch, Token token[]);
//查字符串表
void search_string(string s, Token token[]);
//常数处理机，返回常数
float string_to_num(string t);
//根据state_before确定,返回类别码
void state_to_code(int state_before, string t, Token token[]);
//根据当前状态和当前待处理数据，返回下一个状态
int state_change(int now_state, char now_ch);

void byylf_cf();
extern int ct_num;
extern string idenfr[1000];
extern int intcon[500];
extern float floatcon[500];
extern string charcon[500];
extern string stringcon[500];

#endif